#include "ghost.h"
#include "SFML/Graphics.hpp"
#include "globals.h"
#include <math.h>
#include<iostream>
using namespace std;

int wallCollide(int x, int y, int dir, int level[28][28]) {


	// First, determine the cell of the 2-d array that the sprite is moving into.
	int new_x = x;
	int new_y = y;
	int new_x1;
	int new_x2;
	int new_x3;
	int new_y1;
	int new_y2;
	int new_y3;

	if (dir == RIGHT) { // Moving Right

	// Check along the far right side of the sprite, plus 4 (the speed we’re moving)
		new_x1 = x + 4 + PACSIZE * 2; //multiplying by 2 since PACSIZE is the radius
		new_x2 = x + 4 + PACSIZE * 2;
		new_x3 = x + 4 + PACSIZE * 2;

		// Check at three points along that edge
		new_y1 = y;
		new_y2 = y + PACSIZE;
		new_y3 = y + PACSIZE * 2;
	}

	else if (dir == DOWN) { //moving down
		new_x1 = x;
		new_x2 = x + PACSIZE;
		new_x3 = x + PACSIZE * 2;

		//Check at three points along that edge
		new_y1 = y + 4 + PACSIZE * 2;
		new_y2 = y + 4 + PACSIZE * 2;
		new_y3 = y + 4 + PACSIZE * 2;

	}

	else if (dir == LEFT) { //moving left
		new_x1 = x - 4;
		new_x2 = x - 4;
		new_x3 = x - 4;

		// Check at three points along that edge
		new_y1 = y;
		new_y2 = y + PACSIZE;
		new_y3 = y + PACSIZE * 2;

	}

	else if (dir == UP) { //moving up
		new_x1 = x;
		new_x2 = x + PACSIZE;
		new_x3 = x + PACSIZE * 2;

		//Check at three points along that edge	
		new_y1 = y - 4;
		new_y2 = y - 4;
		new_y3 = y - 4;

	}

	else return 99; // Or whatever the error condition is going to be.

	// So, now we know that new_x, new_y is the place the sprite is trying to go.
	// Translate this into the 2-d array

	int new_cell_x1 = new_x1 / WALLSIZE;
	int new_cell_x2 = new_x2 / WALLSIZE;
	int new_cell_x3 = new_x3 / WALLSIZE;
	int new_cell_y1 = new_y1 / WALLSIZE;
	int new_cell_y2 = new_y2 / WALLSIZE;
	int new_cell_y3 = new_y3 / WALLSIZE;

	// Check to see if the resulting cell is solid.
	if ((level[new_cell_y1][new_cell_x1] == 1)
		|| (level[new_cell_y2][new_cell_x2] == 1)
		|| (level[new_cell_y3][new_cell_x3] == 1))

	{
		//cout << "collision!";
		return 1;
	}
	else
		//dcout << "no collision.";
		return 0;
}

ghost::ghost() {
	xpos = 0;
	ypos = 0;
	color = 0;
	direction = 0;
	dead = 0;
	speed = 0;
	offset = 0;
}

int ghost::getXpos() {
	return xpos;
}

int ghost::getYpos() {
	return ypos;
}

void ghost::initGhost(int x, int y, int dir, bool dead, int Gspeed, sf::Color color) {
	xpos = x;
	ypos = y;
	color = color;
	direction = dir;
	dead = dead;
	speed = Gspeed;
	offset = 1;
	shape.setRadius(PACSIZE/2);
	shape.setFillColor (color);
}

bool ghost::isdead() {
	return dead;
}

void ghost::drawGhost(sf::RenderWindow& window) {
	shape.setPosition(xpos, ypos);
	window.draw(shape);
}

void ghost::printInfo() {
	cout << "x pos " << xpos << " ypos " << ypos << endl;
	cout << "speed " << speed << endl;
}

bool ghost::getPacman(int x, int y) {
	//if (add some math here) {
	//	cout << "ghost got you!" << endl;
	//	return 1;
	//}

	//else
	return 0;
}

//chase function. x and y are pacman's position.
void ghost::chase1(int x, int y, int level[28][28]) {

	//this is just for testing, used this to get it to work :)
	/*cout << "state is " << direction << endl;
	if (wallCollide(xpos, ypos, LEFT, level))
		cout << "there's a wall to the left of me" << endl;
	else
		cout << "no wall to the left." << endl;
	if (wallCollide(xpos, ypos, UP, level))
		cout << "there's a wall above me" << endl;
	if (wallCollide(xpos, ypos, RIGHT, level))
		cout << "there's a wall to the right of me" << endl;
	else
		cout << "no wall to the right." << endl;
	if (wallCollide(xpos, ypos, DOWN, level))
		cout << "there's a wall below me" << endl;*/


		// Moving LEFT or RIGHT, we check for possibility of turning UP or DOWN
	if ((direction == LEFT) || (direction == RIGHT)) {
		// Can we turn UP?
		if (!wallCollide(xpos, ypos, UP, level)) {
			// Is the player UP?
			if ((y < ypos)) {
				direction = UP;
			}
		}
		if (!wallCollide(xpos, ypos, DOWN, level)) {
			// Is the player DOWN?
			if ((y > ypos)) {
				direction = DOWN;
			}
		}
	}
	// Moving UP or DOWN, we check for possibility of turning UP or DOWN
	else if ((direction == UP) || (direction == DOWN)) {
		// Can we turn LEFT?
		if (!wallCollide(xpos, ypos, LEFT, level)) {
			// Is the player LEFT?
			if ((x < xpos)) {
				direction = LEFT;
			}
		}
		if (!wallCollide(xpos, ypos, RIGHT, level)) {
			// Is the player RIGHT?
			if ((x > xpos)) {
				direction = RIGHT;
			}
		}
	}
	// Final case, if we bump into a wall.
	if (direction == UP && wallCollide(xpos, ypos, UP, level)) { direction = DOWN; }
	else if (direction == DOWN && wallCollide(xpos, ypos, DOWN, level)) { direction = UP; }
	else if (direction == LEFT && wallCollide(xpos, ypos, LEFT, level)) { direction = RIGHT; }
	else if (direction == RIGHT && wallCollide(xpos, ypos, RIGHT, level)) { direction = LEFT; }

	// Once we've decided where to move, do so.
	if (direction == UP) ypos -= 4;
	else if (direction == DOWN) ypos += 4;
	else if (direction == LEFT) xpos -= 4;
	else if (direction == RIGHT) xpos += 4;


}
void ghost::chase2(int x, int y, int level[28][28]) {

		// Moving LEFT or RIGHT, we check for possibility of turning UP or DOWN
	if ((direction == LEFT) || (direction == RIGHT)) {
		// Can we turn UP?
		if (!wallCollide(xpos, ypos, UP, level)) {
			// Is the player UP?
			if ((y < ypos)) {
				direction = UP;
			}
		}
		if (!wallCollide(xpos, ypos, DOWN, level)) {
			// Is the player DOWN?
			if ((y > ypos)) {
				direction = DOWN;
			}
		}
	}
	// Moving UP or DOWN, we check for possibility of turning UP or DOWN
	else if ((direction == UP) || (direction == DOWN)) {
		// Can we turn LEFT?
		if (!wallCollide(xpos, ypos, LEFT, level)) {
			// Is the player LEFT?
			if ((x < xpos)) {
				direction = LEFT;
			}
		}
		if (!wallCollide(xpos, ypos, RIGHT, level)) {
			// Is the player RIGHT?
			if ((x > xpos)) {
				direction = RIGHT;
			}
		}
	}
	// Final case, if we bump into a wall.
	if (direction == UP && wallCollide(xpos, ypos, UP, level)) { direction = DOWN; }
	else if (direction == DOWN && wallCollide(xpos, ypos, DOWN, level)) { direction = UP; }
	else if (direction == LEFT && wallCollide(xpos, ypos, LEFT, level)) { direction = RIGHT; }
	else if (direction == RIGHT && wallCollide(xpos, ypos, RIGHT, level)) { direction = LEFT; }

	// Once we've decided where to move, do so.
	if (direction == UP) ypos -= 4;
	else if (direction == DOWN) ypos += 4;
	else if (direction == LEFT) xpos -= 4;
	else if (direction == RIGHT) xpos += 4;


}
void ghost::chase3(int x, int y, int level[28][28]) {
	//this is just for testing, used this to get it to work :)
	cout << "state is " << direction << endl;
	if (wallCollide(xpos, ypos, LEFT, level))
		cout << "there's a wall to the left of me" << endl;
	else
		cout << "no wall to the left." << endl;
	if (wallCollide(xpos, ypos, UP, level))
		cout << "there's a wall above me" << endl;
	if (wallCollide(xpos, ypos, RIGHT, level))
		cout << "there's a wall to the right of me" << endl;
	else
		cout << "no wall to the right." << endl;
	if (wallCollide(xpos, ypos, DOWN, level))
		cout << "there's a wall below me" << endl;

	// Moving UP or DOWN, we check for possibility of turning UP or DOWN
	if ((direction == DOWN) || (direction == UP)) {
		// Can we turn LEFT?
		if (!wallCollide(xpos, ypos, RIGHT, level)) {
			// Is the player LEFT?
			if ((x > xpos)) {
				direction = RIGHT;
			}
		}
		if (!wallCollide(xpos, ypos, LEFT, level)) {
			// Is the player RIGHT?
			if ((x < xpos)) {
				direction = LEFT;
			}
		}
	}
	// Moving LEFT or RIGHT, we check for possibility of turning UP or DOWN
	else if ((direction == RIGHT) || (direction == LEFT)) {
		// Can we turn UP?
		if (!wallCollide(xpos, ypos, UP, level)) {
			// Is the player UP?
			if ((y < ypos)) {
				direction = UP;
			}
		}
		if (!wallCollide(xpos, ypos, DOWN, level)) {
			// Is the player DOWN?
			if ((y > ypos)) {
				direction = DOWN;
			}
		}
	}
	// Final case, if we bump into a wall.
	if (direction == UP && wallCollide(xpos, ypos, UP, level)) { direction = DOWN; }
	else if (direction == DOWN && wallCollide(xpos, ypos, DOWN, level)) { direction = UP; }
	else if (direction == LEFT && wallCollide(xpos, ypos, LEFT, level)) { direction = RIGHT; }
	else if (direction == RIGHT && wallCollide(xpos, ypos, RIGHT, level)) { direction = LEFT; }

	// Once we've decided where to move, do so.
	if (direction == UP) ypos -= 4;
	else if (direction == DOWN) ypos += 4;
	else if (direction == LEFT) xpos -= 4;
	else if (direction == RIGHT) xpos += 4;


}
void ghost::chase4(int x, int y, int level[28][28]) {
	//this is just for testing, used this to get it to work :)
	cout << "state is " << direction << endl;
	if (wallCollide(xpos, ypos, LEFT, level))
		cout << "there's a wall to the left of me" << endl;
	else
		cout << "no wall to the left." << endl;
	if (wallCollide(xpos, ypos, UP, level))
		cout << "there's a wall above me" << endl;
	if (wallCollide(xpos, ypos, RIGHT, level))
		cout << "there's a wall to the right of me" << endl;
	else
		cout << "no wall to the right." << endl;
	if (wallCollide(xpos, ypos, DOWN, level))
		cout << "there's a wall below me" << endl;

	// Moving UP or DOWN, we check for possibility of turning UP or DOWN
	if ((direction == DOWN)) {
		// Can we turn LEFT?
		if (!wallCollide(xpos, ypos, RIGHT, level)) {
			// Is the player LEFT?
			if ((x < xpos)) {
				direction = RIGHT;
			}
		}
	}
	else if ((direction == UP)) {
		// Can we turn UP?
		if (!wallCollide(xpos, ypos, LEFT, level)) {
			// Is the player DOWN?
			if ((y < ypos)) {
				direction = LEFT;
			}
		}
	}
	// Moving LEFT or RIGHT, we check for possibility of turning UP or DOWN
	else if ((direction == LEFT)) {
		// Can we turn UP?
		if (!wallCollide(xpos, ypos, DOWN, level)) {
			// Is the player DOWN?
			if ((y > ypos)) {
				direction = DOWN;
			}
		}
	}
	else if ((direction == RIGHT)) {
		// Can we turn UP?
		if (!wallCollide(xpos, ypos, UP, level)) {
			// Is the player DOWN?
			if ((y < ypos)) {
				direction = UP;
			}
		}
	}
	// Final case, if we bump into a wall.
	if (direction == UP && wallCollide(xpos, ypos, UP, level)) { direction = DOWN; }
	else if (direction == DOWN && wallCollide(xpos, ypos, DOWN, level)) { direction = UP; }
	else if (direction == LEFT && wallCollide(xpos, ypos, LEFT, level)) { direction = RIGHT; }
	else if (direction == RIGHT && wallCollide(xpos, ypos, RIGHT, level)) { direction = LEFT; }

	// Once we've decided where to move, do so.
	if (direction == UP) ypos -= 4;
	else if (direction == DOWN) ypos += 4;
	else if (direction == LEFT) xpos -= 4;
	else if (direction == RIGHT) xpos += 4;


}
