When the archive file is unpacked, you should have the following directory/file tree:

project4/
  src/
    llist/
      dbg.h
      llist.c
      llist.h
  bin/
  tests/
    dbg.h
    list_tests.c
    list_tests.bak
    minunit.h
    runtests.sh
  LICENSE
  Makefile
  README.md

You can build and run the program with the command 'make all' from the projtest directory,
but it should fail at the first test.
The llist.c file is the only one you need to modify.  Simply fill in the correct code for
all the functions.  Run 'make all' and it will automatically build and run the unit tests.
You are finished when all the tests pass.  If the comments for the code are not enough,
you can examine the list_tests.c file to find out what the functions are expected to do.
The list_tests.bak file is just a more condensed version of the tests but, if a test fails,
you won't know exactly which assert caused the failure. It is included just so you can see
how I crafted the tests before breaking them up into individual tests for each assertion.