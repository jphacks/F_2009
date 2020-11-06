import datetime

from .bathroom_monitor import BathroomMonitor

def get_range(time_list,range):
    if (len(time_list['grandma_list']) >= 7):
        if (range == 'week'):
            week_list = time_list['grandma_list'][0:7]
            return week_list
        if (range == 'all'):
            all_list = time_list['grandma_list']
            return all_list
    else:
        # データが一週間分なければすべて返す
        if (range == 'all'):
            all_list = time_list['grandma_list']
            return all_list

def datetime_to_date(datetime_str):
    # datetime型に変換
    tdatetime = datetime.datetime.strptime(datetime_str, '%Y%m%d%H%M%S')
    # 任意の文字列に変換
    tstr = tdatetime.strftime('%Y-%m-%d')
    return tstr

def calc_mean(time_list):
    # 平均値取得
    if len(time_list) == 0:
        return 0
    else:
        sum = 0
        for item in time_list:
            sum += int(item['bath_time'])
        mean = int(sum / len(time_list))
        return mean

def reverse_list(time_list):
    # 配列を逆順にする
    time_list.reverse()
    return time_list

def check_history(user_id, window):
    """

    :param user_id:
    :param window: 範囲、all, week ...
    :return:
    """
    bm = BathroomMonitor(user_id)
    # デバイスから入浴履歴取得
    grandparents_time_dict = bm.fast_list()
    if grandparents_time_dict["status"] == 400:
        return {"result":"error","message":"データの取得に失敗しました"}

    # window分の期間を抽出
    week_list = get_range(grandparents_time_dict,window)
    # リストを逆順に並べ替え
    week_list_reverse = reverse_list(week_list)
    result_dict = {"result": "success", "history": [], "mean": None, "message": "データの取得に成功しました"}
    for index, item in enumerate(week_list_reverse):
        # 日付抽出
        date = datetime_to_date(item["checkin_time"])
        result_dict["history"].append({"date": date, "minute": int(item["bath_time"])})
    # 平均計算
    result_dict["mean"] = calc_mean(week_list)

    return result_dict