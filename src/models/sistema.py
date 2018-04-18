#!bin/python
# -*- coding: utf-8 -*-
"""
author: Andrei Bastos
organization: Engenharia Elétrica/Ufes
data: 17/04/2018
describe: model of line
"""

import mongoengine, linha, csv, os
from barra import Barra
from linha import Linha 

class Sistema(mongoengine.Document):
    Barras = mongoengine.ListField(Barra)
    Linhas = mongoengine.ListField(Linha)

    def exportar(self, filename):                
        pass
    
    def exportar_barras(self, filename):                
        pass
    
    def exportar_linhas(self, filename):                
        pass

    def importar_barras(self, filename):
        try:
            with open(filename, 'rb') as csvfile:
                barras_reader = csv.reader(csvfile, delimiter=',')
                index=0
                for row in barras_reader:
                    if index >0:
                        barra = Barra.load_row(row)                                               
                    index=+1
                    

        except Exception as identifier:
            print identifier                
    
    def importar_linhas(self, filename):                
        pass
    
    def calcular_fluxo_potencia(self):
        pass
    
    def calcular_curto_circuito(self):
        pass


class FluxoPotencia(mongoengine.Document):
    pass

class CurtoCircuito(mongoengine.Document):
    pass
