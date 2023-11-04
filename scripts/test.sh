#!/bin/bash
# vim: et ts=2 sts=2 sw=2
###################################################################
# Script Name  : test.sh
# Description  : Bazel test helper.
# Args         : none
###################################################################
set -eu

# --test_output=<summary, errors, all or streamed> default: "summary"
readonly TEST_OUTPUT_MODE=errors
# --[no]cache_test_results [-t] default: "auto"
readonly CACHE_TEST_RESULTS='no'

bazelisk test --test_output=$TEST_OUTPUT_MODE --cache_test_results=$CACHE_TEST_RESULTS //tests/...
