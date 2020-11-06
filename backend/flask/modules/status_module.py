import sys
import datetime

from .bathroom_monitor import BathroomMonitor
from .history_module import check_history
# 参照するディレクトリをひとつ上の階層へ
sys.path.append('../')
from models.model import UserEntity
from models.model import UserService

def check_status(user_id):
    bm = BathroomMonitor(user_id)

    #デバイスから入浴履歴取得
    grandparents_time_dict = bm.fast_list()
    if grandparents_time_dict["status"] == 400:
        return {"result": "error", "message": "データの取得に失敗しました"}

    # 最新の履歴を取得
    latest_dict = grandparents_time_dict["grandma_list"][0]
    # ダミー
    # latest_dict = {'checkin_time': '20201106133200', 'checkout': '0', 'bath_time': '40'}

    # 入浴開始時間　文字列 -> datetime型に変換
    latest_tdatetime = datetime.datetime.strptime(latest_dict["checkin_time"],
                                                  '%Y%m%d%H%M%S')
    now = datetime.datetime.now()

    body_dict = {}
    status = None

    if latest_tdatetime.day == now.day:
        # 最新の履歴と今日の日付が同一　-> 入浴後or入浴中
        if latest_dict["checkout"] == "0":
            # 緊急状態チェック
            alert_bool = alert_evaluation(user_id, int(latest_dict["bath_time"]))
            if alert_bool:
                # 緊急状態
                status = 3
                jst_entry_time = chenge_timeformat(latest_tdatetime)
                body_dict["entry_time"] = jst_entry_time
                body_dict["message"] = "緊急状態です"
            else:
                # 入浴中
                status = 1
                jst_entry_time = chenge_timeformat(latest_tdatetime)
                body_dict["entry_time"] = jst_entry_time
                body_dict["message"] = "入浴中です"
        else:
            # 入浴後
            status = 2
            jst_entry_time = chenge_timeformat(latest_tdatetime)
            jst_exit_time = chenge_timeformat(
                latest_tdatetime + datetime.timedelta(
                    minutes=int(latest_dict["bath_time"])))
            body_dict["entry_time"] = jst_entry_time
            body_dict["exit_time"] = jst_exit_time
            body_dict["message"] = "今日の入浴は終わりました"
    else:
        # 入浴前
        status = 0
        body_dict["message"] = "今日はまだ入浴していません"

    body_dict["status"] = status

    return body_dict


def chenge_timeformat(tdatetime):
    # 時間データをJST形式に変換
    utc_time = tdatetime + datetime.timedelta(hours=-9)
    jst_time = utc_time.strftime('%Y-%m-%d %H:%M:%S +9000')
    return jst_time

def alert_evaluation(user_id, bath_time):
    """
    緊急状態かどうか評価する
    :param user_id: ユーザID
    :param bath_time: 入室してからの経過時間
    :return: 緊急状態：true , 問題なし：false
    """
    history_dict = check_history(user_id,"all")

    if history_dict["mean"] == 0:
        # 平均が0 -> 過去データがなければ26で計算
        mean_bath_time = 26
    else:
        mean_bath_time = history_dict["mean"]

    if bath_time > mean_bath_time * 2:
        # 経過時間が平均入浴時間の倍より長ければ緊急
        return True
    else:
        # 問題なし
        return False

