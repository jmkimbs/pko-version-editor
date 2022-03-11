#include <iostream>
#include <fstream>
#include <vector>
#include <string>


void seekGameVersion(std::fstream &gameRaw) {
	gameRaw.seekp(0x24DA50);
}

void updateGameVersion(std::fstream &gameRaw, int newVersion) {

	std::cout << "Attempting to update Game.exe version to " << newVersion << std::endl;

	seekGameVersion(gameRaw);
	gameRaw.write(reinterpret_cast<char*>(&newVersion), sizeof(newVersion));

}

int getGameVersion(std::fstream &gameRaw) {

	seekGameVersion(gameRaw);

	int currentVersion;
	gameRaw.read(reinterpret_cast<char*>(&currentVersion), sizeof(currentVersion));

	return currentVersion;

}

void printGameVersion(std::fstream &gameRaw) {

	int gameVersion = getGameVersion(gameRaw);
	std::cout << "Game version is " << gameVersion << std::endl;

}

bool tryParseVersion(std::string &input, int &output) {
	try {
		output = std::stoi(input);
	}
	catch (std::exception) {
		return false;
	}

	return true;
}

int requestNewGameVersion() {

	int newVersion;
	std::string inputVersion;

	while (!tryParseVersion(inputVersion, newVersion)) {
		std::cout << "Enter the new version of the game without any decimals " <<
			"(i.e. 1.36 would be 136; 1.38 would be 138)" << std::endl;
			
		std::cin >> inputVersion;
	}

	return newVersion;

}

bool openGameRaw(std::string gamePath, std::fstream &file) {

	bool opened = false;

	file = std::fstream ( gamePath.c_str(), std::ios::binary | std::ios::in | std::ios::out );

	if (file) {
		opened = true;
	}

	return opened;

}

std::string getGamePath() {

	std::string fileName;

	std::cout << "Please enter the relative path of Game.exe" << std::endl;

	std::cin >> fileName;

	return fileName;
}


int main(int argc, char* argv[])
{
	
	std::string gamePath;
	std::fstream gameFile;
	while (!openGameRaw(gamePath, gameFile)) {
		gamePath = getGamePath();
	}

	printGameVersion(gameFile);
	int newVersion = requestNewGameVersion();
	updateGameVersion(gameFile, newVersion);
	printGameVersion(gameFile);

	std::cout << "Update completed" << std::endl;

	return 0;
}