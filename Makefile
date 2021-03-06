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

CXXFLAGS:= -std=c++0x
CXXLIBS := -pthread

#General
all: test

clean:
	@echo [$@]
	@-rm $(TEST_EXECUTABLES) 2> /dev/null
	@-rm $(EXE) 2> /dev/null
	@-rm $(SRC_OBJECT_FILES) 2> /dev/null

clean-remote:
	@echo [$@]
	@ssh pi 'cd $(CXXAPP);make clean;'

%.cc:

%.h:

sync-remote:
	@echo [$@]
	@-ssh pi 'mkdir $(CXXAPP)' 2> /dev/null
	@rsync -a --exclude '*.exe' --exclude '*.swp' --exclude '*.o' -e ssh . pi:~/$(CXXAPP) 

#Building
build: $(EXE)

build-remote: sync-remote
	@echo [$@]
	@ssh pi 'cd $(CXXAPP);make build'

$(EXE): $(SRC_OBJECT_FILES)
	@echo [$@]
	@$(CXX) $(CXXFLAGS) -o $(EXE) $(SRC_OBJECT_FILES) -lbcm2835 $(CXXLIBS)

%.o: %.cc
	@$(CXX) $(CXXFLAGS) -c -o $@ $< $(CXXLIBS)

#running
run-remote: build-remote
	@echo [$@]
	@ssh -t pi 'cd $(CXXAPP);./$(EXE)'

#Testing
test: run-cc-tests
	@echo [$@]

test-remote: sync-remote
	@echo [$@]
	@ssh pi 'cd $(CXXAPP);make test'

run-cc-tests: $(TEST_EXECUTABLES)
	@echo [$@]
	@echo ========= TEST SUITES ========
	@-for file in $(TEST_EXECUTABLES);do \
	./$${file}; \
	done
	@echo ========= FINISHED ========
	@echo

%.test.exe: %.test.cc $(TEST_FIXTURES) $(TEST_HELPERS) $(TEST_SRC_FILES)
	@echo [$@]
#@echo ==== Compiling $@
#@echo == TEST_SRC_FILES $(TEST_SRC_FILES)
#@echo == TEST_FIXTURES $(TEST_FIXTURES)
#@echo == TEST_HELPERS $(TEST_HELPERS)
#@echo == basename $(shell basename $@ '.test.exe')
#@echo == ? $(shell echo "$@" | sed 's|test/|src/|' | sed 's|.test.exe|.cc|')
#@echo == $$@ $@
#@echo
	@$(CXX) $(CXXFLAGS) -o $@ \
		$(TEST_HELPERS) \
		$(shell find test/cc/fixtures -type f -name '*.fixture.cc' \( ! -name '$(shell basename $@ '.test.exe').fixture.cc' \)) \
		$< \
		$(shell echo $@ | sed 's|test/|src/|' | sed 's|.test.exe|.cc|') \
		$(CXXLIBS)

