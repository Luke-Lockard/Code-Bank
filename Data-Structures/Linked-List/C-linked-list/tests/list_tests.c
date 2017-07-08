#include "minunit.h"
#include <llist/llist.h>
#include <assert.h>

static List* list = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";
char *invalidStr = "T";
ListNode* temp = NULL;

char *test_create()
{
	list = list_create();
	mu_assert(list != NULL, "Failed to create list.");

	return NULL;
}

char *test_create_node()
{
	temp = list_create_node(test1);
	mu_assert(temp != NULL, "Failed to create node.");

	return NULL;
}

char *test_create_node2()
{
    mu_assert(temp->value == test1, "Created node has incorrect value.");

	return NULL;
}

char *test_insert_after()
{
	// insert first item with a string that should not be found
	list_insert_after(list, list_create_node(test1),  invalidStr);
	mu_assert(list->first->value == test1, "Wrong first value after first insert.");

	return NULL;
}

char *test_insert_after2()
{
	mu_assert(list->last->value == test1, "Wrong last value after first insert.");

	return NULL;
}

char *test_insert_after3()
{
	mu_assert(list->count == 1, "Wrong count after first insert.");

	return NULL;
}

char *test_insert_after4()
{
	// insert second item with a null string
	list_insert_after(list, list_create_node(test3),  NULL);
	mu_assert(list->first->value == test1, "Wrong first value after second insert.");

	return NULL;
}

char *test_insert_after5()
{
	mu_assert(list->first->next->value == test3, "Wrong forward link after second insert.");

	return NULL;
}

char *test_insert_after6()
{
	mu_assert(list->last->value == test3, "Wrong last value after second insert.");

	return NULL;
}

char *test_insert_after7()
{
	mu_assert(list->last->prev->value == test1, "Wrong backward link after second insert.");

	return NULL;
}

char *test_insert_after8()
{
	mu_assert(list->count == 2, "Wrong count after second insert.");

	return NULL;
}

char *test_insert_after9()
{
	// insert third item after the first
	list_insert_after(list, list_create_node(test2),  test1);
	mu_assert(list->first->value == test1, "Wrong first value after third insert.");

	return NULL;
}

char *test_insert_after10()
{
	mu_assert(list->first->next->value == test2, "Wrong forward link from item 1 after third insert.");

	return NULL;
}

char *test_insert_after11()
{
	mu_assert(list->first->next->next->value == test3, "Wrong forward link from item 2 after third insert.");

	return NULL;
}

char *test_insert_after12()
{
	mu_assert(list->first->next->prev->value == test1, "Wrong backward link from item 2 after third insert.");

	return NULL;
}

char *test_insert_after13()
{
	mu_assert(list->last->value == test3, "Wrong last value after third insert.");

	return NULL;
}

char *test_insert_after14()
{
	mu_assert(list->last->prev->value == test2, "Wrong backward link from item 3 after third insert.");

	return NULL;
}

char *test_insert_after15()
{
	mu_assert(list->count == 3, "Wrong count after second insert.");

	return NULL;
}

char *test_getters()
{
	mu_assert(list_count(list) == list->count, "Wrong count returned by list_count().");

	return NULL;
}

char *test_getters2()
{
	mu_assert(list_first(list) == list->first, "Wrong pointer returned by list_first().");

	return NULL;
}

char *test_getters3()
{
	mu_assert(list_last(list) == list->last, "Wrong pointer returned by list_last().");

	return NULL;
}

char *test_getters4()
{
	mu_assert(list_find(list, invalidStr) == NULL, "Node returned after invalid search.");

	return NULL;
}

char *test_getters5()
{
	mu_assert(list_find(list, test2)->value == test2, "Wrong node returned after search for test2.");

	return NULL;
}

char *test_remove()
{
	temp = list_find(list, test2);
	mu_assert(list_remove_node(list, temp) == test2, "Wrong node value returned removing node 2.");

	return NULL;
}

char *test_remove1()
{
	mu_assert(list->first->next->value == test3, "Wrong forward link from first after removing node 2.");

	return NULL;
}

char *test_remove2()
{
	mu_assert(list->last->prev->value == test1, "Wrong backward link from last after removing node 2.");

	return NULL;
}

char *test_remove3()
{
	mu_assert(list->count == 2, "Wrong count after first remove.");

	return NULL;
}

char *test_remove4()
{
	mu_assert(list_remove_value(list, test3) == test3, "Wrong node value returned removing node 3.");

	return NULL;
}

char *test_remove5()
{
	mu_assert(list->first->next == NULL, "Wrong forward link from first after removing node 3.");

	return NULL;
}

char *test_remove6()
{
	mu_assert(list->last->value == test1, "Wrong last link after removing node 3.");

	return NULL;
}

char *test_remove7()
{
	mu_assert(list->count == 1, "Wrong count after second remove.");

	return NULL;
}

char *test_remove8()
{
	mu_assert(list_remove_value(list, test1) == test1, "Wrong node value returned removing node 1.");

	return NULL;
}

char *test_remove9()
{
	mu_assert(list->first == NULL, "Wrong first link after removing node 1.");

	return NULL;
}

char *test_remove10()
{
	mu_assert(list->last == NULL, "Wrong last link after removing node 1.");

	return NULL;
}

char *test_remove11()
{
	mu_assert(list->count == 0, "Wrong count after third remove.");

    return NULL;
}

char *test_insert_before()
{
	// insert first item with a string that should not be found
	list_insert_before(list, list_create_node(test3),  invalidStr);
	mu_assert(list->first->value == test3, "Wrong first value after first insert.");

    return NULL;
}

char *test_insert_before2()
{
	mu_assert(list->last->value == test3, "Wrong last value after first insert.");

    return NULL;
}

char *test_insert_before3()
{
	mu_assert(list->count == 1, "Wrong count after first insert.");

    return NULL;
}

char *test_insert_before4()
{
	// insert second item with a null string
	list_insert_before(list, list_create_node(test1),  NULL);
	mu_assert(list->first->value == test1, "Wrong first value before second insert.");

    return NULL;
}

char *test_insert_before5()
{
	mu_assert(list->first->next->value == test3, "Wrong forward link before second insert.");

    return NULL;
}

char *test_insert_before6()
{
	mu_assert(list->last->value == test3, "Wrong last value before second insert.");

    return NULL;
}

char *test_insert_before7()
{
	mu_assert(list->last->prev->value == test1, "Wrong backward link before second insert.");

    return NULL;
}

char *test_insert_before8()
{
	mu_assert(list->count == 2, "Wrong count before second insert.");

    return NULL;
}

char *test_insert_before9()
{
	// insert third item before the first.
	list_insert_before(list, list_create_node(test2),  test3);
	mu_assert(list->first->value == test1, "Wrong first value before third insert.");

    return NULL;
}

char *test_insert_before10()
{
	mu_assert(list->first->next->value == test2, "Wrong forward link from item 1 before third insert.");

    return NULL;
}

char *test_insert_before11()
{
	mu_assert(list->first->next->next->value == test3, "Wrong forward link from item 2 before third insert.");

    return NULL;
}

char *test_insert_before12()
{
	mu_assert(list->first->next->prev->value == test1, "Wrong backward link from item 2 before third insert.");

    return NULL;
}

char *test_insert_before13()
{
	mu_assert(list->last->value == test3, "Wrong last value before third insert.");

    return NULL;
}

char *test_insert_before14()
{
	mu_assert(list->last->prev->value == test2, "Wrong backward link from item 3 before third insert.");

    return NULL;
}

char *test_insert_before15()
{
	mu_assert(list->count == 3, "Wrong count before second insert.");

	return NULL;
}

char *test_clear_destroy()
{
	list_clear(list);
	mu_assert(list->first == NULL, "First still points to a ListNode after clearing.");

	return NULL;
}

char *test_clear_destroy2()
{
	mu_assert(list->last == NULL, "Last still points to a ListNode after clearing.");

	return NULL;
}

char *test_clear_destroy3()
{
	mu_assert(list->count == 0, "Item count does not equal 0 after clearing.");

	return NULL;
}

char *test_clear_destroy4()
{
	// Put things back in the list before destroying it.
	list_insert_before(list, list_create_node(test3),  NULL);
	list_insert_before(list, list_create_node(test2),  NULL);
	list_insert_before(list, list_create_node(test1),  NULL);

    list = list_destroy(list);
	mu_assert(list == NULL, "List pointer still exists after destroy function.");

	return NULL;
}

char *test_iterate()
{
	list = list_create();
	list_insert_before(list, list_create_node(test3),  NULL);
	list_insert_before(list, list_create_node(test2),  NULL);
	list_insert_before(list, list_create_node(test1),  NULL);

	// Forwards
	ListNode* testcur = list->first;
	LIST_FOREACH(list, first, next, cur)
	{
		mu_assert(testcur == cur, "Iterator is pointing at wrong node iterating forward.");
		testcur = testcur->next;
	}

	return NULL;
}

char *test_iterate_bw()
{
	list = list_create();
	list_insert_before(list, list_create_node(test3),  NULL);
	list_insert_before(list, list_create_node(test2),  NULL);
	list_insert_before(list, list_create_node(test1),  NULL);

	// Backwards
	ListNode* testcur = list->last;
	LIST_FOREACH(list, last, prev, cur)
	{
		mu_assert(testcur == cur, "Iterator is pointing at wrong node iterating backward.");
		testcur = testcur->prev;
	}

	return NULL;
}

char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_create);
	mu_run_test(test_create_node);
	mu_run_test(test_create_node2);
	mu_run_test(test_insert_after);
	mu_run_test(test_insert_after2);
	mu_run_test(test_insert_after3);
	mu_run_test(test_insert_after4);
	mu_run_test(test_insert_after5);
	mu_run_test(test_insert_after6);
	mu_run_test(test_insert_after7);
	mu_run_test(test_insert_after8);
	mu_run_test(test_insert_after9);
	mu_run_test(test_insert_after10);
	mu_run_test(test_insert_after11);
	mu_run_test(test_insert_after12);
	mu_run_test(test_insert_after13);
	mu_run_test(test_insert_after14);
	mu_run_test(test_insert_after15);
	mu_run_test(test_getters);
	mu_run_test(test_getters2);
	mu_run_test(test_getters3);
	mu_run_test(test_getters4);
	mu_run_test(test_getters5);
	mu_run_test(test_remove);
	mu_run_test(test_remove2);
	mu_run_test(test_remove3);
	mu_run_test(test_remove4);
	mu_run_test(test_remove5);
	mu_run_test(test_remove6);
	mu_run_test(test_remove7);
	mu_run_test(test_remove8);
	mu_run_test(test_remove9);
	mu_run_test(test_remove10);
	mu_run_test(test_remove11);
	mu_run_test(test_insert_before);
	mu_run_test(test_insert_before2);
	mu_run_test(test_insert_before3);
	mu_run_test(test_insert_before4);
	mu_run_test(test_insert_before5);
	mu_run_test(test_insert_before6);
	mu_run_test(test_insert_before7);
	mu_run_test(test_insert_before8);
	mu_run_test(test_insert_before9);
	mu_run_test(test_insert_before10);
	mu_run_test(test_insert_before11);
	mu_run_test(test_insert_before12);
	mu_run_test(test_insert_before13);
	mu_run_test(test_insert_before14);
	mu_run_test(test_insert_before15);
	mu_run_test(test_clear_destroy);
	mu_run_test(test_clear_destroy2);
	mu_run_test(test_clear_destroy3);
	mu_run_test(test_clear_destroy4);
	mu_run_test(test_iterate);
	mu_run_test(test_iterate_bw);

	return NULL;
}

RUN_TESTS(all_tests);