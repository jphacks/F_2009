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
            jst_entry_time = chenge_timeformat(latest_tdatetime)
            body["entry_time"] = jst_entry_time
            body["message"] = "入浴中です"
        else:
            # 入浴後
            status = 2
            jst_entry_time = chenge_timeformat(latest_tdatetime)
            jst_exit_time = chenge_timeformat(latest_tdatetime + datetime.timedelta(minutes=int(latest_dict["bath_time"])))
            body["entry_time"] = jst_entry_time
            body["exit_time"] = jst_exit_time
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

def chenge_timeformat(tdatetime):
    # 時間データをJST形式に変換
    utc_time = tdatetime + datetime.timedelta(hours=-9)
    jst_time = utc_time.strftime('%Y-%m-%d %H:%M:%S +9000')
    return jst_time

