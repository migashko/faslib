#!/bin/bash
script_name=$(realpath $0)
script_dir=$(dirname $script_name)
prj_dir=$(dirname $script_dir)
#echo $prj_dir
opt="--inconclusive --error-exitcode=1 --force --max-configs=128 \
--quiet --enable=all --suppress=missingIncludeSystem  \
--inline-suppr -I $prj_dir $prj_dir"

#echo $opt
cppcheck --std=c++11 $opt |& tee /tmp/cppcheck.cppcheck > /dev/null

#cppcheck --inconclusive  --error-exitcode=1 --force --max-configs=128 -I /home/migashko/prj/faslib/ --quiet --enable=all --std=c++11 --suppress=missingIncludeSystem  --inline-suppr /home/migashko/prj/faslib/ |& tee /tmp/cppcheck.cppcheck > /dev/null
#cppcheck --inconclusive  --error-exitcode=1 --force -I ./ --quiet --enable=all --std=c++03 --suppress=missingIncludeSystem  --inline-suppr ..  |& tee -a /tmp/cppcheck.cppcheck
sh -c "! grep '^\[' /tmp/cppcheck.cppcheck"
exit $?

