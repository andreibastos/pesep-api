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

from models.power_flow import PowerFlow

######################### Configurações ##################################
app = Flask(__name__)
app.debug = True
app.threaded = True
app.config['SECRET_KEY'] = 'super-secret'


# Caminhos das rotas
route_default = "/"
route_default_calcules = route_default + "calcule"
route_default_config = route_default + "config"
cors = CORS(app, resources={route_default_calcules+"/*": {"origins": "*"}})


####################### Funções comuns #######################################
def datetime_to_timestamp(dt):
    timestamp = (dt - datetime.datetime(1970, 1, 1)).total_seconds()
    return int(timestamp)

####################### Classes #############################################


class InvalidUsage(Exception):
    status_code = 400  # codigo padrão de erro

    def __init__(self, message_error, status_code=None, payload=None):
        Exception.__init__(self)
        self.message_error = message_error
        if status_code is not None:
            self.status_code = status_code
        self.payload = payload
        print(message_error)

    def to_dict(self):
        rv = dict(self.payload or ())
        rv['error'] = True
        rv['code'] = self.status_code
        rv['message_error'] = self.message_error
        return rv

######################## Erros ###############################################


@app.errorhandler(InvalidUsage)
def handle_invalid_usage(error):
    response = jsonify(error.to_dict())
    response.status_code = error.status_code
    return response

######################## Rotas ###############################################
########### cálculos #######################################################
# Fluxo de Potência


@app.route(route_default_calcules+"/power_flow", methods=['POST', 'GET'])
def power_flow():
    try:
        if request.method == 'POST':
            if request.headers['Content-Type'] == 'application/json':
                try:
                    bus = request.json["barras"]
                    line = request.json["linhas"]
                    print(bus)
                    print(line)
                    flow = calcule_power_flow(line, bus)
                    resp = Response(json.dumps(flow), status=200,
                                    mimetype='application/json')
                    # resp = Response(json.dumps([]), status=200, mimetype='application/json')
                    return resp

                except Exception as identifier:
                    
                    raise InvalidUsage(identifier.message)

    except Exception as identifier:
        print(identifier)
        raise InvalidUsage(identifier.message)

# Curto Circuito


@app.route(route_default_calcules+"/short", methods=['POST', 'GET'])
def short_circuit():
    try:
        if request.method == 'POST':
            if request.headers['Content-Type'] == 'application/json':
                try:
                    resp = Response(json.dumps(request.json), status=200,
                                    mimetype='application/json')
                    return resp

                except Exception as identifier:
                    raise InvalidUsage(identifier.message)

    except Exception as identifier:
        raise InvalidUsage(identifier.message)

def verify_consistency(lines, buses):
    return True


def calcule_power_flow(lines, buses):
    try:
        results = []
        consistency = verify_consistency(lines, buses)
        if consistency:
            power_flow = PowerFlow(lines, buses)
            power_flow.calcule()
            results = power_flow.results
        return results
    except:
        raise


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
    app.run(host="0.0.0.0", port=os.environ.get('port', 5000))
