#!/bin/bash

cd $PROJECT_DIR

testDir=$PROJECT_DIR/test/cpp
makefile=$PROJECT_DIR/.Makefile-test-all


function buildRules(){
  local target=".test-all-cpp: ";
  local recipes=""
  for file in $(find $testDir -name *.cpp);do
    local name=`basename $file .cpp`.o
    local dir=`dirname $file | sed "s|$PROJECT_DIR/|./$testdir|"`
    local targetFile="$dir/$name"
    target="$target $targetFile"
    local recipe="`echo -e "\n\
\n\
$targetFile: $file\n\
\techo 5\n\
\t\\$(CXX) \\$(CXXFLAGS)\n\
\n"`"
    recipes="$recipes$recipe"
  done

  echo -e "\
$target\n\
\techo 'Running all cpp tests...'\n\
$recipes\
"
}

buildRules > $makefile
