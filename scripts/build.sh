#!/bin/bash
# vim: et ts=2 sts=2 sw=2
###################################################################
# Script Name  : build.sh
# Description  : Bazel build helper.
# Args         : none
###################################################################
set -eu

echo -e "\n----- //source:test_app -----"
bazelisk build //source:test_app
