#!/bin/bash
script_name=$(realpath $0)
script_dir=$(dirname $script_name)
prj_dir=$(dirname $script_dir)

./cppcheck-exec.sh --std=c++11 $prj_dir |& tee /tmp/cppcheck.cppcheck > /dev/null

sh -c "! grep '^\[' /tmp/cppcheck.cppcheck"
exit $?

