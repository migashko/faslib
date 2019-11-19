#!/bin/bash

scriptdir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
prjdir=${PWD}
prjname="$(basename ${prjdir})"

echo "Это пользовательский скрипт перед публикацией на github:"

rm -f gitlab-ci.yml
rm -f wamba-ci.yml
rm -rf "${prjdir}/.ci"
