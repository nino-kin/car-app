#!/bin/bash
# vim: et ts=2 sts=2 sw=2
###################################################################
# Script Name  : package.sh
# Description  : Bazel package helper.
# Args         : none
###################################################################
set -eu

bazelisk build //pkg:car_app_pkg
