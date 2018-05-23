#!bin/python
# -*- coding: utf-8 -*-
"""
author: Andrei Bastos
organization: Engenharia Elétrica/Ufes
data: 23/05/2018
describe: model of flow_power 
"""


class PowerFlow():
    # init object
    def __init__(self, lines, buses):
        self.lines = lines
        self.buses = buses
    
    def calcule(self):
        flow = [["potencia","r"], [1, 4]]
        print(self.lines)
        print(self.buses)

        return flow
