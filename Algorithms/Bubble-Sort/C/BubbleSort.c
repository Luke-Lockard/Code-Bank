#include <stdio.h>
#include <stdlib.h>

// global array holds 100 integers
int nums[100];
// global variable for the amount of numbers in the array
int max;


// Function that handles gathering numbers for the array from user input
void get_nums() {
	// variable to keep track of the position in the array & the number of 
	// values already entered by the user
	int count = 0;
	// fill the array until the specified number of values to input has been reached
	while (count < max) {
		// asks for input
		printf("Please enter an integer number: ");
		// stores input in a variable
		int num;
		scanf("%d", &num);
		// inserts the number into the array
		nums[count] = num;
		// increase the count because we have added a number to the array
		count++;
	} // end while
}

// Function that displays the values in the array
void display_array() {
	// print the first bracket and number: '[ #,'
	printf("[%d,\n", nums[0]);
	// loops only through the positions in the array that have been filled
	// if it looped through the whole array, there would be a long list of '0's at the end
	// the loop ends before the last number, because we want to print that with the ending bracket
	for (int i = 1; i < max-1; i++) {
		// print out the number
		printf(" %d,\n", nums[i]);
	}
	// print the last number with the ending bracket: ' #]'
	printf(" %d]\n", nums[max-1]);
}

// Function sorts the numbers 
// Only sorts the positions that were filled in the array
void bubble_sort() {
	// from the first position to the last filled position in the array
	for (int i = 0; i < max-1; i++) {
		// bubble the number in that position to its proper order in the array
		for (int j = 0; j < max-1-i; j++){
			// if the current number is greater than the next, swap them
			if (nums[j] > nums[j+1]) {
				int temp = nums[j];
				nums[j] = nums[j+1];
				nums[j+1] = temp;
			} // endif
		} // endfor
	} // endfor
}

// main method
int main(int argc, char const *argv[]) {
	// print a welcome/start message
	printf("We need some numbers to sort!\n");
	// ask for the number of values the user would like to have sorted
	printf("How many numbers would you like to sort (maximum of 100)? \n");
	scanf("%d", &max);
	// handle if the number is greater than 100, or a negative
	while ((max > 100) || (max < 0)) {
		printf("Must be an amount between 0 and 100!! ");
		scanf("%d", &max);
	}
	// get the numbers from the user
	get_nums();
	// display the array as is (unordered)
	printf("\nHere are the numbers ordered as they were given:\n");
	display_array();
	// bubble sort the numbers
	printf("\nSorting numbers...\n\n");
	bubble_sort();
	// display the sorted array
	printf("Here are the sorted numbers:\n");
	display_array();
	return 0;
}
