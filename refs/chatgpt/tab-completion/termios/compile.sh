#!/bin/bash

TGT="./refs/chatgpt/tab-completion/termios/main.cpp"
OUT="./bin/chatgpt-tab-completion-termios"
g++ $TGT -o $OUT
$OUT
rm $OUT
