from flask import Flask
from flask import Blueprint, request
from flask import jsonify



app = Blueprint('status', __name__)

@app.route('/status', methods=['GET'])
def status():
    
    body = {
        "status": True,
        "entry_time": "2020-11-01 10:45:34 +09:00",
        "alert": False
    }
    return jsonify(body)

