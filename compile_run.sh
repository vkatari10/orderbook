#! /usr/bin/bash
g++ -Iinclude -std=c++20 -O2 src/orderbook.cpp main.cpp -o main.out 
./main.out