#!bin/python
# -*- coding: utf-8 -*-
"""
author: Andrei Bastos
organization: Engenharia Elétrica/Ufes
data: 18/03/2018
"""

###################### Importações de Pacotes ##########################
from flask import Flask, jsonify, abort, request, url_for,  make_response, redirect, send_from_directory
import datetime, json, re, os, mongoengine

######################### Configurações ##################################
PESEP_CORE_FOLDER = os.environ.get('PESEP_CORE_FOLDER','~/PESEP/core/')  
app = Flask(__name__)
app.debug = True
app.threaded=True
app.config['MAX_CONTENT_LENGTH'] = 5 * 1024 * 1024 #limitação de 5 MB de arquivo de upload
app.config['SECRET_KEY'] = 'super-secret'

# Caminhos das rotas
route_default = "/api/"
route_default_calcules = route_default + "calcule"
route_default_user = route_default + "user"
ALLOWED_EXTENSIONS = set(['txt','csv','json', 'png', 'jpg', 'jpeg'])

####################### Funções comuns #######################################
def datetime_to_timestamp(dt):    
    timestamp = (dt - datetime.datetime(1970, 1, 1)).total_seconds()    
    return int(timestamp)
def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

####################### Classes #############################################
class InvalidUsage(Exception):
    status_code = 400 #codigo padrão

    def __init__(self, message_error, status_code=None, payload=None):
        Exception.__init__(self)
        self.message_error = message_error
        if status_code is not None:
            self.status_code = status_code
        self.payload = payload

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
