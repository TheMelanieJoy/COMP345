#include <ctime>
#include <vector>
#include <iostream>
using namespace std;

std::vector<int> roll(int quantity) {
	std::vector<int> diceSet;
	for (int i = 0; i < quantity; i++) {
		srand(time(NULL));
		int dieValue = rand() % 6 + 1;
		//3 die faces are blank
		/*if(dieValue > 3)
		dieValue = 0;*/

		cout << "You rolled a " << dieValue << "." << std::endl;
		diceSet.push_back(dieValue);
	}

	return diceSet;
}

int diceSum(std::vector<int> set) {
	int sum = 0;
	for (int value : set)
		sum += value;
	return sum;
}