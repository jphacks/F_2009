import sys
import datetime
from flask import Flask
from flask import Blueprint, request
from flask import jsonify


# 参照するディレクトリをひとつ上の階層へ
sys.path.append('../')
from models.model import UserEntity
from models.model import UserService
from modules.status_module import check_status


app = Blueprint('status', __name__)

@app.route('/status', methods=['GET'])
def call_status():
    """
    入浴状態を取得
    入浴前：０
    入浴中：１
    入浴後：２
    :return:
    """
    user_id = "testuser"
    result_dict = check_status(user_id)
    return jsonify(result_dict)

