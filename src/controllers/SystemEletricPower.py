#!bin/python
# -*- coding: utf-8 -*-
"""
author: Andrei Bastos
organization: Engenharia Elétrica/Ufes
data: 28/06/2018
describe: model of short_circuit
"""
import os
import shutil
import subprocess
import datetime
import time
from settings import SRC_DIR

# comandos
COMMAND_COMPILE = SRC_DIR + "compile.sh"
COMMAND_POWER_FLOW = SRC_DIR + "FPO.sh"
COMMAND_SHORT_CIRCUIT = SRC_DIR + "CC.sh"


def calcule(math_method, inputs):
    command = ""
    results = {}
    if (math_method == 'power_flow'):
        command = COMMAND_POWER_FLOW
    else:
        if (math_method == 'short_circuit'):
            command = COMMAND_SHORT_CIRCUIT

    try:
        directory = create_directory(math_method)
        save_files(inputs, directory)
        input_files = os.listdir(directory)
        execute_command(command, directory)
        results = load_files(directory)
        # remove_inputs(results, input_files)
        remove_temps(directory)
    except Exception as e:
        print(e)
        pass

    return results


def create_directory(math_method):
    dir_tmp = SRC_DIR + "/tmp/"
    try:
        os.mkdir(dir_tmp)
    except Exception as e:
        print(e)
        pass

    directory_temp = dir_tmp + math_method
    try:
        os.mkdir(directory_temp)
    except Exception as e:
        print(e)
        pass

    directory = os.path.join(
        directory_temp,
        datetime.datetime.now().strftime('%s'))
    try:
        os.mkdir(directory)
    except Exception as e:
        print(e)
        pass

    return directory


def save_files(inputs, directory):
    for input in inputs:
        filename = os.path.join(directory, input['filename'])
        save_file(filename, input['data'])


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

    except Exception as e:
        print(e)
        pass


def execute_command(command, directory):
    process = subprocess.Popen([command, directory])
    output, error = process.communicate()


def remove_temps(directory):
    try:
        if (os.path.exists(directory)):
            shutil.rmtree(directory, ignore_errors=True)
    except Exception as e:
        print(e)
        pass


def load_files(directory):
    results = {}
    files = os.listdir(directory)
    files = sorted(files)
    for file in files:
        filename = os.path.join(directory, file)
        results[file] = load_file(filename)
    return results


def load_file(filename):
    delimiter = ','
    file_loaded = []
    if os.path.exists(filename):
        with open(filename, 'r') as f:
            lines = f.readlines()
            if (len(lines) > 0):
                first_line = lines[0]
                count_comma = len(first_line.strip().split(","))
                count_space = len(first_line.strip().split(" "))
                if (count_space > count_comma):
                    delimiter = ' '
                file_loaded = [x.strip().split(delimiter) for x in lines]
                for line in file_loaded:
                    for column in line:
                        column = column.decode("utf-8").encode("utf-8")
    return file_loaded


def remove_inputs(results, input_files):
    keys_remove = []
    extension_files = ['.mod', '.dat']
    for result in results:
        if result in input_files:
            keys_remove.append(result)
        for extension in extension_files:
            if extension in result:
                keys_remove.append(result)

    for key in keys_remove:
        results.pop(key, None)
