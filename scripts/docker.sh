#!/bin/bash
# vim: et ts=2 sts=2 sw=2
###################################################################
# Script Name  : docker.sh
# Description  : Docker helper.
# Args         :
#     param: Docker option (e.g. setup, build, run, exec, etc.)
###################################################################
set -eu

REPO_NAME=$(basename -s .git "$(git config --get remote.origin.url)")
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
REPO_ROOT_DIR=$(cd "$SCRIPT_DIR/.." && pwd)
readonly DOCKER_WORK_DIR=$REPO_ROOT_DIR

# Docker configuration
readonly USER_NAME='nino-kin'
readonly IMAGE_NAME="$USER_NAME/$REPO_NAME"
readonly TAG="latest"
readonly DOCKER_TAG="$IMAGE_NAME:$TAG"
readonly DOCKER_CONTAINER="$REPO_NAME"
readonly DOCKER_MOUNT_OPTION="--mount type=bind,source=$REPO_ROOT_DIR,target=$DOCKER_WORK_DIR"

# Build Docker image
setup() {
  if docker images "$IMAGE_NAME:$TAG" | grep "$IMAGE_NAME\s*$TAG"; then
    read -r -p "A Docker image with the same name already exists. Do you want to delete it and create a new image? (y/n): " answer
    if [ "$answer" == "y" ] || [ "$answer" == "Y" ]; then
      # Remove the image
      docker rmi "$IMAGE_NAME:$TAG"
      echo "Remove successfully and create new one... "
    else
      echo "Aborted the process."
      exit 1
    fi
  fi

  # Build Docker image
  docker build \
  --build-arg HOST_UID=$(id -u) --build-arg HOST_GID=$(id -g) \
  --build-arg WORK_DIR=$DOCKER_WORK_DIR \
  -t "$DOCKER_TAG" \
  -f "$REPO_ROOT_DIR"/Dockerfile .
}

# Run Docker container
run() {
  docker run -d -it \
    --name $DOCKER_CONTAINER \
    $DOCKER_MOUNT_OPTION \
    $DOCKER_TAG \
    /bin/bash
}

# Execute a command in a running container
exec() {
  docker start $DOCKER_CONTAINER
  docker exec -it $DOCKER_CONTAINER bash
}

build() {
  docker run --rm -t \
  --name $DOCKER_CONTAINER \
  $DOCKER_MOUNT_OPTION \
  $DOCKER_TAG \
  bash -c "$SCRIPT_DIR/build.sh"
}

test() {
  docker run --rm -t \
  --name $DOCKER_CONTAINER \
  $DOCKER_MOUNT_OPTION \
  $DOCKER_TAG \
  bash -c "$SCRIPT_DIR/test.sh"
}

coverage() {
  docker run --rm -t \
  --name $DOCKER_CONTAINER \
  $DOCKER_MOUNT_OPTION \
  $DOCKER_TAG \
  bash -c "$SCRIPT_DIR/coverage.sh"
}

package() {
  docker run --rm -t \
  --name $DOCKER_CONTAINER \
  $DOCKER_MOUNT_OPTION \
  $DOCKER_TAG \
  bash -c "$SCRIPT_DIR/package.sh"
}

kill() {
  docker kill $DOCKER_CONTAINER
}

remove-image() {
  docker rmi $DOCKER_TAG
}

pre-commit() {
  docker run --rm -t \
  --dns 8.8.8.8 \
  --name $DOCKER_CONTAINER \
  $DOCKER_MOUNT_OPTION \
  $DOCKER_TAG \
  bash -c "$SCRIPT_DIR/pre-commit.sh"
}

clean() {
  docker run --rm -t \
  --name $DOCKER_CONTAINER \
  $DOCKER_MOUNT_OPTION \
  $DOCKER_TAG \
  bash -c "bazelisk clean --expunge"
}

if [ $# == 0 ]; then
  set -- --help
fi

param=$1
echo "${1}"
  case $param in
  --all | -all | --a | -a)
    setup
    build
  ;;
  --setup | -setup | setup | --docker-build | -docker-build | docker-build)
    setup
  ;;
  --run | -run | run | --docker-run | -docker-run | docker-run)
    run
  ;;
  --build | -build | build)
    build
  ;;
  --test | -test | test | --tests | -tests | tests)
    test
  ;;
  --coverage | -coverage | coverage)
    coverage
  ;;
  --package | -package | package | --pkg | -pkg | pkg)
    package
  ;;
  --enter | -enter | enter | --exec | -exec | exec)
    exec
  ;;
  --kill | -kill | kill)
    kill
  ;;
  --remove-image | -remove-image | remove-image | --rmi | -rmi | rmi)
    remove-image
  ;;
  --pre-commit | -pre-commit | pre-commit)
    pre-commit
  ;;
  --clean | -clean | clean)
    clean
  ;;
  *)
    echo "USAGE: $0 [command]"
    echo " Commands:"
    echo "  setup      - Build an image from a Dockerfile"
    echo "  build      - Perform the build"
    echo "  tests      - Perform the tests"
    echo "  coverage   - Produce code coverage reports"
    echo "  package    - Create release packages"
    echo "  run        - Run the docker container (-it mode)"
    echo "  enter      - Enter the docker container"
    echo "  rmi        - Remove the docker image"
    echo "  clean      - Remove all artifacts"
    echo "  pre-commit - Run pre-commit checks"
    echo ""
    echo "  all       - Perform all the above steps"
  ;;
  esac
