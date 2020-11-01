from flask import Blueprint, request
from flask_restful import Resource, Api


app = Blueprint('history', __name__)
api = Api(app)

class HistoryWeek(Resource):
    def get(self):
        body = {
          "history": [
            {
              "date": "2020-10-30",
              "minute": 13
            },
            {
              "date": "2020-10-31",
              "minute": 22
            },
            {
              "date": "2020-11-01",
              "minute": 15
            },
            {
              "date": "2020-11-02",
              "minute": 10
            },
            {
              "date": "2020-11-03",
              "minute": 23
            },
            {
              "date": "2020-11-04",
              "minute": 20
            },
            {
              "date": "2020-11-05",
              "minute": 20
            }
          ],
          "mean": 18
        }
        return body


api.add_resource(HistoryWeek, '/history/week')
