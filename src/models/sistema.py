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

    def exportar(self, filename):                
        pass
    
    def exportar_barras(self, filename):                
        pass
    
    def importar_sistema(self, filename_barra, filename_linha):
        try:
            self.Barras = self.importar_barras(filename_barra)
            self.Linhas = self.importar_linhas(filename_linha)

        except Exception as identifier:
            print identifier

    def exportar_linhas(self, filename):                
        pass

    def importar_barras(self, filename):
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
    
    def importar_linhas(self, filename):                
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
    
    def calcular_fluxo_potencia(self):
        pass
    
    def calcular_curto_circuito(self):
        pass

    #transformação para dicionário
    def to_dict(self):
        return {"barras":[x.to_dict() for x in self.Barras],"linhas":[x.to_dict() for x in self.Linhas]}
    
    def to_json(self):
        return json.dumps(self.to_dict(), indent=4, sort_keys=True)
        

class FluxoPotencia(mongoengine.Document):
    pass

class CurtoCircuito(mongoengine.Document):
    pass
