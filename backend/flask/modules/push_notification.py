import sys

from onesignal_sdk.client import Client

# 参照するディレクトリをひとつ上の階層へ
sys.path.append('../')
import config

APP_ID = config.APP_ID
REST_API_KEY = config.REST_API_KEY

client = Client(app_id=APP_ID, rest_api_key=REST_API_KEY)


def send_alert():
    notification_body = {
        'contents': {'en': '長時間お風呂から出ていないようです'},
        'included_segments': ["Active Users", "Inactive Users"],
    }
    response = client.send_notification(notification_body)
    return response.body
    # 'included_segments': ["Active Users", "Inactive Users"],

def send_enter_notification():
    notification_body = {
        'contents': {'en': 'お風呂に入りました'},
        'included_segments': ["Active Users", "Inactive Users"],
    }
    response = client.send_notification(notification_body)
    return response.body

def send_exit_notification():
    notification_body = {
        'contents': {'en': 'お風呂から出ました'},
        'included_segments': ["Active Users", "Inactive Users"],
    }
    response = client.send_notification(notification_body)
    return response.body