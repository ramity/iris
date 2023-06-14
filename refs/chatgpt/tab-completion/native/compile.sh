#!/bin/bash

TGT="./refs/chatgpt/tab-completion/native/main.cpp"
OUT="./bin/chatgpt-tab-completion-native"
g++ $TGT -o $OUT
$OUT
rm $OUT
