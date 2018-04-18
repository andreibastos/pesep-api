#!bin/python
# -*- coding: utf-8 -*-
"""
author: Andrei Bastos
organization: Engenharia Elétrica/Ufes
data: 12/03/2018
describe: model of Barra 
"""

import mongoengine, json

class Barra(mongoengine.Document):
    #cabeçário da barra
    HEADER = ['Item', 'Tipo', 'Nome', 'Tensão0', 'Angulo0','Pgerada', 'Qgerada', 'Qmínimo', 'Qmáxima', 'Pcarga', 'Qcarga', 'Pgeradamín', 'Pgeradamáx', 'Qshunt']

    #atributos do csv
    Item = mongoengine.IntField(required=True) #Item
    Tipo = mongoengine.IntField(required=True, default=0) #Tipo
    Nome = mongoengine.StringField(default="Barra {0}".format(Item))           #Nome
    Tensao0 = mongoengine.DecimalField(default=1.0) #Tensão0
    Angulo0 = mongoengine.DecimalField(default=0.0) #Angulo0
    Pgerada = mongoengine.DecimalField() #Pgerada
    Qgerada = mongoengine.DecimalField() #Qgerada    
    Qminimo = mongoengine.DecimalField() #Qmínimo
    Qmaximo = mongoengine.DecimalField() #Qmáximo
    Pcarga = mongoengine.DecimalField() #Pcarga
    Qcarga = mongoengine.DecimalField() #Qcarga
    Pgeradamin = mongoengine.DecimalField() #Pgeradamín
    Pgeradamax = mongoengine.DecimalField() #Pgeradamáx    
    Qshunt = mongoengine.DecimalField() #Qshunt

    # inicialização do objeto
    def __init__(self, Item=None, Tipo=None, *args, **kwargs):
        super(mongoengine.Document, self).__init__(*args, **kwargs)

    #transformação para dicionário
    def to_dict(self):
        Barra = {
            'Item':self.Item,
            'Tipo': self.Tipo,
            'Nome':self.Nome,
            'Tensão0':self.Tensao0,
            'Angulo0':self.Angulo0,
            'Pgerada':self.Pgerada,
            'Qgerada':self.Qgerada,
            'Qmínimo':self.Qminimo,
            'Qmáximo':self.Qmaximo,
            'Pcarga': self.Pcarga,
            'Qcarga':self.Qcarga,
            'Pgeradamín':self.Pgeradamin,
            'Pgeradamáx':self.Pgeradamax,
            'Qshunt':self.Qshunt
            }
        return Barra

    #transformação para json 
    def to_json(self):
        return json.dumps(self.to_dict(), indent=4, sort_keys=True)
    
    #carrega a partir de uma string em json
    @classmethod
    def load_json(cls,json_string):
        return cls.load_dict(json.loads(json_string))

    #carrega a partir de um dict
    @staticmethod
    def load_dict(obj_loaded):
        try:
            barra = Barra()
            barra.Item = obj_loaded.get('Item')
            barra.Tipo = obj_loaded.get('Tipo')
            barra.Nome = obj_loaded.get('Nome')
            barra.Tensao0 = obj_loaded.get('Tensao0')
            barra.Angulo0 = obj_loaded.get('Angulo0')
            barra.Pgerada = obj_loaded.get('Pgerada')
            barra.Qgerada = obj_loaded.get('Qgerada')
            barra.Qminimo = obj_loaded.get('Qminimo')
            barra.Pcarga = obj_loaded.get('Pcarga')
            barra.Qcarga = obj_loaded.get('Qcarga')
            barra.Pgeradamin = obj_loaded.get('Pgeradamin')
            barra.Pgeradamax = obj_loaded.get('Pgeradamax')
            barra.Qshunt = obj_loaded.get('Qshunt')
            return barra
        except Exception as identifier:
            print(identifier)

    #carrega a partir de uma row
    @staticmethod
    def load_row(row):
        try:
            barra = Barra()
            barra.Item = int(row[0])  
            barra.Tipo = int(row[1])
            barra.Nome = str(row[2]) 
            barra.Tensao0 = float(row[3])
            barra.Angulo0 = float(row[4])            
            barra.Pgerada = float(row[5])
            barra.Qgerada = float(row[6])
            barra.Qminimo = float(row[7])
            barra.Qmaximo = float(row[8])
            barra.Pcarga = float(row[9])
            barra.Qcarga = float(row[10])
            barra.Pgeradamin = float(row[11])
            barra.Pgeradamax = float(row[12])
            barra.Qshunt = float(row[13])
            print barra.to_json() 
            return barra
        except Exception as identifier:
            print identifier

    #cabeçário
    def header(self, delimiter=','):
        return "{0}".format(delimiter).join(x for x in self.HEADER)

    def check(self):
        pass