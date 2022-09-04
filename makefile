# Executable file / project name
EXE = linkedlist

# Includes, Sources, Build Objects
SRC   = main linkedlist
INC   = $(filter-out main,$(SRC))

# Directories
BINDIR  = bin
INCDIR  = inc
SRCDIR  = src
OBJDIR  = obj

# Unit Testing
UNITY_ROOT = unit_tests/unity
TESTDIR    = unit_tests
RUNDIR     = unit_tests/runners
INC_DIRS = -I$(SRCDIR)/ -I$(INCDIR)/ -I$(UNITY_ROOT)/

# Set Build flags
CC = gcc
CFLAGS = -I$(INCDIR)
LIBS = -lm

# TFLAGS=-std=c89
TFLAGS += -Wall
TFLAGS += -Wextra
TFLAGS += -Wpointer-arith
TFLAGS += -Wcast-align
TFLAGS += -Wwrite-strings
TFLAGS += -Wswitch-default
TFLAGS += -Wunreachable-code
TFLAGS += -Winit-self
TFLAGS += -Wmissing-field-initializers
TFLAGS += -Wno-unknown-pragmas
TFLAGS += -Wstrict-prototypes
TFLAGS += -Wundef
TFLAGS += -Wold-style-definition

# Build Paths to Files
_SRC  = $(patsubst %,$(SRCDIR)/%.c,$(SRC))
_INC  = $(patsubst %,$(INCDIR)/%.h,$(INC))
_OBJ  = $(patsubst %,$(OBJDIR)/%.o,$(SRC))
_TEST = $(patsubst %,$(TESTDIR)/test/%_test.c,$(INC))
_TOBJ = $(patsubst %,$(TESTDIR)/test/%_test.o,$(INC))
_RUNR = $(patsubst %,$(TESTDIR)/runners/%_runner.c,$(INC))

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	@echo 
	@echo Compiling \"$<\"
	$(CC) -c -o $@ $< $(CFLAGS)

$(TESTDIR)/runners/%_runner.c: $(TESTDIR)/test/%_test.c
	@echo 
	@echo Building runner \"$<\"
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb $< $@

$(TESTDIR)/test/%_test.o: $(_TEST) $(_RUNR)
	@echo 
	@echo Generating test \"$<\"
	$(CC) $(TFLAGS) \
	$(INC_DIRS) \
	$(UNITY_ROOT)/unity.c \
	$(patsubst $(TESTDIR)/test/%_test.o,src/%.c,$@) \
	$(patsubst %_test.o,%_test.c,$@) \
	$(patsubst $(TESTDIR)/test/%_test.o,$(TESTDIR)/runners/%_runner.c,$@) \
	-o $@

# Create phony for no file targets
.PHONY: clean
.PHONY: all
.PHONY: test

default: clean build
	@echo
	@echo BUILD COMPLETE!

# General target for cleaning and building the project
all: clean build test

# Example build target
build: $(_OBJ)
	@echo 
	@echo =======================================
	@echo - - - = = = B U I L D I N G = = = - - -
	@echo =======================================
	@echo Generating executable \"$(BINDIR)/$(EXE)\"
	$(CC) -o $(BINDIR)/$(EXE) $^ $(CFLAGS) $(LIBS)

test: $(_TOBJ) $(_RUNR)
	@echo 
	@echo =================================================
	@echo - - - = = = R U N N I N G - T E S T S = = = - - -
	@echo =================================================
	@for f in unit_tests/test/*.o; do\
		./$$f && echo "-----------------------\n"; \
	done

# Clean objects directory
clean:
	@echo 
	@echo =======================================
	@echo - - - = = = C L E A N I N G = = = - - -
	@echo =======================================
	rm -f $(OBJDIR)/*.o $(TESTDIR)/test/*.o $(TESTDIR)/runners/*_runner.c *~ core $(INCDIR)/*~ $(BINDIR)/$(EXE)
