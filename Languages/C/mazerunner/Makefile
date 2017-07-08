CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.c src/maze.c src/mazer.c)
OBJECTS=$(patsubst %.c, %.o, $(SOURCES))
ESOURCE=src/mazerunner.c
EOBJECT=src/mazerunner.o

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c, %, $(TEST_SRC))

TARGET=bin/mazerunner
TEST_TARGET=tests/mazer_tests
LIB_MAZE=build/maze.a
LIB_MAZER=build/mazer.a
SO_MAZE=$(patsubst %.a, %.so, $(LIB_MAZE))
SO_MAZER=$(patsubst %.a, %.so, $(LIB_MAZER))

# The Target Build
all: $(LIB_MAZE) $(SO_MAZE) $(LIB_MAZER) $(SO_MAZER) exec tests

dev: CFLAGS=-g -Wall -Isrc -Wextra $(OPTFLAGS)
dev: all

$(LIB_MAZE): CFLAGS += -fPIC
$(LIB_MAZE): build src/maze.o
	ar rcs $@ src/maze.o
	ranlib $@

$(SO_MAZE): $(LIB_MAZE) src/maze.o
	$(CC) -shared -o $@ src/maze.o

$(LIB_MAZER): CFLAGS += -fPIC
$(LIB_MAZER): build src/mazer.o
	ar rcs $@ src/mazer.o
	ranlib $@

$(SO_MAZER): $(LIB_MAZER) src/mazer.o
	$(CC) -shared -o $@ src/mazer.o

$(TARGET): $(SO_MAZE) $(SO_MAZER) $(EOBJECT)
	$(CC) -o $@ $(EOBJECT) $(SO_MAZE) $(SO_MAZER)

$($TEST_TARGET): $(SO_MAZE) $(SO_MAZER)
	$(CC) -o $@ $(TESTS) $(SO_MAZE) $(SO_MAZER)

build:
	@mkdir -p build
	@mkdir -p bin

# The Executable
.PHONY: exec
exec: $(TARGET)

# The Unit Tests
.PHONY: tests
tests: CFLAGS += $(LIBS)
tests: 
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(SO_MAZE) $(SO_MAZER) $(TEST_SRC)
#	$(CC) -o $@ $(SO_MAZE) $(SO_MAZER) $(TESTS)
	sh ./tests/runtests.sh

# The Cleaner
clean:
	rm -rf build bin $(OBJECTS) $(EOBJECT) $(TESTS) $(TEST_TARGET)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf 'find . -name "*.dSYM" -print'

# The Install
install:
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib

# The Checker
check:
	@echo Files with potentially dangerous functions.
	@grep "[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)\
		|stpn?cpy|a?sn?printf|byte_)" $(SOURCES) || true