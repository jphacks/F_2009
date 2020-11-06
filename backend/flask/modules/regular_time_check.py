import sys
import time

#from apscheduler.schedulers.blocking import BlockingScheduler
from apscheduler.schedulers.background import BackgroundScheduler

from .history_module import check_history
from .status_module import check_status
from .push_notification import send_alert, send_enter_notification, send_exit_notification
# 参照するディレクトリをひとつ上の階層へ
sys.path.append('../')
from models.model import UserService


#scheduler = BlockingScheduler()

scheduler = BackgroundScheduler()



@scheduler.scheduled_job('interval', seconds=5, max_instances=1)
def regular_check_bathtime():
    """
    入浴状態の定期チェック
    :return:
    """
    us = UserService()
    users = us.find_all()
    print('1分毎に実行')
    for user in users:
        print(user.user_id)
        status_dict = check_status(user.user_id)
        if status_dict["status"] == 1:
            # 入浴中
            if user.notice_management == 0 or user.notice_management == 2 or user.notice_management == 3:
                # 入浴してからまだ通知していなければ通知する
                user.notice_management = 1
                us.update(user)
                send_enter_notification()

            break
        elif status_dict["status"] == 2:
            # 入浴後
            if user.notice_management == 0 or user.notice_management == 1 or user.notice_management == 3:
                # 入浴後まだ通知していなければ通知する
                user.notice_management = 2
                us.update(user)
                send_exit_notification()
            break
        elif status_dict["status"] == 3:
            # 緊急
            if user.notice_management == 0 or user.notice_management == 1 or user.notice_management == 2:
                # 緊急時まだ通知していなければ通知する
                user.notice_management = 3
                us.update(user)
                send_alert()
            break
        else:
            # 入浴前
            if user.notice_management != 0:
                user.notice_management = 0
                us.update(user)
            break

        print('5秒毎に実行')
        return