TGT="./refs/chatgpt/tab-completion/main.cpp"
OUT="./bin/chatgpt-tab-completion"
g++ $TGT -o $OUT
$OUT
rm $OUT
