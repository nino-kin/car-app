#!/bin/bash
# vim: et ts=2 sts=2 sw=2
###################################################################
# Script Name  : pre-commit.sh
# Description  : Pre-commit helper.
# Args         : none
###################################################################
set -eu

pre-commit run --all-files
