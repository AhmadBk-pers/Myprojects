/*
************************************************************************************************************************
*** In this assignment I have decided to create a base class called unit and every other unit class inherits from it ***
*** and the grid is a two dimension matrix of pointers of unit class												 ***
************************************************************************************************************************
*/
#include <iostream>
#include "Header.h"

const int Setup_count = 9, P1_starting_row = 1, P2_starting_row = 8, P1_playerNumber = 1, P2_playerNumber = 2;

int main()
{
	//creating the instances for the two players
	Player player1(P1_starting_row);
	Player player2(P2_starting_row);

	//creating a grid of pointers
	Unit* Grid[8][8] = { NULL };

	//Setup stage
	SetUp(Grid,player1,player2);

	//Game stage 
	Game(Grid, player1, player2);
}