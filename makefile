# DIRECTORIES
SRC_DIR = .\src
MAINSRC_DIR = $(SRC_DIR)\main
TESTERSRC_DIR = $(SRC_DIR)\test

INCLUDE_DIR = .\include

RELEASE_DIR = .\release

TEST_DIR = .\test


# COMPILER (editable)
CC = g++



# COMMANDS



# Command 1 "make" : make executable file
# every source file $(MAINSRC_DIR)\*.cpp is compiled to $(RELEASEOBJ_DIR)\*.o
# then link them to generate $(RELEASEBIN_DIR)\$(RELEASEBIN).exe

# editable variables
RELEASEBINNODIR = sudoku.exe
RELEASEFLAGS = -I $(INCLUDE_DIR) -fdiagnostics-color=always -g

# computed variables
RELEASEOBJ_DIR = $(RELEASE_DIR)\obj
RELEASEBIN_DIR = $(RELEASE_DIR)\bin

RELEASESRCS = $(wildcard $(MAINSRC_DIR)/*.cpp)
RELEASEOBJS = $(patsubst %.cpp,$(RELEASEOBJ_DIR)/%.o,$(notdir $(RELEASESRCS)))
RELEASEBIN = $(RELEASEBIN_DIR)\$(RELEASEBINNODIR)

# instructions
all: releaseEnv $(RELEASEBIN)

$(RELEASEBIN): $(RELEASEOBJS)
	$(CC) $(RELEASEOBJS) -o $(RELEASEBIN) $(RELEASEFLAGS)

$(RELEASEOBJS): $(RELEASEOBJ_DIR)/%.o: $(MAINSRC_DIR)/%.cpp
	$(CC) -c $< -o $@ $(RELEASEFLAGS)

releaseEnv: 
	@if not exist $(RELEASE_DIR) (mkdir $(RELEASE_DIR))
	@if not exist $(RELEASEBIN_DIR) (mkdir $(RELEASEBIN_DIR))
	@if not exist $(RELEASEOBJ_DIR) (mkdir $(RELEASEOBJ_DIR))




# Command 2 "make unittest TESTFILE=<filename>"
# this makefile will find testfile as $(MAINSRC_DIR)\<filename>.cpp and tester in $(TESTERSRC_DIR)\test_<filename>.cpp
# compile them to $(TESTENV_DIR)\<filename>.o $(TESTENV_DIR)\test_<filename>.o
# and then link them to generate a PE file as $(TESTENV_DIR)\<filename>.exe and run
# this also generates notefile $(TESTENV_DIR)\<filename>.gcno and data for gcno to use
# then use gcov to generate coverage report

# fake target
.PHONY: unittest
.PHONY: $(TESTBIN) $(TESTMAINOBJ) $(TESTTESTEROBJ) testEnv
# editable variables
TESTFLAGS = -I $(INCLUDE_DIR) -fdiagnostics-color=always -g --coverage -fprofile-abs-path

# computed variables
TESTFILENOFIXES = $(patsubst %.cpp,%,$(patsubst test_%,%,$(TESTFILE)))
TESTENV_DIR = $(TEST_DIR)\$(TESTFILENOFIXES)

TESTMAINSRC = $(MAINSRC_DIR)\$(TESTFILENOFIXES).cpp
TESTTESTERSRC = $(TESTERSRC_DIR)\test_$(TESTFILENOFIXES).cpp
TESTMAINOBJ = $(TESTENV_DIR)\$(TESTFILENOFIXES).o
TESTTESTEROBJ = $(TESTENV_DIR)\test_$(TESTFILENOFIXES).o
TESTBIN = $(TESTENV_DIR)\$(TESTFILENOFIXES).exe

# instructions
unittest: testEnv $(TESTBIN) runtest

runtest:
	cd $(TESTENV_DIR) && $(notdir $(TESTBIN)) && gcov $(notdir $(TESTMAINSRC)) $(notdir $(TESTTESTSRC)) > cov.txt

$(TESTBIN): $(TESTMAINOBJ) $(TESTTESTEROBJ)
	$(CC) $(TESTMAINOBJ) $(TESTTESTEROBJ) -o $(TESTBIN) $(TESTFLAGS)

$(TESTMAINOBJ): $(TESTMAINSRC)
	$(CC) -c $(TESTMAINSRC) -o $(TESTMAINOBJ) $(TESTFLAGS)

$(TESTTESTEROBJ): $(TESTTESTERSRC)
	$(CC) -c $(TESTTESTERSRC) -o $(TESTTESTEROBJ) $(TESTFLAGS)

testEnv:
	@if not exist $(TEST_DIR) (mkdir $(TEST_DIR))
	@if not exist $(TESTENV_DIR) (mkdir $(TESTENV_DIR))


# Command 3 "make clean"

# fake target
.PHONY: clean
.PHONY: cleanTest cleanRelease cleanReleasebin cleanReleaseobj

# computed variables
RELEASEBIN_DIR = $(RELEASE_DIR)\bin
RELEASEOBJ_DIR = $(RELEASE_DIR)\obj

# instructions
clean: cleanRelease cleanTest

cleanRelease: cleanReleasebin cleanReleaseobj
	@if exist $(RELEASE_DIR) (rmdir /S /Q $(RELEASE_DIR))

cleanReleasebin:
	@if exist $(RELEASEBIN_DIR) (rmdir /S /Q $(RELEASEBIN_DIR))

cleanReleaseobj:
	@if exist $(RELEASEOBJ_DIR) (rmdir /S /Q $(RELEASEOBJ_DIR))

cleanTest:
	@if exist $(TEST_DIR) (rmdir /S /Q $(TEST_DIR))




# Command 4 "make debug" : debug this makefile

# fake target
.PHONY: debug

# instructions
debug: