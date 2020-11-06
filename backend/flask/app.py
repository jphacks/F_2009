from flask import Flask ,render_template
from flask import Blueprint
from controller import status, history, users
from flask_cors import CORS

from modules.regular_time_check import scheduler
from modules.push_notification import send_alert

app = Flask(__name__)
app.config['JSON_AS_ASCII'] = False
app.config['JSON_SORT_KEYS'] = False
CORS(app, origin=['localhost','jphacks.github.io'], allow_headers=['Content-Type', 'Authorization'],
     methods=['GET', 'POST', 'PUT', 'DELETE'])

app.register_blueprint(status.app, url_prefix = '/api')
app.register_blueprint(history.app, url_prefix = '/api')
app.register_blueprint(users.app, url_prefix = '/api')

# 定期リクエスト開始
scheduler.start()

@app.route('/')
def hello():
    #send_alert()
    return 'Hello world'

@app.route('/.well-known/acme-challenge/<filename>')
def well_known(filename):
    return render_template('.well-known/acme-challenge/'+ filename)



def main():
    app.debug = True

    app.run()

if __name__ == '__main__':
    main()
