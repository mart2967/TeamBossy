#!/bin/bash

dir=$1



### Counts current directory! ###
DIRECTORIES="$(find $1 -type d| wc -l)"
FILES="$(find $1 -type f | wc -l)"

printf "Processed all the files from  <$dir>
There were $DIRECTORIES directories.
There were $FILES regular files.
"
