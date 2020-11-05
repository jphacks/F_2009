import sys
import time

from apscheduler.schedulers.blocking import BlockingScheduler
#from apscheduler.schedulers.background import BackgroundScheduler

# 参照するディレクトリをひとつ上の階層へ
sys.path.append('../')
from models.model import UserService
from controller.status import check_status

scheduler = BlockingScheduler()

#scheduler = BackgroundScheduler()



@scheduler.scheduled_job('interval', seconds=10, max_instances=1)
def check_bath_status():
    us = UserService()
    users = us.find_all()

    for user in users:
        print(user.user_id)
        #status_dict = check_status()
        print('5秒毎に実行')

