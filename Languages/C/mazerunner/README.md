When the archive file is unpacked, you should have the following directory/file tree:

mazerunner/
  src/
    dbg.h
    maze.c
    maze.h
    maze.o
    mazer.h
    mazer.c
    mazerunner.c
    mazerunner.o
  tests/
    dbg.h
    minunit.h
    runtests.sh
    mazer_tests.c
  LICENSE
  Makefile
  Makefile.bld
  README.md

You can build and run the demo with the command 'make all' from the projtest directory. This
demo expects two integer parameters for the width and height of a maze, which it will then
generate.  The parameters must be odd numbers.  If they are incorrect or missing, a usage
message will be displayed.  Example:

~/ee222/mazerunner$ bin/mazerunner 71 21

There is a second makefile called Makefile.bld which expects your library code to be called
mazer.c (with optional mazer.h) and your unit tests to be in mazer_tests.c in the tests
subdirectory.  To use it, rename Makefile to Makefile.bak and then rename Makefile.bld to
Makefile without an extension.  If you name your source files anything else, you will need
to adjust the makefile accordingly.