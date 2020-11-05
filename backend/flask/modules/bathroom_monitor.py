import sys
import requests
import ast

# 参照するディレクトリをひとつ上の階層へ
sys.path.append('../')
from models.model import UserService

class BathroomMonitor(object):
    def __init__(self, user_id=None):
        self.user_id = user_id
        self.device_id = None
        self.hash = None

    def set_device_id(self,device_id):
        self.device_id = device_id
        return self.device_id

    def check_user(self):
        """
        dbにユーザが存在するか確認する
        :return:
        """
        us = UserService()
        user = us.find(self.user_id)
        if user is None:
            return None
        else:
            # デバイスidセット
            self.device_id = user.device_id
            self.hash = user.token
            return user

    def dummy(self):
        """
        テスト用にIoTデバイスのログイン時間を更新する
        :return:
        """
        payload = {"device_id": self.device_id}
        res = requests.post(
            'http://kn46itblog.xsrv.jp/hackathon/jphacks2020/php_apis/device/edit/dummy', json=payload
        )
        print(res.text)
        # String -> dict 変換
        res_dict = ast.literal_eval(res.text)
        return res_dict

    def assign(self):
        """
        デバイスにユーザを割り当てる
        :return:
        """
        payload = \
            {
                "device_id": self.device_id,
                 "user_id": self.user_id
            }

        res = requests.post(
            'http://kn46itblog.xsrv.jp/hackathon/jphacks2020/php_apis/device/edit/assign', json=payload
        )
        print(res.text)
        # String -> dict 変換
        res_dict = ast.literal_eval(res.text)
        # ハッシュセット
        self.hash = res_dict["hash"]

        # dbのhash更新
        us = UserService()
        user = us.find(self.user_id)
        user.token = res_dict["hash"]
        us.update(user)

        return res_dict

    def list_all(self):
        payload = \
            {
                "device_id": self.device_id,
                "user_id": self.user_id,
                "limit_num": 0,
                "limit_day": 0,
                "hash": self.hash
             }

        res = requests.post(
            'http://kn46itblog.xsrv.jp/hackathon/jphacks2020/php_apis/bath/show/list', json=payload
        )
        print(res.text)
        res_dict = ast.literal_eval(res.text)
        return res_dict

    def unassign(self):
        payload = \
            {
                "device_id": self.device_id,
                "user_id": self.user_id,
                "hash": self.hash
             }

        res = requests.post(
            'http://kn46itblog.xsrv.jp/hackathon/jphacks2020/php_apis/device/edit/unassign', json=payload
        )
        print(res.text)
        res_dict = ast.literal_eval(res.text)
        return res_dict

    def fast_list(self):
        user = self.check_user()
        if user is None:
            return {"status": 400, "message": "指定のユーザは存在しませんでした"}

        # device_connection = self.dummy()
        # if device_connection["status"] == 400:
        #     return device_connection
        #
        # assign_data = self.assign()
        # if assign_data["status"] == 400:
        #     return assign_data

        result = self.list_all()
        if result["status"] == 400:
            return result
        # unassign_data = self.unassign()
        # if unassign_data["status"] == 400:
        #     return unassign_data
        # result = '{"status":200,"grandma_list":[{"checkin_time":"20201102202200","checkout":"0","bath_time":"10"},{"checkin_time":"20201101192500","checkout":"1","bath_time":"20"},{"checkin_time":"20201031192200","checkout":"1","bath_time":"20"},{"checkin_time":"20201030195000","checkout":"1","bath_time":"23"},{"checkin_time":"20201029193000","checkout":"1","bath_time":"10"},{"checkin_time":"20201028192200","checkout":"1","bath_time":"15"},{"checkin_time":"20201027201000","checkout":"1","bath_time":"22"},{"checkin_time":"20201026191200","checkout":"1","bath_time":"13"}],"gramdpa_list":[],"message":"入浴情報一覧の取得に成功しました."}'
        # result_dict = ast.literal_eval(result)
        return result
