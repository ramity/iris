#!/bin/bash

# Completion function for my_script.sh
_my_script_completion() {
    local cur_word args

    # Current word being completed
    cur_word="${COMP_WORDS[COMP_CWORD]}"

    # Previous arguments passed to my_script.sh
    args="${COMP_WORDS[*]:1:$COMP_CWORD}"

    # Generate completion options based on the arguments and current word
    # Replace the dummy suggestions with your own completion logic
    completions="foo bar baz"

    # Use compgen to generate completions
    COMPREPLY=($(compgen -W "$completions" -- "$cur_word"))
}

# Register completion function for my_script.sh
complete -F _my_script_completion my_script.sh

# Rest of your script here...
