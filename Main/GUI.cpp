#pragma once

#include "GUI.h"
#include "SDL_image.h"

#include <Windows.h>

GUI::GUI() {
	piecesFolder = "Default";
	boardFolder = "Default";
	winScreenFolder = "Default";
	promoteFolder = "Default";
	otherFolder = "Default";
}

void GUI::start() {

	if(width > GetSystemMetrics(SM_CXSCREEN) || width > GetSystemMetrics(SM_CYSCREEN)) {
		if(GetSystemMetrics(SM_CXSCREEN) > GetSystemMetrics(SM_CYSCREEN)) {
			width = GetSystemMetrics(SM_CYSCREEN);
		}
		else {
			width = GetSystemMetrics(SM_CXSCREEN);
		}
	}

	int originwidth = width;

	string path = "Textures\\";

	string piecePath = path + "Pieces\\" + piecesFolder + "\\";
	string boardPath = path + "Board\\" + boardFolder + "\\";
	string winScreenPath = path + "WinScreen\\" + winScreenFolder + "\\";
	string promotePath = path + "Promote\\" + promoteFolder + "\\";
	string otherPath = path + "Other\\" + otherFolder + "\\";

	SetProcessDPIAware();

	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("Chess", (GetSystemMetrics(SM_CXSCREEN) - width) / 2, (GetSystemMetrics(SM_CYSCREEN) - width) / 2, width, width, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

	SDL_SetWindowIcon(window, IMG_Load((piecePath + "white-pawn.png").c_str()));

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	BlackKing = IMG_LoadTexture(renderer, (piecePath + "black-king.png").c_str());
	BlackPawn = IMG_LoadTexture(renderer, (piecePath + "black-pawn.png").c_str());
	BlackBishop = IMG_LoadTexture(renderer, (piecePath + "black-bishop.png").c_str());
	BlackRook = IMG_LoadTexture(renderer, (piecePath + "black-rook.png").c_str());
	BlackKnight = IMG_LoadTexture(renderer, (piecePath + "black-knight.png").c_str());
	BlackQueen = IMG_LoadTexture(renderer, (piecePath + "black-queen.png").c_str());

	WhiteKing = IMG_LoadTexture(renderer, (piecePath + "white-king.png").c_str());
	WhitePawn = IMG_LoadTexture(renderer, (piecePath + "white-pawn.png").c_str());
	WhiteBishop = IMG_LoadTexture(renderer, (piecePath + "white-bishop.png").c_str());
	WhiteRook = IMG_LoadTexture(renderer, (piecePath + "white-rook.png").c_str());
	WhiteKnight = IMG_LoadTexture(renderer, (piecePath + "white-knight.png").c_str());
	WhiteQueen = IMG_LoadTexture(renderer, (piecePath + "white-queen.png").c_str());

	board = IMG_LoadTexture(renderer, (boardPath + "Board.png").c_str());

	hightex = IMG_LoadTexture(renderer, (otherPath + "Highlight.png").c_str());

	pointtex = IMG_LoadTexture(renderer, (otherPath + "Point.png").c_str());

	whitePromote = IMG_LoadTexture(renderer, (promotePath + "whitePromote.png").c_str());
	blackPromote = IMG_LoadTexture(renderer, (promotePath + "blackPromote.png").c_str());

	WhiteWin = IMG_LoadTexture(renderer, (winScreenPath + "whiteWin.png").c_str());
	BlackWin = IMG_LoadTexture(renderer, (winScreenPath + "blackWin.png").c_str());
	Draw = IMG_LoadTexture(renderer, (winScreenPath + "draw.png").c_str());


	bool isRunning = true;
	isEnded = false;
	SDL_Event event;

	game = new Game();
	game->compute();

	int x = width;
	int y = width;

	while(isRunning) {

		diffx = 0;
		diffy = 0;

		SDL_GetWindowSize(window, &x, &y);

		x += x % 8;
		y += y % 8;

		SDL_SetWindowSize(window, x, y);

		if((SDL_GetWindowFlags(window) & SDL_WINDOW_MAXIMIZED) == SDL_WINDOW_MAXIMIZED) {
			SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		}

		if(x > y) {
			width = y;
			diffx = x - y;
		}
		else {
			width = x;
			diffy = y - x;
		}

		promote_rect.x = diffx / 2;
		promote_rect.y = diffy / 2;
		promote_rect.w = width;
		promote_rect.h = width;

		piece_rect.w = width / 8;
		piece_rect.h = width / 8;

		board_rect.x = diffx / 2;
		board_rect.y = diffy / 2;
		board_rect.w = width;
		board_rect.h = width;

		while(SDL_PollEvent(&event) != 0) {
			if(event.type == SDL_QUIT) {
				isRunning = false;
			}
			else if(event.type == SDL_KEYDOWN && event.key.keysym.scancode == 21) {
				restart();
			}
			else if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
				process(event.button.x, event.button.y);
			}
			else if(event.type == SDL_KEYDOWN && event.key.keysym.scancode == 41) {
				SDL_SetWindowFullscreen(window, 0);
				SDL_RestoreWindow(window);
				SDL_SetWindowSize(window, originwidth, originwidth);
				SDL_SetWindowPosition(window, (GetSystemMetrics(SM_CXSCREEN) - originwidth) / 2, (GetSystemMetrics(SM_CYSCREEN) - originwidth) / 2);
			}
		}

		draw();
		SDL_Delay(50);
	}

	SDL_Quit();
}

Tuple GUI::getPosition(int positionX, int positionY) {
	return Tuple((positionX - diffx / 2) / (width / 8), 7 - ((positionY - diffy / 2) / (width / 8)));
}

void GUI::draw() {

	SquareArray<Piece*>* squares = game->getSquares();
	SDL_Texture* texture;

	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, board, NULL, &board_rect);

	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {

			Piece* temp = squares->get(i, j);

			piece_rect.x = (width / 8) * i + diffx / 2;
			piece_rect.y = width - (width / 8) * (j + 1) + diffy / 2;

			if(point[i][j]) {
				SDL_RenderCopy(renderer, pointtex, NULL, &piece_rect);
			}

			if(temp == nullptr) {
				continue;
			}

			if(highlight[i][j]) {
				SDL_RenderCopy(renderer, hightex, NULL, &piece_rect);
			}

			texture = pickTexture(temp->getType(), temp->getSide());

			SDL_RenderCopy(renderer, texture, NULL, &piece_rect);

			if(point[i][j]) {
				SDL_RenderCopy(renderer, pointtex, NULL, &piece_rect);
			}
		}
	}

	if(game->getPromote()) {
		SDL_Texture* promote;

		if(game->getTurn()) {
			promote = whitePromote;
		}
		else {
			promote = blackPromote;
		}
		SDL_RenderCopy(renderer, promote, NULL, &promote_rect);
	}

	if(isEnded) {
		if(game->getTurn() && game->getWhiteKing()->isCheck()) {
			texture = BlackWin;
		}
		else if(!game->getTurn() && game->getBlackKing()->isCheck()) {
			texture = WhiteWin;
		}
		else {
			texture = Draw;
		}
		SDL_RenderCopy(renderer, texture, NULL, &board_rect);
	}

	SDL_RenderPresent(renderer);
}

SDL_Texture* GUI::pickTexture(string type, bool side) {

	if(type == "Pawn") {
		if(side) {
			return WhitePawn;
		}
		return BlackPawn;
	}

	if(type == "King") {
		if(side) {
			return WhiteKing;
		}
		return BlackKing;
	}

	if(type == "Queen") {
		if(side) {
			return WhiteQueen;
		}
		return BlackQueen;
	}

	if(type == "Knight") {
		if(side) {
			return WhiteKnight;
		}
		return BlackKnight;
	}

	if(type == "Bishop") {
		if(side) {
			return WhiteBishop;
		}
		return BlackBishop;
	}

	else {
		if(side) {
			return WhiteRook;
		}
		return BlackRook;
	}
}

void GUI::process(int positionX, int positionY) {

	Tuple pos = getPosition(positionX, positionY);
	int x = pos.getPositionX();
	int y = pos.getPositionY();

	if(isEnded) {

		if(y == 2 || y == 3) {
			if(x >= 2 && x <= 5) {
				restart();
			}
		}
		return;
	}

	if(game->getPromote()) {

		Tuple* promotedest = game->getPromoteDest();

		Piece* king;

		if(game->getTurn()) {
			king = game->getWhiteKing();
		}
		else {
			king = game->getBlackKing();
		}

		if(x == 3 && y == 4) {
			Queen* queen = new Queen(king, game->getSquares(), promotedest, game->getTurn());

			game->removePiece(game->getSquares()->get(promotedest->getPositionX(), promotedest->getPositionY()));
			game->addPiece(queen);
		}
		else if(x == 4 && y == 4) {
			Rook* rook = new Rook(king, game->getSquares(), promotedest, game->getTurn());

			game->removePiece(game->getSquares()->get(promotedest->getPositionX(), promotedest->getPositionY()));
			game->addPiece(rook);
		}
		else if(x == 3 && y == 3) {
			Bishop* bishop = new Bishop(king, game->getSquares(), promotedest, game->getTurn());

			game->removePiece(game->getSquares()->get(promotedest->getPositionX(), promotedest->getPositionY()));
			game->addPiece(bishop);
		}
		else if(x == 4 && y == 3) {
			Knight* knight = new Knight(king, game->getSquares(), promotedest, game->getTurn());

			game->removePiece(game->getSquares()->get(promotedest->getPositionX(), promotedest->getPositionY()));
			game->addPiece(knight);
		}
		else {
			return;
		}

		game->setPromote(false);
		game->changeTurn();
		if(game->compute()) {
			isEnded = true;
		}
		return;
	}

	SquareArray<Piece*>* squares = game->getSquares();

	memset(highlight, 0, sizeof(highlight));
	memset(point, 0, sizeof(point));

	if(chosenPiece == nullptr) {
		chosenPiece = squares->get(pos.getPositionX(), pos.getPositionY());

		if(chosenPiece != nullptr && chosenPiece->getSide() == game->getTurn()) {
			highlight[pos.getPositionX()][pos.getPositionY()] = true;

			LinkedList<Tuple*>* movables = chosenPiece->getMovables();
			Iterator<Tuple*>* iterator = movables->getIterator();
			Tuple* curr = iterator->getNext();

			while(curr != nullptr) {
				point[curr->getPositionX()][curr->getPositionY()] = true;
				curr = iterator->getNext();
			}
		}
		return;
	}

	if(chosenPiece->getSide() != game->getTurn()) {
		chosenPiece = nullptr;
		process(positionX, positionY);
		return;
	}

	LinkedList<Tuple*>* movables = chosenPiece->getMovables();
	Iterator<Tuple*>* iterator = movables->getIterator();
	Tuple* curr = iterator->getNext();

	while(curr != nullptr) {

		if(curr->equals(&pos)) {

			game->movePiece(chosenPiece, new Tuple(curr->getPositionX(), curr->getPositionY()));
			chosenPiece = nullptr;
			if(!game->getPromote()) {
				game->changeTurn();
				if(game->compute()) {
					isEnded = true;
				}
			}

			delete iterator;
			return;
		}
		curr = iterator->getNext();
	}

	chosenPiece = nullptr;
	process(positionX, positionY);
}

void GUI::end() {
	bool isRunning = true;
	SDL_Event event;


	while(isRunning) {
		while(SDL_PollEvent(&event) != 0) {
			if(event.type == SDL_QUIT) {
				isRunning = false;
			}
		}

		draw();
		SDL_Delay(50);
	}

	SDL_Quit();
}

void GUI::restart() {
	delete game;

	game = new Game();
	game->compute();

	isEnded = false;
}

void GUI::setWidth(int width) {
	this->width = width;
}

void GUI::setPiecesFolder(string folder) {
	this->piecesFolder = folder;
}

void GUI::setBoardFolder(string folder) {
	this->boardFolder = folder;
}

void GUI::setPromoteFolder(string folder) {
	this->promoteFolder = folder;
}

void GUI::setWinScreenFolder(string folder) {
	this->winScreenFolder = folder;
}

void GUI::setOtherFolder(string folder) {
	this->otherFolder = folder;
}




