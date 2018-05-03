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
            return fluxoPotencia.calcular()
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

    barras = []

    rede = []

    
    Sistema = mongoengine.ReferenceField(Sistema)

       # inicialização do objeto
    def __init__(self, Sistema=None ,*args, **kwargs):        
        super(mongoengine.Document, self).__init__(*args, **kwargs)
        self.Sistema = Sistema

    #transformação para dicionário
    def to_dict(self):
        fluxoPotencia = { 
            "barras":self.barras,
            "rede":self.rede       
            }
        return fluxoPotencia
    
    #transformação para json 
    def to_json(self):
        return json.dumps(self.to_dict(), indent=4, sort_keys=True)
    
    def to_csv(self):
        pass

    #carrega a partir de uma string em json
    @classmethod
    def load_json(cls, json_string):
        return cls.load_dict(json.loads(json_string))

    #carrega a partir de um dict
    @staticmethod
    def load_dict(obj_loaded):
        try:            
            fluxoPotencia = FluxoPotencia()            
            return fluxoPotencia

        except Exception as identifier:
            print(identifier)

    @staticmethod
    def load_row(row):
        try:
            pass            
        except Exception as identifier:
            print identifier

    #cabeçário
    def header(self, delimiter=','):
        return "{0}".format(delimiter).join(x for x in self.HEADER)

    def check(self):
        pass

    def ImportarFluxoPotencia(self, filename):
        try:
            fluxoPotencia = None
            fluxoPotencia = FluxoPotencia()           
                       

            with open(filename, 'r') as csvfile:
                fluxos_reader = csv.reader(csvfile, delimiter=',')
                index=0
                for row in fluxos_reader:
                    if index >0:
                        if row[0] != '':
                            barra = {}
                            barra["item"] = int(row[0])
                            barra["nome"] = row[1]
                            barra["tensao"] = float(row[2])
                            barra["angulo"] = float(row[3])
                            barra["Pgerada"] = float(row[4])
                            barra["Qgerada"] = float(row[5])
                            barra["Pcarga"] = float(row[6])
                            barra["Qcarga"] = float(row[7])
                            fluxoPotencia.barras.append(barra)
                            no = {}
                            no["de"] = barra["item"]
                        else:
                            no["para"] = int(row[8])
                            no["P_Fluxo"] = float(row[9])
                            no["Q_Fluxo"] = float(row[10])
                            fluxoPotencia.rede.append(no)
                            no = {}
                            no["de"] = barra["item"]
                
                    index=+1
            return fluxoPotencia

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
