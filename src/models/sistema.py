#!bin/python
# -*- coding: utf-8 -*-
"""
author: Andrei Bastos
organization: Engenharia Elétrica/Ufes
data: 17/04/2018
describe: model of line
"""

import csv
import os

import mongoengine, json 

from barra import Barra
from linha import Linha


class Sistema(mongoengine.Document):
    Barras = mongoengine.ListField(Barra)
    Linhas = mongoengine.ListField(Linha)

    #Importações
    def ImportarSistema(self, filename_barra, filename_linha):
        try:
            self.Barras = self.ImportarBarras(filename_barra)
            self.Linhas = self.ImportarLinhas(filename_linha)

        except Exception as identifier:
            print identifier
    
    def ImportarBarras(self, filename):
        try:
            barras = []
            with open(filename, 'rb') as csvfile:
                barras_reader = csv.reader(csvfile, delimiter=',')
                index=0
                for row in barras_reader:
                    if index >0:
                        barra = Barra.load_row(row)
                        barras.append(barra)
                    index=+1
            return barras

        except Exception as identifier:
            print identifier                
                       
    def ImportarLinhas(self, filename):                
        try:
            linhas = []
            with open(filename, 'rb') as csvfile:
                linhas_reader = csv.reader(csvfile, delimiter=',')
                index=0
                for row in linhas_reader:
                    if index >0:
                        linha = Linha.load_row(row)
                        linhas.append(linha)
                    index=+1
            return linhas

        except Exception as identifier:
            print identifier
    
    
    #Exportações
    def ExportarBarras(self, filename):                
        pass
    
    def ExportarLinhas(self, filename):                
        pass
    
    def ExportarSistema(self, filename):
        pass
    
    def CalcularFluxoPotencia(self):
        try:
            fluxoPotencia = FluxoPotencia(Sistema=self)
            fluxoPotencias = fluxoPotencia.calcular()
            return fluxoPotencias
        except Exception as identifier:
            print identifier
    
    def CalcularCurtoCircuito(self):
        pass

    #transformação para dicionário
    def to_dict(self):
        return {"barras":[x.to_dict() for x in self.Barras],"linhas":[x.to_dict() for x in self.Linhas]}
    
    def to_json(self):
        return json.dumps(self.to_dict(), indent=4, sort_keys=True)


class FluxoPotencia(mongoengine.Document):

    HEADER = ['Barra', 'Nome', 'Tensão', 'Angulo', 'Pgerada', 'Qgerada', 'Pcarga', 'Qcarga','Para', 'P_fluxo', 'Q_fluxo'  ]

    Barra = mongoengine.IntField()
    Nome = mongoengine.StringField()
    Tensao = mongoengine.DecimalField()
    Angulo = mongoengine.DecimalField()
    Pgerada = mongoengine.DecimalField()
    Qgerada = mongoengine.DecimalField()
    Pcarga = mongoengine.DecimalField()
    Qcarga = mongoengine.DecimalField()
    Para = mongoengine.DecimalField()
    P_fluxo = mongoengine.DecimalField()
    Q_fluxo = mongoengine.DecimalField()

    Sistema = mongoengine.ReferenceField(Sistema)

       # inicialização do objeto
    def __init__(self, Sistema=None ,*args, **kwargs):        
        super(mongoengine.Document, self).__init__(*args, **kwargs)
        self.Sistema = Sistema

     #transformação para dicionário
    def to_dict(self):
        fluxoPotencia = {
            'Barra':self.Barra,
            'Nome': self.Nome,
            'Tensao':self.Tensao,
            'Angulo':self.Angulo,
            'Pgerada':self.Pgerada,
            'Qgerada':self.Qgerada,
            'Pcarga':self.Pcarga,           
            'Qcarga':self.Qcarga,          
            'Para':self.Para,        
            'P_fluxo':self.P_fluxo,           
            'Q_fluxo':self.Q_fluxo          
            }
        return fluxoPotencia
    
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
            fluxoPotencia = FluxoPotencia()
            fluxoPotencia.Barra = obj_loaded.get('Barra')
            fluxoPotencia.Nome = obj_loaded.get('Nome')
            fluxoPotencia.Tensao = obj_loaded.get('Tensao')
            fluxoPotencia.Angulo = obj_loaded.get('Angulo')
            fluxoPotencia.Pgerada = obj_loaded.get('Pgerada')
            fluxoPotencia.Qgerada = obj_loaded.get('Qgerada')
            fluxoPotencia.Pcarga = obj_loaded.get('Pcarga')
            fluxoPotencia.Qcarga = obj_loaded.get('Qcarga')
            fluxoPotencia.Para = obj_loaded.get('Para')
            fluxoPotencia.P_fluxo = obj_loaded.get('P_fluxo')
            fluxoPotencia.Q_fluxo = obj_loaded.get('Q_fluxo')
            return fluxoPotencia

        except Exception as identifier:
            print(identifier)

    @staticmethod
    def load_row(row):
        try:
            fluxoPotencia = FluxoPotencia()
            fluxoPotencia.Barra = int(row[0]) if (row[0]) != '' else  None
            fluxoPotencia.Nome = str(row[1]) if (row[1]) != '' else  None
            fluxoPotencia.Tensao = float(row[2]) if (row[2]) != '' else  None
            fluxoPotencia.Angulo = float(row[3]) if (row[3]) != '' else  None
            fluxoPotencia.Pgerada = float(row[4]) if (row[4]) != '' else  None
            fluxoPotencia.Qgerada = float(row[5]) if (row[5]) != '' else  None
            fluxoPotencia.Pcarga = float(row[6]) if (row[6]) != '' else  None
            fluxoPotencia.Qcarga = float(row[7]) if (row[7]) != '' else  None
            fluxoPotencia.Para = float(row[8]) if (row[8]) != '' else  None
            fluxoPotencia.P_fluxo = float(row[9]) if (row[9]) != '' else  None
            fluxoPotencia.Q_fluxo = float(row[10]) if (row[10]) != '' else  None
            return fluxoPotencia
        except Exception as identifier:
            print identifier

    #cabeçário
    def header(self, delimiter=','):
        return "{0}".format(delimiter).join(x for x in self.HEADER)

    def check(self):
        pass

    def ImportarFluxoPotencia(self, filename):
        try:
            fluxos = []
            with open(filename, 'rb') as csvfile:
                fluxos_reader = csv.reader(csvfile, delimiter=',')
                index=0
                for row in fluxos_reader:
                    if index >0:
                        fluxoPotencia = FluxoPotencia.load_row(row)
                        fluxos.append(fluxoPotencia)
                    index=+1
            return fluxos

        except Exception as identifier:
            print identifier

    
    def calcular(self):
        try:
            if self.Sistema:
                filename_fluxo = '../test/models/fluxo.csv'
                print filename_fluxo
                
                return self.ImportarFluxoPotencia(filename_fluxo)
            else:
                raise Exception
            
        except Exception as identifier:
            print identifier
        
              

class CurtoCircuito(mongoengine.Document):
    pass
