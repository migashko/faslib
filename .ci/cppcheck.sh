#!/bin/bash
script_name=$(realpath $0)
script_dir=$(dirname $script_name)
prj_dir=$(dirname $script_dir)

opt="--inconclusive --error-exitcode=1 --force --max-configs=128 \
--quiet --enable=all --suppress=missingIncludeSystem  \
--inline-suppr -I $prj_dir $prj_dir"

cppcheck --std=c++11 --xml-version=2 --suppressions-list="$script_dir"/suppressions-list.txt $opt 
#if [[ -n "$1" ]]; then
  # --xml-version=2 
#  cppcheck --std=c++11 $opt $1
#else
#  cppcheck --std=c++11 $opt |& tee /tmp/cppcheck.cppcheck > /dev/null
#  sh -c "! grep '^\[' /tmp/cppcheck.cppcheck"
#fi
exit $?

