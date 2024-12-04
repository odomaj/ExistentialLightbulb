'''
    Made by Alexander Odom for Assignment 1 for CS 447
'''

import os

if(os.path.exists(os.getcwd() + '/../build')):
    os.chdir('../build')
else:
    os.chdir('../')
    os.system('mkdir build')
    os.chdir('build')

dir = os.getcwd()

os.system('g++ -std=c++11 ../src/io/IO.cpp ../src/bulb/BulbConfig.cpp ../src/main.cpp ../src/solver/BulbSolver.cpp ../src/graph/graph.cpp ../src/graph/node.cpp -o bulbsolver')