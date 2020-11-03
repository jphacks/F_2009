from flask import Flask
from flask import Blueprint, request
from flask import jsonify

# from ..models.model import UserEntity
# from ..models.model import UserService


app = Blueprint('status', __name__)

@app.route('/status', methods=['GET'])
def status():
    # us = UserService()
    # a = us.find_all()

    body = {
        "status": 1,
        "entry_time": "2020-11-01 10:45:34 +09:00",
        "alert": False
    }
    return jsonify(body)

