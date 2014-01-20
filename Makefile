#!/bin/make -f
CXXAPP := node-pi-native-tools
EXE := $(CXXAPP).exe
SRC_FILES = $(shell find src -type f -name '*.cc')
SRC_OBJECT_FILES = $(SRC_FILES:%.cc=%.o)
TEST_SRC_FILES = $(shell find src -type f -name '*.cc' \( ! -name 'main.cc' \))
TEST_FIXTURES = $(shell find test/cc/fixtures -type f)
TEST_HELPERS = $(shell find test/cc/helpers -type f -name '*.cc')
TEST_FILES = $(shell find test/cc -type f -name *.test.cc)
TEST_EXECUTABLES=$(TEST_FILES:%.test.cc=%.test.exe)

CXXFLAGS:= -std=c++0x -pthread

#General
all: test-all
	@echo

clean:
	@echo Cleaning up
	@-rm $(TEST_EXECUTABLES) 2> /dev/null
	@-rm $(EXE) 2> /dev/null
	@-rm $(SRC_OBJECT_FILES) 2> /dev/null

clean-remote:
	@ssh pi 'cd $(CXXAPP);make clean;'

%.cc:

sync-remote:
	@-ssh pi 'mkdir $(CXXAPP)' 2> /dev/null
	rsync -a --exclude '*.exe' --exclude '*.swp' --exclude '*.o' -e ssh . pi:~/$(CXXAPP) 

#Building
build: $(EXE)

build-remote: sync-remote
	ssh pi 'cd $(CXXAPP);make build'

$(EXE): $(SRC_OBJECT_FILES)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(SRC_OBJECT_FILES) -lbcm2835 

%.o: %.cc
	@echo $@
	$(CXX) $(CXXFLAGS) -c $< -o $@

#running
run-remote: build-remote
	ssh -t pi 'cd $(CXXAPP);./$(EXE)'

#Testing
test-all: run-cc-tests

test-remote: sync-remote
	ssh pi 'cd $(CXXAPP);make test-all'

run-cc-tests: $(TEST_EXECUTABLES)
	@echo
	@echo ========= TEST SUITES ========
	@-for file in $(TEST_EXECUTABLES);do \
	./$${file}; \
	done
	@echo ========= FINISHED ========
	@echo

%.test.exe: %.test.cc $(TEST_SRC_FILES) $(TEST_FIXTURES) $(TEST_HELPERS)
	@echo ==== Compiling $@
	@echo == TEST_SRC_FILES $(TEST_SRC_FILES)
	@echo == TEST_FIXTURES $(TEST_FIXTURES)
	@echo == TEST_HELPERS $(TEST_HELPERS)
	@echo
	@$(CXX) $(CXXFLAGS) $< $(TEST_FIXTURES) $(TEST_HELPERS) $(TEST_SRC_FILES) -o $@

