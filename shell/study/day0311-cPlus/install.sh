#!/bin/bash
g++ ./sources/*.cpp -I./headers -o ./bin/person

chmod 777 ./bin/person

./bin/person