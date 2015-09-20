#!/bin/bash
self=$(<tokenizer.c)
test_case_1=$(<tests/test_case_1.txt)
test_case_2=$(<tests/test_case_2.txt)
test_case_3=$(<tests/test_case_3.txt)

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
        3)
            ./tokenizer "$test_case_3"
            ;;
esac

