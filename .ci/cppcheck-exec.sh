#!/bin/bash
script_name=$(realpath $0)
script_dir=$(dirname $script_name)
prj_dir=$(dirname $script_dir)

opt="--inconclusive --error-exitcode=1 --force --max-configs=128 \
--quiet --enable=all --suppress=missingIncludeSystem --suppressions-list=suppressions.txt \
--template='{id}:{file}:{line}:[{severity}]:{message}' --inline-suppr -I $prj_dir"
cppcheck --std=c++11 $opt $@


