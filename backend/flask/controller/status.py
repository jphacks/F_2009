from flask import Blueprint, request
from flask_restful import Resource, Api


app = Blueprint('status', __name__)
api = Api(app)

class Status(Resource):
    def get(self):
        body = {
            "status": True,
            "entry_time": "2020-11-01 10:45:34 +09:00"
        }
        return body


api.add_resource(Status, '/status')
