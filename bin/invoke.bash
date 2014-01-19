#!/bin/bash
SCRIPT_DIR=$(dirname $(readlink -f ${BASH_SOURCE[@]}))
PROJECT_DIR=$(dirname $SCRIPT_DIR)

command=$1
shift 1

case $command in
  run)
    script=$1
    shift 1
    . $SCRIPT_DIR/$script.bash $@
  ;;
esac
