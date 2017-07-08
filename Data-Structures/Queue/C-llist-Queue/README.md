When the archive file is unpacked, you should have the following directory/file tree:

project4/
  bin/
  build/
    libllist.a
    libllist.so
  src/
    queue.c
    stack.c
    llist/
      dbg.h
      llist.c
      llist.h
      llist.o
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
and all tests should pass followed by the build of bin/stack and bin/queue.  You can then
run those programs, though they only accept commands and echo them back without doing
anything.  Before you can modify them, you will need to complete the llist library.
The llist.c file is the file you need to modify, completeing the four functions you didn't
finish in Project 4.  There will not be any unit tests for them.  You can write their code
from srcatch, but if you use the functions already in the library, each of them will only take
a single line of code.  

When you have finished the library functions, you can now use the library to finish the stack
and queue programs.  For your report, be sure to show your testing, showing that the stack
and queue programs really do add and remove items correctly.  Don't forget to see what happens
if the stack or queue is empty.  Don't forget to comment your code, too.