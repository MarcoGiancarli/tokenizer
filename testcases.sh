#!/bin/bash
self=$(<tokenizer.c)
test_case_1=$(<test_case_1.txt)
test_case_2=$(<test_case_2.txt)

case "$1" in
        self)
            ./tokenizer "$self"
            ;;
        1)
            ./tokenizer "$test_case_1"
            ;;
        2)
            ./tokenizer "$test_case_2"
            ;;
esac

