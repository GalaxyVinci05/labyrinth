#!/usr/bin/env bash

gcc src/main.c src/robot.c src/stanza.c src/ostacolo.c -o main
./main
