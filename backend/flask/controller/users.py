import sys

from flask import Flask
from flask import Blueprint, request
from flask import jsonify
import random, string


# 参照するディレクトリをひとつ上の階層へ
sys.path.append('../')
from models.model import UserEntity
from models.model import UserService
from modules.bathroom_monitor import BathroomMonitor


app = Blueprint('users', __name__)


@app.route('/users/create', methods=['POST'])
def create():
    req_dict = request.get_json(force=True)
    device_id = req_dict["device_id"]
    us = UserService()
    user = us.findByDeviceId(device_id)
    if user is not None:
        return jsonify({"result": "error", "message": "割当済みのデバイスです"})

    bm = BathroomMonitor()
    bm.set_device_id(device_id)
    res = bm.dummy()
    if res["status"] == 400:
        return jsonify({"result": "error", "message": "指定のIoTデバイスは存在しません"})

    # ランダム文字列生成
    randomname = ''.join([random.choice(string.ascii_letters + string.digits) for i in range(20)])
    ue = UserEntity()
    ue.user_id = randomname
    ue.device_id = device_id
    us = UserService()
    us.create(ue)

    body = {
        'result': 'success',
        'user_id': randomname
    }

    return jsonify(body)