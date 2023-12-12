#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
RESET='\033[0m'
BOLD='\033[1m'

FILES="mappies/parser_test/*"
for file in $FILES
do
	echo -e "$GREEN\n\n\nTesting file $file\n\n\n$RESET"
	./cub3D $file
done