#include "minunit.h"
#include <dlfcn.h>

/* We need to include the mazer.h file so the globals and
   maze functions are available to the tests. */
#include "maze.h"
#include "mazer.h"

/* This program demonstrates both using library functions and
   also using the minunit unit test macros to create unit tests
   for the library functions. */

// pointer to function type.  Note: if your functions have
// different parameters, you will need a different type for
// each different signature.
typedef int (*lib_function) ();
// library to access
char *lib_file = "build/mazer.so";
// pointer to the library
void *lib = NULL;

/* This function attempts to run a function and
   compares its return value against a selected value.  It will
   display and log debug messages if the function is not found
   or returns something other than expected. */
int check_function(const char *func_to_run,
		   int expected)
{
  lib_function func = dlsym(lib, func_to_run);
  check(func != NULL,
	"Did not find %s function in the library %s: %s", func_to_run,
	lib_file, dlerror());

  int rc = func();
  check(rc == expected, "Function %s returned %d ",
	func_to_run, rc);

  return 1;
error:
  return 0;
}

/* This function attempts to open the library file and associate
   it with the pointer variable lib.  If it doesn't work, it will
   display and log a debug message. */
char *test_dlopen()
{
  lib = dlopen(lib_file, RTLD_NOW);
  mu_assert(lib != NULL, "Failed to open the library to test.");

  return NULL;
}

/* This function uses the minunit macro mu_assert to test functions
   by passing data to the check_function routine defined above. */
char *test_functions()
{
  // set up the maze for testing
  setX(11);
  setY(11);
  InitMaze();

  // now all functions should work except for MoveForward and
  // AtDestination.
  mu_assert(check_function("InitRunner", true),
	    "InitRunner.");
  mu_assert(check_function("TurnLeft", true),
	    "TurnLeft failed.");
  mu_assert(check_function("TurnRight", true),
	    "TurnRight failed.");
  mu_assert(check_function("IsWall", true),
	    "IsWall failed to detect wall.");

  // now set up the grid to be empty so we can test more.
  int i;
  for (i = 0; i < 121; i++)
	grid[i] = ' ';
  facing = EAST;
  mu_assert(check_function("IsWall", false),
	    "IsWall failed to detect open space.");
  mu_assert(check_function("MoveForward", true),
	    "MoveForward failed to move across open space.");

  // see if we can detect the end of the maze.
  xpos = 9;
  ypos = 9;
  facing = NORTH;
  mu_assert(check_function("AtDestination", true),
	    "AtDestination failed.");

  // now check IsWall against '.' and then 'o'.
  for (i = 0; i < 121; i++)
	grid[i] = '.';
  mu_assert(check_function("IsWall", false),
	    "IsWall failed to detect backtrackable space.");
  for (i = 0; i < 121; i++)
	grid[i] = 'O';
  mu_assert(check_function("IsWall", true),
	    "IsWall failed to detect impassable space already backtracked.");
  for (i = 0; i < 121; i++)
	grid[i] = 'o';
  mu_assert(check_function("IsWall", false),
	    "IsWall failed to detect passable space already backtracked.");

  return NULL;
}

/* This function uses the minunit macro mu_assert to test functions
   by passing data to the check_function routine defined above. In
   this case, we are expecting a failure.*/
char *test_failures()
{
  // First we set up for failure
  grid = NULL;

  mu_assert(check_function("InitRunner", false),
	    "InitRunner should fail with no grid.");
  mu_assert(check_function("IsWall", true),
	    "IsWall should fail with no grid.");
  mu_assert(check_function("MoveForward", false),
	    "MoveForward should fail with no grid.");
  mu_assert(check_function("AtDestination", false),
	    "AtDestination should fail with no grid.");

  // also impossible facing
  facing = 5;
  mu_assert(check_function("TurnLeft", false),
	    "TurnLeft should fail on bad facing.");
  mu_assert(check_function("TurnRight", false),
	    "TurnRight should fail on bad facing.");

  return NULL;
}

/* This function attempts to close the library file and if it doesn't
   work, it will display and log a debug message. */
char *test_dlclose()
{
  int rc = dlclose(lib);
  mu_assert(rc == 0, "Failed to close lib.");

  return NULL;
}

/* This function initializes the minunit tests and then sequentially
   runs all the tests defined above using the mu_run_test macro. */
char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_dlopen);
  mu_run_test(test_functions);
  mu_run_test(test_failures);
  mu_run_test(test_dlclose);

  return NULL;
}

// This is the entry point for the shell script for testing.
RUN_TESTS(all_tests);
