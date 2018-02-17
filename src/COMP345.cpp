// COMP345.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Map.cpp"

void setup() {

	cout << "Setting up game for 2 players..." << endl;
	int numberOfPlayers = 2;
	vector<Player> players;
	for (int i = 0; i < numberOfPlayers; i++) {
		string name = "Player " + to_string(i);
		Player player = Player(name);
		players.push_back(player);
	}

	//Shuffles race banners and badges' index
	srand(time(NULL));
	vector<FantasyRaceBanner>races = { Amazons(),Dwarves(),Elves(),Ghouls(),Halflings(),Trolls() };
	vector<Badge>badges = { Alchemist(),Berserk(),Bivouacking(),DragonMaster(),Fortified(),Heroic() };
	std::random_shuffle(races.begin(), races.end());
	std::random_shuffle(badges.begin(), badges.end());

	for(int i = 0; i < 6; i++)
		cout << i+1 << ". " << badges[i].getName() << " " << races[i].getName() << endl;

	//Tests picks_race()
	cout << "(Assume player 1 selects choice 1)" << endl;
	int selectedRace = 1;
	players.at(0).picks_race(races.at(selectedRace), badges.at(selectedRace));
	/*races.erase(races.begin() + selectedRace);
	badges.erase(badges.begin() + selectedRace);*/
	cout << players.at(1).getName() << " selects " << endl;
}

int main()
{
	//making a new map
	Map g = Map(10, 20);

	//fill up all regions
	g.addRegion("R0");
	g.addRegion("R1");
	g.addRegion("R2");
	g.addRegion("R3");
	g.addRegion("R4");

	// fill up all links
	g.addLink(0, 1);
	g.addLink(0, 2);
	g.addLink(0, 3);
	g.addLink(0, 4);

	// trying to add illegal links
	g.addLink(1, 1);
	g.addLink(5, 4);

	g.linked();

	std::cout << "\n";
	
		setup();

    cout << "Testing reinforcements dice" << std::endl;
    cout << "Rolling die 1..." << std::endl;
    int dice1 = roll();
	cout << "Rolling die 2..." << std::endl;
	int dice2 = roll();
    
    return 0;
}