CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.c)
OBJECTS=$(patsubst %.c, %.o, $(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c, %, $(TEST_SRC))

TARGET=build/libllist.a
SO_TARGET=$(patsubst %.a, %.so, $(TARGET))
P1_TARGET=bin/stack
P2_TARGET=bin/queue

# The Target Build
all: $(TARGET) $(SO_TARGET) tests $(P1_TARGET) $(P2_TARGET)

dev: CFLAGS=-g -Wall -Isrc -Wextra $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

$(P1_TARGET): $(OBJECTS) src/stack.c
	$(CC) src/stack.c $(OBJECTS) -o $@

$(P2_TARGET): $(OBJECTS) src/queue.c
	$(CC) src/queue.c $(OBJECTS) -o $@
	
build:
	@mkdir -p build
	@mkdir -p bin

# The Unit Tests
.PHONY: tests
tests: CFLAGS += $(LIBS)
tests: 
	$(CC) $(CFLAGS) -o $(TESTS) $(SO_TARGET) $(TEST_SRC)
	sh ./tests/runtests.sh

# The Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS)
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