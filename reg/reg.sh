#!/bin/bash

g++ *.cpp
./a.out
python3 better_plot.py
firefox plot_result.html