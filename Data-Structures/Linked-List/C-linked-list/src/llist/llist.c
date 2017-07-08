#include <llist/llist.h>
#include <llist/dbg.h>

/*
  Just initializes the list structure (the node pointers are NULL and
  the count = 0.
*/
List*     list_create()
{
  List* myList = malloc(sizeof(List));
  myList->count = 0;
  myList->first = NULL;
  myList->last = NULL;
  return myList;
}

/*
  Just initializes a ListNode structure (the node pointers are NULL and
  the pointer to the data is set to payload.
*/
ListNode* list_create_node(void* payload)
{
  // check if myList exists
  // check if myList.first exists
  ListNode* myNode = malloc(sizeof(ListNode));
  myNode->value = payload;
  myNode->next = NULL;
  myNode->prev = NULL;
  return myNode;
}

/*
  Frees any nodes in the list and then frees the list structure.
*/
List*     list_destroy(List* list)
{
  // empty the list
	list_clear(list);
  // free list structure
 	free(list);
 	list = NULL;
 	return list;
}

/*
  Frees any nodes in the list but leaves the list structure.
*/
void      list_clear(List* list)
{
  while (list_count(list) != 0) {
  	// list_remove_node() takes care of pointers, freeing the memory, and the count
    list_remove_node(list, list->first);
  }
}

/*
  Returns the count in the list structure.
*/
int       list_count(List* list)
{
  return list->count;
}

/*
  Returns the first node in the list.
*/
ListNode* list_first(List* list)
{
  return list->first;
}

/*
  Returns the last node in the list.
*/
ListNode* list_last(List* list)
{
  return list->last;
}

/*
  Finds a node in the list by value and returns the pointer to the node.
  If no matching node is found, returns NULL.
*/
ListNode* list_find(List* list, void* value)
{
	ListNode* current = list->first;
	while(current != NULL){
		if (current->value == value) return current;
		current = current->next; 
	}
	return NULL;
}

/*
  Inserts a node in the list after the node containing value.  If no node
  has the passed value or if value == NULL, insert at the end of the list.
*/
void      list_insert_after(List* list, ListNode* node, void* value)
{	
	// special case: empty list
	// just insert the node in the list
	if (list_count(list) == 0) {
		list->first = node;
		list->last = node;
		list->count++;
		
	} else {	// not an empty list
		
		if (value == NULL) {	// insert at end of list
			ListNode* last_node = list->last;
			last_node->next = node;
			node->prev = last_node;
			list->last = node;
			list->count++;
			
		} else {	// insert the node in the list after the node containing value
			
			// find the node containing the value
			// list_find() will return NULL if node doesn't exist
			ListNode* current = list_find(list, value);
			
			if (current->value == NULL){	// Node didn't exist, insert new node at end
				ListNode* last_node = list->last;
				last_node->next = node;
				current->prev = last_node;
				list->last = node;
				list->count++;
				
			} else if (current->value == value){	// node containing value reached
				node->next = current->next;
				node->prev = current;
				current->next = node;
				node->next->prev = node;
				list->count++;
				
			} else {
				printf("\nERROR: list_insert_after() Expected to reach end of list, or node containing value, but did not.\n");
			}
		}
	}
}


/*
  Inserts a node in the list before the node containing value.  If no node has
  the passed value or if value == NULL, insert at the beginning of the list.
*/
void      list_insert_before(List* list, ListNode* node, void* value)
{
	// special case: empty list
	// just insert the node in the list
	if (list_count(list) == 0) {
		list->first = node;
		list->last = node;
		list->count++;
		
	} else {	// not an empty list
		
		if (value == NULL) {	// insert at beginning of list
			ListNode* first_node = list->first;
			first_node->prev = node;
			node->next = first_node;
			list->first = node;
			list->count++;
			
		} else {	// insert the node in the list before the node containing value

			// find the node containing the value
			// list_find() will return NULL if node doesn't exist
			ListNode* current = list_find(list, value);
			
			if (current->value == NULL){	// Node didn't exist, insert new node at beginning
				ListNode* first_node = list->first;
				first_node->prev = node;
				node->next = first_node;
				list->first = node;
				list->count++;
				
			} else if (current->value == value){	// node containing value reached
				node->next = current;
				node->prev = current->prev;
				current->prev->next = node;
				current->prev = node;
				list->count++;
				
			} else {
				printf("\nERROR: list_insert_after() Expected to reach end of list, or node containing value, but did not.\n");
			}
		}
	}
}

/*
  Removes the specified node from the list and frees it.  The node's value
  is saved and returned.
*/
void*     list_remove_node(List* list, ListNode* node)
{
	void* val = node->value;

	// Four cases: node not in list, is first node, is last node, or in middle
	if ((node->next == NULL) && (node->prev == NULL) && (list->first != node)) return NULL;

	// Node is first node
	if (node->prev == NULL) {
		//subcase: node is only node in list
		if (node->next == NULL){
			list->first = NULL;
			list->last = NULL;
			free(node);
			list->count--;
			return val;
		
		} else {
			list->first = node->next;
			list->first->prev = NULL;
			free(node);
			list->count--;
			return val;
		}

	// Node is last node
	} else if (node->next == NULL) {
		list->last = node->prev;
		list->last->next = NULL;
		free(node);
		list->count--;
		return val;
	
	// Node is in middle of list
	} else {
		node->prev->next = node->next;
		node->next->prev = node->prev;
		free(node);
		list->count--;
		return val;
	}
}

/*
  Removes the node with the specified value from the list.  The node's value
  is saved and returned.  If a node with the value is not found in the list,
  return NULL
*/
void*     list_remove_value(List* list, void* value)
{
	// find the node with specified value
	// will get the node, or NULL if not found
	ListNode* node = list_find(list, value);

	if (node == NULL) return NULL;

	void* val = list_remove_node(list, node);
	return val;
}

/*
	Helper function.
	Prints out the list. Used for debugging mostly.
*
void	  print_list(List* list)
{
	if (list->first == NULL && list->count == 0) {
		printf("\nLIST EMPTY\n\n");
	}
	ListNode* current = list->first;
	while(current != NULL) {
		printf("[%s] ", current->value);
		current = current->next;
	}
	printf("\n");
}
*/

// ----- The following functions are not needed until Project 5 ------------ //
/*
  Adds a node at one end of the list (your choice but document it).
*/
void      list_push(List* list, void* value)
{
	// create the node
	ListNode* node = list_create_node(value);
	// insert it into the list
	if (list_count(list) == 0){	// special case: empty list
		list->first = node;
		list->last = node;
	
	} else {	// not an empty list
		ListNode* last_node = list->last;
		node->prev = last_node;
		last_node->next = node;
		list->last = node;
	}
	// increase the list count
	list->count++;
}

/*
  Add a node at one end of the list (your choice, but document it).
*/
void      list_enqueue(List* list, void* value);

/*
  Removes a node from the same end of the list as list_push(). The value
  of the removed node is returned.
*/
void*     list_pop(List* list);

/*
  Removes a node from the opposite end of the list as list_enqueue().  The
  value of the removed node is returned.
*/
void*     list_dequeue(List* list);

