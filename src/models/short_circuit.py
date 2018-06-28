#!bin/python
# -*- coding: utf-8 -*-
"""
author: Andrei Bastos
organization: Engenharia Elétrica/Ufes
data: 28/06/2018
describe: model of short_circuit
"""
import os
import subprocess
import datetime

# comandos
COMMAND_COMPILE = "g++ ./math/CC/CC.cpp -o ../dist/CC"
COMMAND_CC = "./CC.sh"


def compile_CC():
    try:
        os.mkdir("../dist")
    except:
        pass

    process = subprocess.Popen([COMMAND_COMPILE], shell=True)
    output, error = process.communicate()

class ShortCircuit():
    directory = "tmp"
    results = []


