#!/bin/bash
# $1: phrase to find
# $2: phrase to replace $1
if [ "$1" = "" -o "$2" = "" ]; then
	echo "Usage: replace.sh [PHRASE TO FIND] [PHRASE TO REPLACE PHRASE TO FIND]"
	exit 1
fi

git grep -w "$1" src asm include >/dev/null
if [ "$?" -ne 0 ]; then
	echo "error: query symbol not found"
	exit 1
fi

git grep -w "$2" src asm include >/dev/null
if [ "$?" -eq 0 ]; then
	echo "error: replacement symbol already exists"
	exit 1
fi

set -e

if [ "$(uname -s)" == "Darwin" ]; then
	SED="$(which gsed)"
else
	SED="$(which sed)"
fi

${SED} -i 's/\<'"$1"'\>/'"$2"'/g' $(git grep -Ilwr "$1")
