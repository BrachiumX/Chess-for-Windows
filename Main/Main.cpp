#include <fstream>
#include <string>

#include "GUI.h"

#include "SDL.h"
#include "SDL_image.h"

using namespace std;

const int width = 960;
const int height = 960;

int main(int argc, char* argv[]) {

	GUI gui;

	ifstream inputFile("config.txt");

	if(inputFile.is_open()) {
		string line;

		while(getline(inputFile, line)) {
			if(line.find("Width") != string::npos) {
				gui.setWidth(stoi(line.substr(7)));
			}
			else if(line.find("Pieces") != string::npos) {
				gui.setPiecesFolder(line.substr(9));
			}
			else if(line.find("Board") != string::npos) {
				gui.setBoardFolder(line.substr(8));
			}
			else if(line.find("Promote") != string::npos) {
				gui.setPromoteFolder(line.substr(10));
			}
			else if(line.find("WinScreen") != string::npos) {
				gui.setWinScreenFolder(line.substr(12));
			}
			else if(line.find("Other") != string::npos) {
				gui.setOtherFolder(line.substr(8));
			}

		}
	}
	gui.start();

	return 0;
}
