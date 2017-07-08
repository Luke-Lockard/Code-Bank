#include <mazer.h>

/*
	InitRunner simply sets the x and y positions to 1 and the facing to
	North (defined in maze.h) to begin the path search
*/
int InitRunner()
{
	// Not much point in doing anything without a maze.  Otherwise we
	// initialize the runner.
	check(grid != NULL, "Init Warning: maze is not defined.");
	xpos = 1;
	ypos = 1;
	facing = NORTH;
	return true;

error:
	return false;
}

/*
	TurnLeft changes the value of variable 'facing' accordingly,
	pointing the robot in a direction 90 degress counterclockwise from its
	former direction.
	Returns true on success, false on failure.
*/
int TurnLeft()
{
	if (facing == NORTH) {
		facing = WEST;
		return true;
	} else if (facing == WEST) {
		facing = SOUTH;
		return true;
	} else if (facing == SOUTH) {
		facing = EAST;
		return true;
	} else if (facing == EAST) {
		facing = NORTH;
		return true;
	} else {
		return false;
	}
	
}

/*
	TurnRightchanges the value of variable 'facing' accordingly,
	pointing the robot in a direction 90 clockwise from its
	former direction.
	Returns true on success, false on failure.
*/
int TurnRight()
{
	if (facing == NORTH) {
		facing = EAST;
		return true;
	} else if (facing == EAST) {
		facing = SOUTH;
		return true;
	} else if (facing == SOUTH) {
		facing = WEST;
		return true;
	} else if (facing == WEST) {
		facing = NORTH;
		return true;
	} else {
		return false;
	}
}

/*
	IsWall gets the value of the position in front of the robot. If it is a '#',
	then there is a wall. If not, then there is not a wall.
	Returns true if wall, false if not
*/
int IsWall()
{
	check(grid != NULL, "IsWall Warning: maze is not defined.");
	char in_front;
	int index;

	if (facing == NORTH) {
		index = XYToIndex(xpos, ypos - 1);
		in_front = getCharAtIndex(index);
	} else if (facing == EAST) {
		index = XYToIndex(xpos + 1, ypos);
		in_front = getCharAtIndex(index);
	} else if (facing == SOUTH) {
		index = XYToIndex(xpos, ypos + 1);
		in_front = getCharAtIndex(index);
	} else if (facing == WEST) {
		index = XYToIndex(xpos - 1, ypos);
		in_front = getCharAtIndex(index);
	}
	
	if (in_front == '#' || in_front == 'O') {
		return true;
	} else {
		return false;
	}
	
error:
	return true;
}

/*
	MoveForward leaves a breadcrumb where the robot currenty is, then moves the 
	robot in the direction that it is facing.
	Returns true on success, false on error/failure
*/
int MoveForward()
{
	check(grid != NULL, "MoveForward Warning: maze is not defined.");
	int current_pos = XYToIndex(xpos, ypos);
	char c = getCharAtIndex(current_pos);

	if (c == ' ') {
		setCharAtIndex(current_pos, '.');
	} else if (c == '.') {
		setCharAtIndex(current_pos, 'o');
	} else if (c == 'o') {
		setCharAtIndex(current_pos, 'O');
	} else {
		return false;
	}

	if (facing == NORTH) {
		ypos -= 1;
	} else if (facing == SOUTH) {
		ypos += 1;
	} else if (facing == WEST) {
		xpos -= 1;
	} else if (facing == EAST) {
		xpos += 1;
	} else {
		return false;
	}
	
	return true;

error:
	return false;
}

/*
	AtDestination checks if the robot's position is in the lower right of the maze.
	That position is calculated as (gwidth-2, gheight-2)
	IF true, sets position char to 'x', returns true
	IF false, returns false
*/
int AtDestination()
{
	check(grid != NULL, "AtDest Warning: maze is not defined.");
	
	if (xpos == gwidth-2 && ypos == gheight-2) {
		int dest_index = XYToIndex(xpos, ypos);
		setCharAtIndex(dest_index, 'x');
		return true;
	} else {
		return false;
	}
	
error:
	return false;
}
