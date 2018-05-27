#!bin/python
# -*- coding: utf-8 -*-
"""
author: Andrei Bastos
organization: Engenharia Elétrica/Ufes
data: 23/05/2018
describe: model of flow_power 
"""
import os, subprocess, datetime, hashlib, shutil

COMMAND_AMPL = "./solve_fpo_ampl.sh"

class PowerFlow():
    directory = "tmp"
    power_flow = []

    # init object
    def __init__(self, lines, buses):
        self.lines = lines
        self.buses = buses

    def calcule(self):
        try:
            directory_temp = "tmp"
            self.directory = os.path.join(directory_temp,str(hashlib.new('ripemd160',str(self.lines)+str(self.buses)).hexdigest())) 
            try:
                os.mkdir(directory_temp)
            except:
                pass

            try:    
                os.mkdir(self.directory)
                name = "linha.csv"
                name = os.path.join(self.directory,name)
                save_file(name, self.lines)

                name = "barra.csv"
                name = os.path.join(self.directory,name)
                save_file(name, self.buses)

                self.execute_ampl()
            except:
                pass

            self.load_file()
            # self.remove_temps()
        except Exception as error:
            print error

        return self.power_flow

    def remove_temps(self):
        try:
            if (os.path.exists(self.directory)):
                shutil.rmtree(self.directory, ignore_errors=True)
        except Exception as error:
            print error

    def execute_ampl(self):
        process = subprocess.Popen( [COMMAND_AMPL, self.directory])
        output, error = process.communicate()
        # print output, error

    def load_file(self):
        path_fluxo = os.path.join(self.directory, "fluxo.csv")
        if os.path.exists(path_fluxo):
            with open(path_fluxo, 'r') as f:
                
                self.power_flow = [  x.strip().split(",") for x in f.readlines()]
                
                for line in self.power_flow:
                    for column in line:
                        column = column.decode("utf-8").encode("utf-8")

                               

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

