#include <string>

//This is the base class for all of the units
class Unit {
public:
	std::string unit_name;
	int Health;					
	int area_of_damage;
	int Damage ;
	int Range;
	int Movement;
	int Ownership;			//This indicates the owner ship of this unit
};

//This is the short range archer class 
class SRA : public Unit {
public:

	//initializing the ownership based on the given number to the constructer
	SRA(int playerNumber) {
		unit_name		= "SRA";
		Health			= 100;
		area_of_damage	= 1;
		Damage			= 20;		
		Range			= 3;
		Movement		= 1;
		Ownership		= playerNumber;
	}

};

//This is the long range archer class 
class LRA : public Unit {
public :

	//initializing the ownership based on the given number to the constructe
	LRA(int playerNumber) {
		unit_name = "LRA";
		Health			= 40;
		area_of_damage	= 9;
		Damage			= 10;
		Range			= 5;
		Movement		= 1;
		Ownership		= playerNumber;
	}
};

//This is the Swordsman class 
class Swordsman : public Unit {
public:

	//initializing the ownership based on the given number to the constructer
	Swordsman(int playerNumber) {
		unit_name		= "Swordsman";
		Health			= 200;
		area_of_damage	= 1;
		Damage			= 30;
		Range			= 1;
		Movement		= 1;
		Ownership		= playerNumber;
	}
};

//This is the Spearman class 
class Spearman : public Unit {
public:

	//initializing the ownership based on the given number to the constructer
	Spearman(int playerNumber) {
		unit_name		= "Spearman";
		Health			= 120;
		area_of_damage	= 1;
		Damage			= 22;
		Range			= 2;
		Movement		= 2;
		Ownership		= playerNumber;
	}
};

//This is the Mage class 
class Mage : public Unit {
public:

	//initializing the ownership based on the given number to the constructer
	Mage(int playerNumber) {
		unit_name		= "Mage";
		Health			= 80;
		area_of_damage	= 4;
		Damage			= 25;
		Range			= 2;
		Movement		= 1;
		Ownership		= playerNumber;
	}
};

//This is the Brute class 
class Brute : public Unit {
public:

	//initializing the ownership based on the given number to the constructer
	Brute(int playerNumber) {
		unit_name		= "Brute";
		Health			= 250;
		area_of_damage	= 1;
		Damage			= 10;
		Range			= 1;
		Movement		= 1;
		Ownership		= playerNumber;
	}
};

//This is the Runner class 
class Runner : public Unit {
public:

	//initializing the ownership based on the given number to the constructer
	Runner(int playerNumber) {
		unit_name		= "Runner";
		Health			= 60;
		area_of_damage	= 1;
		Damage			= 15;
		Range			= 1;
		Movement		= 6;
		Ownership		= playerNumber;
	}
};

//This is the healer class 
class Healer : public Unit {
public:

	//initializing the ownership based on the given number to the constructer
	Healer(int playerNumber) {
		unit_name		= "Healer";
		Health			= 80;
		area_of_damage	= 1;
		Damage			= -15;
		Range			= 4;
		Movement		= 1;
		Ownership		= playerNumber;
	}
};

//This is the player class which holds all the required data to each player
class Player {
public:
	bool firstLRA	= false;
	bool secondLRA	= false;
	bool SRA		= false;
	bool Swordsman	= false;
	bool Spearman	= false;
	bool Mage		= false;
	bool Brute		= false;
	bool Runner		= false;
	bool Healer		= false;
	int StartingRow;
	int player_number;
	Player(int row) {
		StartingRow = row;
		if (StartingRow == 1)
			player_number = 1;
		else
			player_number = 2;
	}
};
