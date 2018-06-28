#!bin/python
# -*- coding: utf-8 -*-
"""
author: Andrei Bastos
organization: Engenharia Elétrica/Ufes
data: 23/05/2018
describe: model of flow_power 
"""
import os
import subprocess
import datetime
import hashlib
import shutil

COMMAND_AMPL = "./FPO.sh"


class PowerFlow():
    directory = "tmp"
    results = []

    # init object
    def __init__(self, lines, buses):
        self.lines = lines
        self.buses = buses

    def calcule(self):
        try:
            directory_temp = "tmp"
            self.directory = os.path.join(directory_temp, str(hashlib.new(
                'ripemd160', str(self.lines)+str(self.buses)).hexdigest()))
            try:
                os.mkdir(directory_temp)
            except:
                pass

            try:
                os.mkdir(self.directory)
            except:
                pass

            name = os.path.join(self.directory, "linha.csv")
            save_file(name, self.lines)

            name = os.path.join(self.directory, "barra.csv")
            save_file(name, self.buses)

            self.execute_ampl()

            self.load_files()
            self.remove_temps()
        except Exception as error:
            print error

        return self.results

    def remove_temps(self):
        try:
            if (os.path.exists(self.directory)):
                shutil.rmtree(self.directory, ignore_errors=True)
        except Exception as error:
            print error

    def execute_ampl(self):
        process = subprocess.Popen([COMMAND_AMPL, self.directory])
        output, error = process.communicate()
        # print output, error

    def load_files(self):
        path_flow = os.path.join(self.directory, "fluxo.csv")
        path_susceptance = os.path.join(self.directory, "sus.txt")
        path_column = os.path.join(self.directory, "coluna.txt")
        path_line = os.path.join(self.directory, "linha.txt")
        self.results = {
            "power_flow": load_file(path_flow),
            "susceptance": load_file(path_susceptance),
            "lines": load_file(path_column),
            "columns":load_file(path_line),
         }

def load_file(filename):
    file_loaded = []
    if os.path.exists(filename):
        with open(filename, 'r') as f:
            file_loaded = [x.strip().split(",") for x in f.readlines()]
            for line in file_loaded:
                for column in line:
                    column = column.decode("utf-8").encode("utf-8")
    return file_loaded


def save_file(name, lines):
    try:
        with open(name, 'w') as f:
            index = 0
            for line in lines:
                line_str = ""
                for column in line:
                    if type(column) is not unicode:
                        column = str(column)
                    else:
                        column = column.encode('utf-8')
                    line_str += column + ","

                line_str = line_str.strip(',')
                if index < len(lines) - 1:
                    line_str += "\n"

                f.write(line_str)

                index += 1

    except Exception as error:
        print error
