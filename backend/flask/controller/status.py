import sys
import datetime
from flask import Flask
from flask import Blueprint, request
from flask import jsonify

# 参照するディレクトリをひとつ上の階層へ
sys.path.append('../')
from models.model import UserEntity
from models.model import UserService
from modules.bathroom_monitor import BathroomMonitor

app = Blueprint('status', __name__)

@app.route('/status', methods=['GET'])
def status():
    """
    入浴状態を取得
    入浴前：０
    入浴中：１
    入浴後：２
    :return:
    """
    user_id = "testuser"
    bm = BathroomMonitor(user_id)

    # デバイスから入浴履歴取得
    grandparents_time_list = bm.fast_list()
    # 最新の履歴を取得
    latest_dict = grandparents_time_list["grandma_list"][0]
    latest_tdatetime = datetime.datetime.strptime(latest_dict["checkin_time"], '%Y%m%d%H%M%S')
    now = datetime.datetime.now()

    body = {}
    status = None

    if latest_tdatetime.day == now.day:
        # 最新の履歴と今日の日付が同一　-> 入浴後or入浴中
        if latest_dict["checkout"] == "0":
            # 入浴中
            status = 1
            utc_time_entry = latest_tdatetime + datetime.timedelta(hours=-9)
            jst_entry_time = utc_time_entry.strftime('%Y-%m-%d %H:%M:%S +9000')
            body["entry_time":jst_entry_time]
            body["message"] = "入浴中です"
        else:
            # 入浴後
            status = 2
            body["message"] = "今日の入浴は終わりました"
    else:
        # 入浴前
        status = 0
        body["message"] = "今日はまだ入浴していません"

    body["status"] = status

    # アラートチェック
    us = UserService()
    user = us.find(user_id)
    body["alert"] = bool(user.alert)

    return jsonify(body)

