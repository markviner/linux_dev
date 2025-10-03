#!/bin/bash

if [[ -z "$BASH_VERSION" ]]; then
    echo "This script works with Bash only!!" >&2
    exit 1
fi

set -e

main() {
    local delay="${1:-0}"
    local lines=() i j char
    
    while IFS= read -r line; do
        lines+=("${line//$'\t'/    }")
    done

    if [[ ${#lines[@]} -eq 0 ]]; then
        exit 0
    fi

    # find the max str len
    local max_len=0
    for line in "${lines[@]}"; do
        (( ${#line} > max_len )) && max_len=${#line}
    done

    local temp_file
    temp_file=$(mktemp)
    trap 'rm -f "$temp_file"' EXIT

    ## temp store array of symbls
    for ((i=0; i<${#lines[@]}; i++)); do
        local line="${lines[i]}"
        for ((j=0; j<max_len; j++)); do
            if [[ j -lt ${#line} ]]; then
                char="${line:j:1}"
            else
                char=" "
            fi
            printf "%d\t%d\t%c\n" "$i" "$j" "$char"
        done
    done > "$temp_file"

    # output
    tput clear
    shuf "$temp_file" | while IFS=$'\t' read -r i j char; do
        tput cup "$i" "$j"
        echo -n "$char"
        if (( $(echo "$delay > 0" | bc -l 2>/dev/null) )); then
            sleep "$delay"
        fi
    done

    tput cup "${#lines[@]}" 0
}

main "$@"
