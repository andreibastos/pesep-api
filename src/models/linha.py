#!bin/python
# -*- coding: utf-8 -*-
"""
author: Andrei Bastos
organization: Engenharia Elétrica/Ufes
data: 12/03/2018
describe: model of linha
"""

import mongoengine, json

class Linha(mongoengine.Document):
    #cabeçário da linha    
    HEADER = ['Item', 'fbus', 'tbus', 'r', 'x', 'Tap', 'A']

    #atributos do csv
    Item = mongoengine.IntField(required=True) 
    Fbus = mongoengine.IntField(required=True) 
    Tbus = mongoengine.StringField(required=True)
    r = mongoengine.DecimalField(required=True, default = 1) 
    x = mongoengine.DecimalField(required=True, default = 1) 
    Tap = mongoengine.DecimalField(required=True, default = 1) 
    A = mongoengine.DecimalField(required=True, default = 0) 

    # inicialização do objeto
    def __init__(self, Item=None, *args, **kwargs):
        super(mongoengine.Document, self).__init__(*args, **kwargs)

    #transformação para dicionário
    def to_dict(self):
        linha = {
            'Item':self.Item,
            'fbus': self.Fbus,
            'tbus':self.Tbus,
            'r':self.r,
            'x':self.x,
            'Tap':self.Tap,
            'A':self.A            
            }
        return linha
    
    #transformação para json 
    def to_json(self):
        return json.dumps(self.to_dict())

    #carrega a partir de uma string em json
    @classmethod
    def load_json(cls, json_string):
        return cls.load_dict(json.loads(json_string))

    #carrega a partir de um dict
    @staticmethod
    def load_dict(obj_loaded):
        try:            
            linha = Linha()
            linha.Item = obj_loaded.get('Item')
            linha.Fbus = obj_loaded.get('Fbus')
            linha.Tbus = obj_loaded.get('Tbus')
            linha.r = obj_loaded.get('r')
            linha.x = obj_loaded.get('x')
            linha.Tap = obj_loaded.get('Tap')
            linha.A = obj_loaded.get('A')
            return linha

        except Exception as identifier:
            print(identifier)

    @staticmethod
    def load_row(row):
        try:
            linha = Linha()
            
            linha.Item = int(row[0]) 
            linha.Fbus = float(row[1])
            linha.Tbus = float(row[2])
            linha.r = float(row[3])
            linha.x = float(row[4])
            linha.Tap = float(row[5])
            linha.A = float(row[6])
            
            print linha.to_json() 
            return linha
        except Exception as identifier:
            print identifier

    #cabeçário
    def header(self, delimiter=','):
        return "{0}".format(delimiter).join(x for x in self.HEADER)

    def check(self):
        pass