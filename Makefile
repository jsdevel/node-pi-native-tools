CXXAPP := node-pi-native-tools
EXE := $(CXXAPP).exe
SRC_FILES = $(shell find src -type f -name '*.cpp')
SRC_OBJECT_FILES = $(SRC_FILES:%.cpp=%.o)
TEST_SRC_FILES = $(shell find src -type f -name '*.cpp' \( ! -name 'main.cpp' \))
TEST_FIXTURES = $(shell find test/cpp/fixtures -type f)
TEST_HELPERS = $(shell find test/cpp/helpers -type f -name '*.cpp')
TEST_FILES = $(shell find test/cpp -type f -name *.test.cpp)
TEST_EXECUTABLES=$(TEST_FILES:%.test.cpp=%.test.exe)

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

%.cpp:

sync-remote:
	@-ssh pi 'mkdir $(CXXAPP)' 2> /dev/null
	rsync -a --exclude '*.exe' --exclude '*.swp' --exclude '*.o' -e ssh . pi:~/$(CXXAPP) 

#Building
build: $(EXE)

build-remote: sync-remote
	ssh pi 'cd $(CXXAPP);make build'

$(EXE): $(SRC_OBJECT_FILES)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(SRC_OBJECT_FILES) -lbcm2835 

%.o: %.cpp
	@echo $@
	$(CXX) $(CXXFLAGS) -c $< -o $@

#running
run-remote: build-remote
	ssh -t pi 'cd $(CXXAPP);./$(EXE)'

#Testing
test-all: run-cpp-tests

test-remote: sync-remote
	ssh pi 'cd $(CXXAPP);make test-all'

run-cpp-tests: $(TEST_EXECUTABLES)
	@echo
	@echo ========= TEST SUITES ========
	@-for file in $(TEST_EXECUTABLES);do \
	echo "";\
	echo "======== $${file}";\
	./$${file} || { echo 'FAILED'; exit 1; };\
	echo "";\
	echo "";\
	done
	@echo ========= FINISHED ========
	@echo

%.test.exe: %.test.cpp $(TEST_SRC_FILES) $(TEST_FIXTURES) $(TEST_HELPERS)
	@echo ==== Compiling $@
	@echo == TEST_SRC_FILES $(TEST_SRC_FILES)
	@echo == TEST_FIXTURES $(TEST_FIXTURES)
	@echo == TEST_HELPERS $(TEST_HELPERS)
	@echo
	@$(CXX) $(CXXFLAGS) $< $(TEST_FIXTURES) $(TEST_HELPERS) $(TEST_SRC_FILES) -o $@

