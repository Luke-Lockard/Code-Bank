/* Project 1 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// used for conversion from degrees to radians
#define PI 3.14159265

int main()
{
	// Welcome message
	printf("Welcome to the Ballistics Calculator\n");

	// Initiate main loop
	// While run == 1, we run the program.
	// The program ends when the user wants to stop calculating ballistics, which then
	// changes the 'run' value to 0, which will end the main loop, and the function will terminate.
	int run = 1;
	while (run == 1) {
		// declare variables
		double height = -1;
		double angle = 100;
		double velocity = 0;
		double g = -9.8; // acceleration of gravity is 9.8 m/s^2
		
		// Ask for an input of height
		printf("\nInput a height (meters) between 0 and 1 mile high (1600m): ");
		// keep asking for the height until an acceptable number is given
		while ((height < 0) || (height > 1600))
		{
			scanf("%lf", &height);
			// Display error messages if the input was bad
			if (height < 0) printf("That's too low, try again: ");
			if (height > 1600) printf("That's too high, try again: ");
	
		}

		// Ask for an input of firing angle between 90 and -90
		printf("Input a Firing Angle (degrees) between -90 and 90: ");
		// keep asking for the angle until an acceptable number is given
		while ((angle < -90) || (angle > 90))
		{
			scanf("%lf", &angle);
			// Display error messages if the input was bad
			if (angle < -90) printf("That's too low, try again: ");
			if (angle > 90) printf("That's too high, try again: ");

		}

		// Ask for an input of Initial Velocity
		printf("Input an Initial Velocity (m/s) greater than 0: ");
		// keep asking for the velocity until an acceptable number is given
		while (velocity <= 0)
		{
			scanf("%lf", &velocity);
			// Display error messages if the input was bad
			if (velocity <= 0) printf("That's too low, try again: ");
		}

		// Now calculate the time and distance to impact
		printf("\nThank you.\n\n");
		printf("Projectile launched at %g m/s, at %g degrees and from %g meters high.\n", velocity, angle, height);
		printf("Calculating time and distance to impact... \n");

		// We need to calculate the initial VERTICAL and HORIZONTAL velocities
		double val = PI / 180; // value to convert angle from degrees to radians
		double vert_velocity = velocity * sin(val * angle);
		double horiz_velocity = velocity * cos(val * angle);

		double t1, t2, t_to_impact;
		double dist_to_impact;

		/* Professor Kelley's Version:
		if (angle >= 0) {
			
			//t1 = 2 * vert_velocity / g; // time to return to same height if firing angle > 0
			//t2 = (height * 16) / (velocity * 15);
			//t_to_impact = t1 + t2;
		}
		*/

		// My version: (Should work for any angle...)
		// displacement formula:
		// -height = vert_velocity*t + -4.9(t)^2
		// Use quadratic formula to solve for time (t):
		// 0 = -4.9(t)^2 + vert_velocity*t + heigth
		// t = (-vert_velocity + sqrt(vert_velocity^2 -4*(-4.9)*height)) / -9.8
		t_to_impact = (-vert_velocity - sqrt( pow(vert_velocity,2) + (4 * 4.9 * height))) / g;
		dist_to_impact = t_to_impact * horiz_velocity;

		// display our solutions
		printf("\nYou fired the projectile at %g m/s at %g degrees from %g meters high.\n", velocity, angle, height);
		printf("The projectile went %g meters for %g seconds before hitting the groud.\n\n", dist_to_impact, t_to_impact);

		// now check if the user wants to calculate another trajectory
		// assume that they respond with bad input
		int incorrect_input = 1;
		// var to save their answer to
		int answer;
		// as long as they input an incorrect answer (anything other than 'y' or 'n'), continue to ask
		while (incorrect_input == 1) {
			printf("Would you like to calculate another trajectory? (1 = yes, 2 = no): ");
			scanf("%d", &answer);
			if (answer == 2) {
				// if they answer no, then the input is acceptable, so we stop this while loop
				incorrect_input = 0;
				// they answered no, so we end the program by changing run to 0, so the main loop terminates.
				run = 0;
				printf("\nThanks for using the Ballistics Calculator. Goodbye\n");
			} else if (answer == 1) {
				// if they answer no, then the input is acceptable, so we stop this while loop
				incorrect_input = 0;
				// they answered yes, so the main loop runs again. (We make sure that run is still 1)
				run = 1;
			} else {
				// any other input keeps this while loop running
				incorrect_input = 1;
				printf("\nSorry, please answer with a '1' or '2'\n\n");
			}
		}
	}
	// exit program
	return 0;
}