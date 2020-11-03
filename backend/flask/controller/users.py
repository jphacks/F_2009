from flask import Flask
from flask import Blueprint, request
from flask import jsonify
import random, string
#
# from ..models.model import UserEntity
# from ..models.model import UserService


app = Blueprint('users', __name__)


@app.route('/users/create', methods=['POST'])
def create():
    req_dict = request.get_json(force=True)
    randomname = ''.join([random.choice(string.ascii_letters + string.digits) for i in range(20)])
    device_id = req_dict["device_id"]
    # ue = UserEntity()
    # ue.user_id = randomname
    # ue.device_id = device_id
    # us = UserService()
    # us.create(ue)

    body = {
        'user_id': randomname
    }

    return jsonify(body)