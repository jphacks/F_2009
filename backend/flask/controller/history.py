import sys
import datetime
from flask import Flask
from flask import Blueprint, request
from flask import jsonify

# 参照するディレクトリをひとつ上の階層へ
sys.path.append('../')
#from modules.bathroom_monitor import BathroomMonitor
from modules.history_module import check_history
app = Blueprint('history', __name__)

@app.route('history/week', methods=['GET'])
def week():
    user_id = "testuser"
    result_dict = check_history(user_id, 'week')
    return jsonify(result_dict)


