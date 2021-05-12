#include "classes.cpp"
#include <iostream>

const int Setup_count = 9, P1_starting_row = 1, P2_starting_row = 8, P1_playerNumber = 1, P2_playerNumber = 2;

// Set up stage functions
//This function goes through the units of the player and checks the unselected units and prints them
void print_avaliable_pieces_toset(Player P)
{
	if (P.firstLRA == false)
		std::cout << "1.firstLRA"	<< std::endl;
	if (P.secondLRA == false)
		std::cout << "2.secondLRA"	<< std::endl;
	if (P.SRA == false)
		std::cout << "3.SRA"		<< std::endl;
	if (P.Swordsman == false)
		std::cout << "4.Swordsman"	<< std::endl;
	if (P.Spearman == false)
		std::cout << "5.Spearman"	<< std::endl;
	if (P.Mage == false)
		std::cout << "6.Mage"		<< std::endl;
	if (P.Brute == false)
		std::cout << "7.Brute"		<< std::endl;
	if (P.Runner == false)
		std::cout << "8.Runner"		<< std::endl;
	if (P.Healer == false)
		std::cout << "9.Healer"		<< std::endl;
}

//This function checks if the unit required is unselected and then checks if it is in the availble range of position and finally checks if the place is taken or not
bool check_avalability(Player P, int unit_number, char colum_position, int row_position, Unit* Grid[8][8])
{
	//checking if the unit required is unselected
	switch (unit_number)
	{
	case 1:
		if (P.firstLRA)
			return false;
		break;
	case 2:
		if (P.secondLRA)
			return false;
		break;
	case 3:
		if (P.SRA)
			return false;
		break;
	case 4:
		if (P.Swordsman)
			return false;
		break;
	case 5:
		if (P.Spearman)
			return false;
		break;
	case 6:
		if (P.Mage)
			return false;
		break;
	case 7:
		if (P.Brute)
			return false;
		break;
	case 8:
		if (P.Runner)
			return false;
		break;
	case 9:
		if (P.Healer)
			return false;
		break;
	default:
		break;
	}

	//checks if it is in the availble range of position and finally checks if the place is taken or not
	if (P.StartingRow == 1 && row_position <= 2) {							//checking the placement for the first player
		if (Grid[row_position - 1][colum_position - 'A'] == NULL)			//checking if the position is taken or not
			return true;
		else
			return false;
	}
	else if (P.StartingRow == 8 && row_position >= 7) {						//checking the placement for the first player
		if (Grid[row_position - 1][colum_position - 'A'] == NULL)			//checking if the position is taken or not
			return true;
		else
			return false;
	}else
		return false;
}

//This funtion takes the responsiblity of creating the appropriate unit based on the given number
Unit* create_unit(Player &P, int unit_number, char colum_position, int row_position, int player_number)
{
	//Deciding which unit type to create based on the choice
	//Here the alocation was made in the heap with new operater because I want the class to stay available outside of this scope
	switch (unit_number)
	{
	case 1:
	{
		Unit* LRA1 = new LRA(player_number);
		P.firstLRA = true;
		return LRA1;
		break;
	}
	case 2:
	{
		Unit* LRA2 = new LRA(player_number);
		P.secondLRA = true;
		return LRA2;
		break;
	}
	case 3:
	{
		Unit* SRA1 = new SRA(player_number);
		P.SRA = true;
		return SRA1;
		break;
	}
	case 4:
	{
		Unit* Swordsman1 = new Swordsman(player_number);
		P.Swordsman = true;
		return Swordsman1;
		break;
	}
	case 5:
	{
		Unit* Spearman1 = new Spearman(player_number);
		P.Spearman = true;
		return Spearman1;
		break;
	}
	case 6:
	{
		Unit* Mage1 = new Mage(player_number);
		P.Mage = true;
		return Mage1;
		break;
	}
	case 7:
	{
		Unit* Brute1 = new Brute(player_number);
		P.Brute = true;
		return Brute1;
		break;
	}
	case 8:
	{
		Unit* Runner1 = new Runner(player_number);
		P.Runner = true;
		return Runner1;
		break;
	}
	case 9:
	{
		Unit* Healer1 = new Healer(player_number);
		P.Healer = true;
		return Healer1;
		break;
	}
	default:
		break;
	}
}

//This function prints the grid 
void print_grid(Unit* Grid[8][8])
{
	//Printing the first row (chars row)
	std::cout << "\t";
	for (char row = 'A'; row < 'I'; row++)
	{
		std::cout << row << "\t";
	}
	std::cout << "\n";


	for (int i = 0; i < 8; i++)
	{

		//printing the first colunm
		std::cout << i + 1 << "\t";

		//Printing the whole units
		for (int j = 0; j < 8; j++)
		{
			if (Grid[i][j] == NULL)
				std::cout << "* \t";
			else {
				//Printing the name of the unit addition to the player that owns that unit
				if (Grid[i][j]->unit_name == "LRA")
					std::cout << "LRA(" << Grid[i][j]->Ownership << ")\t";
				if (Grid[i][j]->unit_name == "SRA")
					std::cout << "SRA(" << Grid[i][j]->Ownership << ")\t";
				if (Grid[i][j]->unit_name == "Swordsman")
					std::cout << "Swrd(" << Grid[i][j]->Ownership << ")\t";
				if (Grid[i][j]->unit_name == "Spearman")
					std::cout << "Spr(" << Grid[i][j]->Ownership << ")\t";
				if (Grid[i][j]->unit_name == "Mage")
					std::cout << "Mge(" << Grid[i][j]->Ownership << ")\t";
				if (Grid[i][j]->unit_name == "Brute")
					std::cout << "Brt(" << Grid[i][j]->Ownership << ")\t";
				if (Grid[i][j]->unit_name == "Runner")
					std::cout << "Rnr(" << Grid[i][j]->Ownership << ")\t";
				if (Grid[i][j]->unit_name == "Healer")
					std::cout << "Hlr(" << Grid[i][j]->Ownership << ")\t";

			}
		}
		std::cout << "\n";
	}
}

//This function is resposible for the set up of the board
void SetUp(Unit* Grid[8][8], Player player1, Player player2)
{
	//waiting untill completing the turns
	for (int turnCount = 0; turnCount < Setup_count; turnCount++)
	{
		//The cordinates and the unit number as displayed
		int row_position, unit_number;
		char colum_position;

		//Printing the instructions for the first player
		std::cout << "Player 1 turn Please chosse the number of which unit you want to place followed by the position for example 2 A 2" << std::endl;
		print_avaliable_pieces_toset(player1);
		std::cin >> unit_number >> colum_position >> row_position;

		//checking if the input is valid
		while (!check_avalability(player1, unit_number, colum_position, row_position, Grid))  
		{
			//warrning the player that there is an error and give him another chance to type the input
			std::cout << "ERROR!Player 1 turn Please choose the number of which unit you want to place followed by the position for example 2 A 2" << std::endl;
			print_avaliable_pieces_toset(player1);
			std::cin >> unit_number >> colum_position >> row_position;
						
			//checking the availibility again
			check_avalability(player1, unit_number, colum_position, row_position, Grid);
		}

		//Setting the player in the selected position
		Grid[row_position - 1][colum_position - 'A'] = create_unit(player1, unit_number, colum_position, row_position, P1_playerNumber);

		//printing the whole grid properly
		print_grid(Grid);

		//Printing the instructions for the second player
		std::cout << "Player 2 turn Please chosse the number of which unit you want to place followed by the position for example 2 A 2" << std::endl;
		print_avaliable_pieces_toset(player2);
		std::cin >> unit_number >> colum_position >> row_position;

		//checking if the input is valid
		while (!check_avalability(player2, unit_number, colum_position, row_position, Grid))
		{
			//warrning the player that there is an error and give him another chance to type the input
			std::cout << "ERROR!Player 2 turn Please chosse the number of which unit you want to place followed by the position for example 2 A 2" << std::endl;
			print_avaliable_pieces_toset(player2);
			std::cin >> unit_number >> colum_position >> row_position;

			//checking the availibility again
			check_avalability(player1, unit_number, colum_position, row_position, Grid);
		}

		//Setting the unit in the selected position
		Grid[row_position - 1][colum_position - 'A'] = create_unit(player2, unit_number, colum_position, row_position, P2_playerNumber);

		//printing the whole grid properly
		print_grid(Grid);
	}
}



//Game stage functions
//This function prints the stats of all the units in the grid 
void print_all_stats(Unit* Grid[8][8])
{
	//Going throug the whole grid and printing the stats of each unit
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (Grid[i][j] != NULL)
			{
				std::cout << "**********************************" << std::endl;
				std::cout << "** Unit name \t\t"		<< Grid[i][j]->unit_name			<< "\t**" << std::endl;
				std::cout << "** Health \t\t"			<< Grid[i][j]->Health				<< "\t**" << std::endl;
				std::cout << "** Area of damage \t"		<< Grid[i][j]->area_of_damage		<< "\t**" << std::endl;
				std::cout << "** Damage \t\t"			<< Grid[i][j]->Damage				<< "\t**" << std::endl;
				std::cout << "** Range \t\t"			<< Grid[i][j]->Range				<< "\t**" << std::endl;
				std::cout << "** Movement \t\t"			<< Grid[i][j]->Movement				<< "\t**" << std::endl;
				std::cout << "** Ownership \t\tPlayer"	<< Grid[i][j]->Ownership			<< "\t**" << std::endl;
				std::cout << "**********************************"	<< std::endl;
			}
		}
}

//This function checks if the other player lost
bool check_winning(int otherplayernumber, Unit* Grid[8][8])
{
	//This loop checks if there is any unit left of the other player units
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (Grid[i][j] != NULL)
				if (Grid[i][j]->Ownership == otherplayernumber)						//here we are checking if there is any unit left of the other player units
					return false;

	return true;
}

//This function checks if the move requested is valid
bool check_move_validity(Player P, Unit* Grid[8][8], int old_row_position, int new_row_position, char old_colum_position, char new_colum_position)
{
	//Calculate the requested blocks to move
	int row_move_range = abs(old_row_position - new_row_position);
	int colum_move_range = abs(old_colum_position - new_colum_position);

	//Checking if the new position within the range of grid
	if ((new_row_position < 8) && (new_colum_position < 'I'))
	{
		//check if there is a piece in this position
		if (Grid[old_row_position - 1][old_colum_position - 'A'] != NULL)
		{
			//Check if the piece requested to be moved is actually owned by the player
			if (Grid[old_row_position - 1][old_colum_position - 'A']->Ownership == P.player_number)
			{
				if (Grid[new_row_position - 1][new_colum_position - 'A'] == NULL)
				{
					//Check if  the requesed position within the right range
					if ((row_move_range <= Grid[old_row_position - 1][old_colum_position - 'A']->Movement) && (colum_move_range <= Grid[old_row_position - 1][old_colum_position - 'A']->Movement))
						return true;
					else
					{
						//Error massege out of range
						std::cout << "ERROR!! The requested position is out of range!! this piece is allowed to move only" << Grid[old_row_position - 1][old_colum_position - 'A']->Movement << "steps only" << std::endl;
						return false;
					}
				}
				else
				{
					//Error massege requested position is not empty
					std::cout << "ERROR!! Requested position is not empty" << std::endl;
					return false;
				}
			}
			else {
				//Error massege ownership error
				std::cout << "ERROR!! This piece is not owned by you" << std::endl;
				return false;
			}

		}
		else {
			//Error massege not existed piece
			std::cout << "ERROR!! There is no piece in this postion" << std::endl;
			return false;
		}
	}
	else {
		//Error massege requested position is out of grid range
		std::cout << "ERROR!! Requested position is out of grid range" << std::endl;
		return false;
	}
}

bool check_attack_validity(Player P, Unit* Grid[8][8], int unit_row_position, int attack_row_position, char unit_colum_position, char attack_colum_position)
{
	//Calculate the requested blocks to move
	int row_attack_range = abs(unit_row_position - attack_row_position);
	int colum_attack_range = abs(unit_colum_position - attack_colum_position);

	//Checking if the attacked position within the range of grid
	if ((attack_row_position - 1 < 8) && (attack_colum_position - 'A' < 'I'))
	{
		//check if there is a piece in this position
		if (Grid[unit_row_position - 1][unit_colum_position - 'A'] != NULL)
		{
			//Check if the piece requested to be moved is actually owned by the player
			if (Grid[unit_row_position - 1][unit_colum_position - 'A']->Ownership == P.player_number)
			{
				//Check if  the requesed position within the right range
				if ((row_attack_range <= Grid[unit_row_position - 1][unit_colum_position - 'A']->Range) && (colum_attack_range <= Grid[unit_row_position - 1][unit_colum_position - 'A']->Range))
					return true;
				else
				{
					//Error massege out of range
					std::cout << "ERROR!! The requested position is out of range!! this piece is allowed to attack only" << Grid[unit_row_position - 1][unit_colum_position - 'A']->Range << "steps only" << std::endl;
					return false;
				}

			}
			else {
				//Error massege ownership error
				std::cout << "ERROR!! This piece is not owned by you" << std::endl;
				return false;
			}

		}
		else {
			//Error massege not existed piece
			std::cout << "ERROR!! There is no piece in this postion" << std::endl;
			return false;
		}
	}
	else {
		//Error massege requested position is out of grid range
		std::cout << "ERROR!! Requested position is out of grid range" << std::endl;
		return false;
	}
}

//This function moves the requested unit to the requested position 
bool Move_unit(Player P, Unit* Grid[8][8])
{
	int old_row_position,new_row_position;
	char old_colum_position,new_colum_position;
	bool Move_is_valid;

	//Printing instuctions and getting the input
	std::cout << "Please enter the position of the unit that you want to move followed by the new position." << std::endl;
	std::cin >> old_colum_position >> old_row_position >> new_colum_position >> new_row_position;

	//Checking if the move is valid
	Move_is_valid = check_move_validity(P, Grid,old_row_position, new_row_position, old_colum_position, new_colum_position);
	
	//Making the move if it is valid
	if (Move_is_valid)
	{
		//Moving the unit from the old postion to the new one
		Grid[new_row_position - 1][new_colum_position - 'A'] = Grid[old_row_position - 1][old_colum_position - 'A'];
		
		//Removing the unit from the old position
		Grid[old_row_position - 1][old_colum_position - 'A'] = NULL;
		return true;
	}
	else
		return false;
}

//This funtion deals damage to the enemy units for 1 square
void deal_damage_1sq(Player P, Unit* Grid[8][8], int unit_row_position, int attack_row_position, char unit_colum_position, char attack_colum_position)
{
	//Checking that the attacked square is not empty
	if (Grid[attack_row_position - 1][attack_colum_position - 'A'] != NULL)
	{
		//Checking if the attacked unit is not an owned by the attacking player
		if (Grid[attack_row_position - 1][attack_colum_position - 'A']->Ownership != P.player_number)
		{
			//Dealing damage to the attecked unit by the amount of damage of the attacking unit
			Grid[attack_row_position - 1][attack_colum_position - 'A']->Health -= Grid[unit_row_position - 1][unit_colum_position - 'A']->Damage;
		}
	}
	else
		std::cout << "The attacked square is empty!!" << std::endl;

}

//This funtion deals damage to the enemy units for 2*2 squares
void deal_damage_4sq(Player P, Unit* Grid[8][8], int unit_row_position, int attack_row_position, char unit_colum_position, char attack_colum_position)
{
	//Going through the attack area
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			//checking if the attack area within the grid
			if (((attack_row_position - 1 + i)<8)&& ((attack_colum_position - 'A' + j) < 8))
			{
				//Checking if the attacked square is not empty
				if (Grid[attack_row_position - 1 + i][attack_colum_position - 'A' + j] != NULL)
				{
					//Checking if the attacked unit is not an owned by the attacking player
					if (Grid[attack_row_position - 1 + i][attack_colum_position - 'A' + j]->Ownership != P.player_number)
					{
						//Dealing damage to the attecked unit by the amount of damage of the attacking unit
						Grid[attack_row_position - 1 + i][attack_colum_position - 'A' + j]->Health -= Grid[unit_row_position - 1][unit_colum_position - 'A']->Damage;
					}
				}
			}
		}
	}

}

//This funtion deals damage to the enemy units for 3*3 squares
void deal_damage_9sq(Player P, Unit* Grid[8][8], int unit_row_position, int attack_row_position, char unit_colum_position, char attack_colum_position)
{
	//Going through the attack area
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			//checking if the attack area within the grid
			if (((attack_row_position - 1 + i) < 8) && ((attack_colum_position - 'A' + j) < 8))
			{
				//Checking if the attacked square is not empty
				if (Grid[attack_row_position - 1 + i][attack_colum_position - 'A' + j] != NULL)
				{
					//Checking if the attacked unit is not an owned by the attacking player
					if (Grid[attack_row_position - 1 + i][attack_colum_position - 'A' + j]->Ownership != P.player_number)
					{
						//Dealing damage to the attecked unit by the amount of damage of the attacking unit
						Grid[attack_row_position - 1 + i][attack_colum_position - 'A' + j]->Health -= Grid[unit_row_position - 1][unit_colum_position - 'A']->Damage;
					}
				}
			}
		}
	}

}

//This funtion deals damage to the enemy units
void deal_damage(Player P, Unit* Grid[8][8], int unit_row_position, int attack_row_position, char unit_colum_position, char attack_colum_position)
{
	//Dealing damage based on area of damage
	switch (Grid[unit_row_position - 1][unit_colum_position - 'A']->area_of_damage)
	{
	//Dealing damge on 1 square
	case 1:
		deal_damage_1sq(P, Grid, unit_row_position, attack_row_position, unit_colum_position, attack_colum_position);
		break;
	//Dealing damge on 2*2 square (Mage)
	case 4:
		deal_damage_4sq(P, Grid, unit_row_position, attack_row_position, unit_colum_position, attack_colum_position);
		break;
	//Dealing damge on 3*3 square (LRA)
	case 9:
		deal_damage_9sq(P, Grid, unit_row_position, attack_row_position, unit_colum_position, attack_colum_position);
		break;

	default:
		break;
	}

}

//Checking the dead units and the removing them
void remove_dead_bodies(Unit* Grid[8][8])
{
	//Going throug the whole grid and removing the dead units
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			//Checking if there is a unit
			if (Grid[i][j] != NULL)
			{
				//Checking the health
				if ((Grid[i][j]->Health) <= 0)
				{
					//Deleting the unit (releasing it from the heap)
					delete Grid[i][j];
					Grid[i][j] = NULL;
				}
			}
		}
}

//This function attacks the units
bool Attack_unit(Player P, Unit* Grid[8][8]) {
	int unit_row_position, attack_row_position;
	char unit_colum_position, attack_colum_position;
	bool Attack_is_valid;

	//Printing instuctions and getting the input
	std::cout << "Please enter the position of the unit that you want to attack with followed by the position of the block that you want to attack." << std::endl;
	std::cin >> unit_colum_position >> unit_row_position >> attack_colum_position >> attack_row_position;

	//Checking if the attack is valid
	Attack_is_valid = check_attack_validity(P, Grid, unit_row_position, attack_row_position, unit_colum_position, attack_colum_position);

	//Making the attack if it is valid
	if (Attack_is_valid)
	{
		//Dealing the damage
		deal_damage(P, Grid, unit_row_position, attack_row_position, unit_colum_position, attack_colum_position);

		//removing the dead units
		remove_dead_bodies(Grid);

		return true;
	}
	else
		return false;

}

//This function responsible for the plays of each player
void play(Player P, Unit* Grid[8][8])
{
	int choice;
	int num_of_plays = 0;

	//giving each player two play in each turn
	while (num_of_plays != 2)
	{
		//Printing the gridd
		print_grid(Grid);

		//Printing the choices for the player to make
		std::cout << "Player ";
		//Printing the number of player
		if (P.StartingRow == 1)
			std::cout << 1;
		else
			std::cout << 2;
		std::cout << "please choose:"						<< std::endl;
		std::cout << "1. Moving a unit"						<< std::endl;
		std::cout << "2. Attacking with unit"				<< std::endl;
		std::cout << "3. Print the stats of all the units"	<< std::endl;
		std::cin >> choice;

		//selection the appropriate play based on the player choice
		switch (choice)
		{
		case 1:
		{
			//Checking if the move was performed
			if (Move_unit(P, Grid))
				num_of_plays += 1;
			break;
		}
		case 2:
		{
			//Checking if the attack was performed
			if (Attack_unit(P, Grid))
				num_of_plays += 1;
			break;
		}
		case 3:
		{
			//Printing all of the stats of all the units
			print_all_stats(Grid);
			break;
		}
		default:
			std::cout << "Wrong input " << std::endl;
			break;
		}

	}
}

//This funtion is the game stage
void Game(Unit* Grid[8][8], Player player1, Player player2)
{
	bool game_finished = false;

	while (!game_finished)
	{

		//Start player 1 turn
		play(player1, Grid);

		//checking if Player 1 won
		game_finished = check_winning(P2_playerNumber, Grid);
		if (game_finished)
		{
			std::cout << "Game over Player 1 won the game" << std::endl;
			break;
		}

		//Start player 1 turn
		play(player2, Grid);

		//checking if Player 2 won
		game_finished = check_winning(P1_playerNumber, Grid);
		if (game_finished)
		{
			std::cout << "Game over Player 2 won the game" << std::endl;
			break;
		}
	}
}