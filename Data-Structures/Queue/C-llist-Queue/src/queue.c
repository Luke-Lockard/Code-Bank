/*  queue.c
    This program will use the llist library to implement a queue.
    The program will repeatedly prompt the user for an operation and will
    recognize "q" for "queue", "d" for "dequeue", "p" for "print", and "h"
    for "halt".  "q" prompts for the integer value to add to the queue and
    "d" displays the value that was dequeued.
*/
#include "./llist/llist.h"
#include <stdio.h>

void main(){
  char in;
  List* list = list_create();

  // Welcome message
  printf("Welcome to the Queue Demo\n");
  printf("\nWhen prompted, enter the one-letter commands 'q' to add to the\n");
  printf("queue, 'd' to dequeue an item, 'p' to print the current queue, and\n");
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
		case 'q':
		          printf("You entered 'q'.\n\n");
              char str[20];
              printf("Enter a number: ");
              scanf("%s", str);
              char *ptr;
              long l = strtol(str, &ptr, 10);
              void* lptr = (void*)l;
              list_enqueue(list, lptr);
              printf("Enqueued node [%d] into list.\n\n", l);
		          break;
		case 'd':
		          printf("You entered 'd'.\n\n");
              list_dequeue(list);
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