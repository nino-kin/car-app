.PHONY: setup build tests run exec kill coverage package clean debug
.DEFAULT_GOAL := help

SHELL := /bin/bash

PROJECT_NAME := $(shell basename -s .git `git config --get remote.origin.url`)

PWD := $(shell pwd)
ROOT_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
SCRIPT_DIR := scripts

# Docker
## Local web server port
DOCKER_PORT := 8000

# Bazel
## Test output mode: --test_output=<summary, errors, all or streamed> default=summary
TEST_OUTPUT_MODE := errors

# For more information on this technique, see
# https://marmelab.com/blog/2016/02/29/auto-documented-makefile.html

help: ## Show this help message
	@echo -e "\nUsage: make TARGET\n\nTargets:"
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) \
	| sort \
	| awk 'BEGIN {FS = ":.*?## "}; {printf "  %-20s %s\n", $$1, $$2}'

setup: ## Set up environment
	@echo -e "\nINFO: Set up your environment..."
	@echo "============================================================"
	@$(ROOT_DIR)/$(SCRIPT_DIR)/docker.sh setup
	@echo "============================================================"

build: ## Build the project
	@echo -e "\nINFO: Building $(PROJECT_NAME)..."
	@echo "============================================================"
	@$(ROOT_DIR)/$(SCRIPT_DIR)/docker.sh build
	@echo "============================================================"

tests: ## Test the projct
	@echo -e "\nINFO: Testing $(PROJECT_NAME)..."
	@echo "============================================================"
	@$(ROOT_DIR)/$(SCRIPT_DIR)/docker.sh tests
	@echo "============================================================"

run: ## Run Docker conatainer
	@echo -e "\nINFO: Running a container..."
	@echo "============================================================"
	@$(ROOT_DIR)/$(SCRIPT_DIR)/docker.sh run
	@echo "============================================================"

exec: ## Run Docker conatainer
	@echo -e "\nINFO: You can execute commands in a running container..."
	@echo "============================================================"
	@$(ROOT_DIR)/$(SCRIPT_DIR)/docker.sh exec
	@echo "============================================================"

kill: ## Kill Docker container
	@echo -e "\nINFO: Kill a running container..."
	@echo "============================================================"
	@$(ROOT_DIR)/$(SCRIPT_DIR)/docker.sh kill
	@echo "============================================================"

coverage: ## Analyze coverage
	@echo -e "\nINFO: Creating release packages..."
	@echo "================================================================================"
	@[ -z "$$(find . -maxdepth 1 -type d -name 'coverage-html')" ] || sudo chmod -R 777 coverage-html/ && rm -rf coverage-html/
	@$(ROOT_DIR)/$(SCRIPT_DIR)/docker.sh coverage
	@echo "================================================================================"

package: ## Create release packages
	@echo -e "\nINFO: Creating relase packages..."
	@echo "================================================================================"
	@$(ROOT_DIR)/$(SCRIPT_DIR)/docker.sh package
	@echo "================================================================================"

clean: ## Clean all artifacts
	@echo -e "\nINFO: Cleaning up..."
	@[ -z "$$(find . -maxdepth 1 -type d -name '.bazel')" ] || sudo chmod -R 777 .bazel/ && rm -rf .bazel/
	@[ -z "$$(find . -maxdepth 1 -type d -name 'site')" ] || sudo chmod -R 777 site/ && rm -rf site/
	@[ -z "$$(find . -maxdepth 1 -type d -name 'out')" ] || sudo chmod -R 777 out/ && rm -rf out/
	@[ -z "$$(find . -maxdepth 1 -type d -name 'coverage-html')" ] || sudo chmod -R 777 coverage-html/ && rm -rf coverage-html/
	@sudo rm -f bazel-*
	@find . -type d -name .bazel -exec rm -rf {} +

debug: ## Debug
	@echo -e "\nINFO: Building $(PROJECT_NAME) in DEBUG mode..."
	@echo "============================================================"
	@echo -e "\n----- //source:test_app -----"
	@bazelisk build --config=optdbg //source:test_app
	@echo "============================================================"

#---------------------------------------#
# App                                   #
#---------------------------------------#
.PHONY: run-test-app
run-test-app: ## Run test app
	@echo -e "\nINFO: Run test app..."
	@echo "============================================================"
	@$(ROOT_DIR)/bazel-bin/source/test_app
	@echo "============================================================"

#---------------------------------------#
# MkDocs                                #
#---------------------------------------#
.PHONY: mkdocs-build, mkdocs-serve
mkdocs-build: ## Build documentation for MkDocs
	@docker run --rm -it -v $(PWD):/docs squidfunk/mkdocs-material build

mkdocs-serve: ## Serve documentation for MkDocs
	docker run --rm -it -p $(DOCKER_PORT):8000 -v $(PWD):/docs squidfunk/mkdocs-material
