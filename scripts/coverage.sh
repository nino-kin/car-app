#!/bin/bash
# vim: et ts=2 sts=2 sw=2
###################################################################
# Script Name  : coverage.sh
# Description  : Bazel coverage helper.
# Args         : none
###################################################################
set -eu

readonly OUTPUT_DIR='coverage-html'
# --test_output=<summary, errors, all or streamed> default: "summary"
readonly TEST_OUTPUT_MODE=errors
# --[no]cache_test_results [-t] default: "auto"
readonly CACHE_TEST_RESULTS='no'

# Measure code coverage
bazelisk coverage --combined_report=lcov --test_output ${TEST_OUTPUT_MODE} --cache_test_results=${CACHE_TEST_RESULTS} --instrumentation_filter="-^.*test.*$" //tests/...
echo -e "\n===== $(bazelisk info output_path)/_coverage/ ====="
ls -la $(bazelisk info output_path)/_coverage/
# Produce coverage reports in HTML format
echo -e "\nINFO: Generating coverage reports in HTML format..."
echo "================================================================================"
genhtml --branch-coverage --demangle-cpp -o $OUTPUT_DIR "$(bazelisk info output_path)/_coverage/_coverage_report.dat"
