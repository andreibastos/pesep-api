#!bin/python
# -*- coding: utf-8 -*-
"""
author: Andrei Bastos
organization: Engenharia Elétrica/Ufes
data: 18/02/2018
describe: main code 
"""

###################### Importações de Pacotes ##########################
from flask import Response, Flask, jsonify, abort, request, url_for,  make_response, redirect, send_from_directory
from flask_cors import CORS
import datetime
import json
import re
import os

from controllers.SystemEletricPower import calcule, compile_CC

######################### Configurações ##################################
app = Flask(__name__)
app.debug = True
app.threaded = True
app.config['SECRET_KEY'] = 'super-secret'


# Caminhos das rotas
route_default = "/"
route_default_calcules = route_default + "calcule"
route_default_config = route_default + "config"
cors = CORS(app, resources={"/*": {"origins": "*"}})


####################### Funções comuns #######################################
def datetime_to_timestamp(dt):
    timestamp = (dt - datetime.datetime(1970, 1, 1)).total_seconds()
    return int(timestamp)


def get_response_data(request):
    try:
        if request.method == 'POST':
            if request.headers['Content-Type'] == 'application/json':
                try:
                    return request.json
                except Exception as identifier:
                    raise InvalidUsage(identifier.message)
    except Exception as identifier:
        raise InvalidUsage(identifier.message)

####################### Classes #############################################


class InvalidUsage(Exception):
    status_code = 400  # codigo padrão de erro

    def __init__(self, message_error, status_code=None, payload=None):
        Exception.__init__(self)
        self.message_error = message_error
        if status_code is not None:
            self.status_code = status_code
        self.payload = payload
        print(self.to_dict())

    def to_dict(self):
        rv = dict(self.payload or ())
        rv['error'] = True
        rv['code'] = self.status_code
        rv['message_error'] = self.message_error
        return rv

######################## Erros ###############################################


@app.errorhandler(404)
def page_not_found(e):
    return Response(json.dumps({'message_error': 'not exist.  please usage: /calcule/power_flower or /calcule/short_circuit ', 'code': 404, 'error': True}), status=404,
                    mimetype='application/json')


@app.errorhandler(InvalidUsage)
def handle_invalid_usage(error):
    return Response(json.dumps(error.to_dict()), status=200,
                    mimetype='application/json')

######################## Rotas ###############################################
# Fluxo de Potência


@app.route(route_default_calcules+"/power_flow", methods=['POST', 'GET'])
def power_flow():
    data = get_response_data(request)
    if (data):
        inputs = []
        print(data)
        files = ['barra.csv', 'linha.csv']
        for filename in files:
            inputs.append({
                'filename': filename,
                'data': data[filename]
            })
        flow = calcule('power_flow', inputs)

        resp = Response(json.dumps(flow), status=200,
                        mimetype='application/json')
        return resp
    else:
        raise InvalidUsage('not find files')


# Curto Circuito


@app.route(route_default_calcules+"/short_circuit", methods=['POST', 'GET'])
def short_circuit():
    data = get_response_data(request)
    if (data):
        try:
            inputs = []
            files = ['barra.csv', 'linha.csv', 'entrada_falta.txt']
            for filename in files:
                inputs.append({
                    'filename': filename,
                    'data': data[filename]
                })
            short = calcule('short_circuit', inputs)

            resp = Response(json.dumps(short), status=200,
                            mimetype='application/json')
            return resp
        except Exception as error:
            raise InvalidUsage(error.message)
    else:
        raise InvalidUsage('not find files')

# Configurações


@app.route(route_default_config + "/headers")
def get_headers():
    f = open('./config/headers_files.json', 'r')
    HEADERS = json.load(f)
    resp = Response(json.dumps(HEADERS), status=200,
                    mimetype='application/json')
    f.close()
    return resp


######################## Função Principal ######################################
if __name__ == '__main__':
    compile_CC()
    app.run(host="0.0.0.0", port=os.environ.get('port', 5000))
