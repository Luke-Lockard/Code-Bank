/*  stack.c
    This program will use the llist library to implement a queue.
    The program will repeatedly prompt the user for an operation and will
    recognize "+" for "push", "-" for "pop", "p" for "print", and "h"
    for "halt".  "+" prompts for the integer value to add to the stack and
    "-" displays the value that was popped.
*/
#include "./llist/llist.h"
#include <stdio.h>

void main(){
  char in;
  List* list = list_create();

  // Welcome message
  printf("Welcome to the Stack Demo\n");
  printf("\nWhen prompted, enter the one-letter commands '+' to push to the\n");
  printf("stack, '-' to pop an item, 'p' to print the current stack, and\n");
  printf("'h' to halt the program.\n\n");


  //input loop
  while(1)
  {
    printf("Ok, enter your command: ");
    while (((in = getc(stdin)) != '\n') && (in != EOF)) // filter 'enter' character
    {
      switch(in)
      {
		case 'h':
		          printf("You entered 'h'.\n");
		          exit(0);
		case '+':
		          printf("You entered '+'.\n\n");
		          char str[20];
		          printf("Enter a number: ");
		          scanf("%s", str);
		          char *ptr;
		          long l = strtol(str, &ptr, 10);
		          void* lptr = (void*)l;
		          list_push(list, lptr);
		          printf("Pushed node [%d] into list.\n\n", l);
		          break;
		case '-':
		          printf("You entered '-'.\n\n");
		          list_pop(list);
		          break;
		case 'p':
		          printf("You entered 'p'.\n\n");
		          display_list(list);
		          break;
		default:
		          printf("You entered an invalid command.\n\n");
		          break;
      }
    }
  }
}

