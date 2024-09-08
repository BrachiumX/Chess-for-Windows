#pragma once

#include "Game.h"
#include "Tuple.h"
#include "SDL.h"

class GUI {

private:
	int width = 960;
	Game* game;
	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Rect piece_rect;

	SDL_Texture* BlackKing;
	SDL_Texture* BlackPawn;
	SDL_Texture* BlackBishop;
	SDL_Texture* BlackRook;
	SDL_Texture* BlackKnight;
	SDL_Texture* BlackQueen;

	SDL_Texture* WhiteKing;
	SDL_Texture* WhitePawn;
	SDL_Texture* WhiteBishop;
	SDL_Texture* WhiteRook;
	SDL_Texture* WhiteKnight;
	SDL_Texture* WhiteQueen;

	SDL_Texture* BlackWin;
	SDL_Texture* WhiteWin;
	SDL_Texture* Draw;

	SDL_Rect board_rect;
	SDL_Texture* board;

	SDL_Texture* hightex;
	SDL_Texture* pointtex;

	SDL_Texture* whitePromote;
	SDL_Texture* blackPromote;

	SDL_Rect promote_rect;

	Piece* chosenPiece;

	bool highlight[8][8];
	bool point[8][8];

	bool isEnded;

	string piecesFolder;
	string boardFolder;
	string winScreenFolder;
	string promoteFolder;
	string otherFolder;

	int diffx;
	int diffy;

public:

	GUI();

	void start();

	void draw();

	void process(int positionX, int positionY);

	Tuple getPosition(int positionX, int positionY);

	SDL_Texture* pickTexture(string type, bool side);

	void end();

	void restart();

	void setWidth(int width);

	void setPiecesFolder(string folder);
	void setBoardFolder(string folder);
	void setPromoteFolder(string folder);
	void setWinScreenFolder(string folder);
	void setOtherFolder(string folder);
};