#!/bin/bash
SRC=$(find src -name '*.cpp' -not -name 'main.cpp')
TEST=$(find test -name '*.cpp')
c++ -glldb -std=c++17 -Isrc -Itest -o run-test $TEST $SRC && ./run-test
