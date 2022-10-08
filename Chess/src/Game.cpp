#pragma once
#include <iostream>
#include <vector>
#include "Piece.h"
#include "Game.h"

class Game {
public:
	Game() {
		std::cout << "Setting Layout" << std::endl;
		setStandardLayout();
	}
	~Game() {
		delete[] & piecePositions;
	}
	std::vector<struct moveOption>* getValidMoves(Piece* piece, bool directKingCheck = true) {
		std::vector<struct moveOption>* returnVector = new std::vector<struct moveOption>;

		std::tuple<int, int> location = piece->getLocation();
		int x = std::get<0>(location);
		int y = std::get<1>(location);

		Teams opponent;
		if (piece->getTeam() == Teams::Black) {
			opponent = Teams::White;
		}
		else if (piece->getTeam() == Teams::White) {
			opponent = Teams::Black;
		}

		switch (piece->getType()) {

			// Pawn Moving Logic
			case (PieceType::Pawn):
			{
				Pawn* p = (Pawn*)piece;

				if (!p->getHasMoved()) {
					if (y + 2 <= 7 && piecePositions[x][y + 2]->getType() == PieceType::Empty) {
						returnVector->emplace_back(p, x, y + 2 );
					}
				}
				if (y + 1 <= 7 && piecePositions[x][y + 1]->getType() == PieceType::Empty) {
					returnVector->emplace_back(p,  x, y + 1 );
				}
				if (y + 1 <= 7 && x + 1 <= 7 && piecePositions[x + 1][y + 1]->getType() != PieceType::Empty && piecePositions[x + 1][y + 1]->getTeam() == opponent) {
					returnVector->emplace_back(p,  x + 1, y + 1 );
				}
				if (y + 1 <= 7 && x - 1 >= 0 && piecePositions[x - 1][y + 1]->getType() != PieceType::Empty && piecePositions[x - 1][y + 1]->getTeam() == opponent ) {
					returnVector->emplace_back(p,  x - 1, y + 1 );
				}
				struct enPassant ep = p->getEnPassant();
				if (ep.valid == true) {
					returnVector->emplace_back(p, ep.x, ep.y);
				}
			}
			break;

			// Rook Moving Logic
			case (PieceType::Rook):
			{
				getValidFileRankMoves(returnVector, opponent, piece);
			}
			break;

			// Knight Moving Logic
			case (PieceType::Knight):
			{
				if (x + 2 <= 7 && y + 1 <= 7 && (piecePositions[x + 2][y + 1]->getType() == PieceType::Empty || piecePositions[x + 2][y + 1]->getTeam() == opponent)) {
					returnVector->emplace_back(piece, x + 2, y + 1);
				}
				if (x + 2 <= 7 && y - 1 >= 0 && (piecePositions[x + 2][y - 1]->getType() == PieceType::Empty || piecePositions[x + 2][y - 1]->getTeam() == opponent)) {
					returnVector->emplace_back(piece, x + 2, y - 1);
				}
				if (x - 2 >= 0 && y + 1 <= 7 && (piecePositions[x - 2][y + 1]->getType() == PieceType::Empty || piecePositions[x - 2][y + 1]->getTeam() == opponent)) {
					returnVector->emplace_back(piece, x - 2, y + 1);
				}
				if (x - 2 >= 0 && y - 1 >= 0 && (piecePositions[x - 2][y - 1]->getType() == PieceType::Empty || piecePositions[x - 2][y - 1]->getTeam() == opponent)) {
					returnVector->emplace_back(piece, x - 2, y - 1);
				}
				if (x + 1 <= 7 && y + 2 <= 7 && (piecePositions[x + 1][y + 2]->getType() == PieceType::Empty || piecePositions[x + 1][y + 2]->getTeam() == opponent)) {
					returnVector->emplace_back(piece, x + 1, y + 2);
				}
				if (x + 1 <= 7 && y - 2 >= 0 && (piecePositions[x + 1][y - 2]->getType() == PieceType::Empty || piecePositions[x + 1][y - 2]->getTeam() == opponent)) {
					returnVector->emplace_back(piece, x + 1, y - 2);
				}
				if (x - 1 >= 0 && y + 2 <= 7 && (piecePositions[x - 1][y + 2]->getType() == PieceType::Empty || piecePositions[x - 1][y + 2]->getTeam() == opponent)) {
					returnVector->emplace_back(piece, x - 1, y + 2);
				}
				if (x - 1 >= 0 && y - 2 >= 0 && (piecePositions[x - 1][y - 2]->getType() == PieceType::Empty || piecePositions[x - 1][y - 2]->getTeam() == opponent)) {
					returnVector->emplace_back(piece, x - 1, y - 2);
				}
			}
			break;

			// Bishop Moving Logic
			case (PieceType::Bishop):
			{
				getValidDiagonalMoves(returnVector, opponent, piece);
			}
			break;

			// King Moving Logic
			case (PieceType::King):
			{
				if (x + 1 <= 7 && (piecePositions[x + 1][y]->getType() == PieceType::Empty || piecePositions[x + 1][y]->getTeam() == opponent))  {
					if (directKingCheck) {
						if (checkForCheck(struct location(x + 1, y), opponent)  == false) {
							returnVector->emplace_back(piece, x + 1, y);
						}
					}
					else {
						returnVector->emplace_back(piece, x + 1, y);
					}
				}
				if (x - 1 >= 0 && (piecePositions[x - 1][y]->getType() == PieceType::Empty || piecePositions[x - 1][y]->getTeam() == opponent)) {
					if (directKingCheck) {
						if (checkForCheck(struct location(x - 1, y), opponent) == false) {
							returnVector->emplace_back(piece, x - 1, y);
						}
					}
					else {
						returnVector->emplace_back(piece, x - 1, y);
					}
				}
				if (y + 1 <= 7 && (piecePositions[x][y + 1]->getType() == PieceType::Empty || piecePositions[x][y + 1]->getTeam() == opponent)) {
					if (directKingCheck) {
						if (checkForCheck(struct location(x, y + 1), opponent) == false) {
							returnVector->emplace_back(piece, x, y + 1);
						}
					}
					else {
						returnVector->emplace_back(piece, x, y + 1);
					}
				}
				if (y - 1 >= 0 && (piecePositions[x][y - 1]->getType() == PieceType::Empty || piecePositions[x][y - 1]->getTeam() == opponent)) {
					if (directKingCheck) {
						if (checkForCheck(struct location(x, y - 1), opponent) == false) {
							returnVector->emplace_back(piece, x, y - 1);
						}
					}
					else {
						returnVector->emplace_back(piece, x, y - 1);
					}
				}
				if (x + 1 <= 7 && y + 1 <= 7 && (piecePositions[x + 1][y + 1]->getType() == PieceType::Empty || piecePositions[x + 1][y + 1]->getTeam() == opponent)) {
					if (directKingCheck) {
						if (checkForCheck(struct location(x + 1, y + 1), opponent) == false) {
							returnVector->emplace_back(piece, x + 1, y + 1);
						}
					}
					else {
						returnVector->emplace_back(piece, x + 1, y + 1);
					}
				}
				if (x + 1 <= 7 && y - 1 >= 0 && (piecePositions[x + 1][y - 1]->getType() == PieceType::Empty || piecePositions[x + 1][y - 1]->getTeam() == opponent)) {
					if (directKingCheck) {
						if (checkForCheck(struct location(x + 1, y - 1), opponent) == false) {
							returnVector->emplace_back(piece, x + 1, y - 1);
						}
					}
					else {
						returnVector->emplace_back(piece, x + 1, y - 1);
					}
				}
				if (x - 1 >= 0 && y + 1 <= 7 && (piecePositions[x - 1][y + 1]->getType() == PieceType::Empty || piecePositions[x - 1][y + 1]->getTeam() == opponent)) {
					if (directKingCheck) {
						if (checkForCheck(struct location(x - 1, y + 1), opponent) == false) {
							returnVector->emplace_back(piece, x - 1, y + 1);
						}
					}
					else {
						returnVector->emplace_back(piece, x - 1, y + 1);
					}
				}
				if (x - 1 >= 0 && y - 1 >= 0 && (piecePositions[x - 1][y - 1]->getType() == PieceType::Empty || piecePositions[x - 1][y - 1]->getTeam() == opponent)) {
					if (directKingCheck) {
						if (checkForCheck(struct location(x - 1, y - 1), opponent) == false) {
							returnVector->emplace_back(piece, x - 1, y - 1);
						}
					}
					else {
						returnVector->emplace_back(piece, x - 1, y - 1);
					}
				}
			}
			break;

			case (PieceType::Queen):
			{
				getValidDiagonalMoves(returnVector, opponent, piece);
				getValidFileRankMoves(returnVector, opponent, piece);
			}
			break;
		}
		return returnVector;
	}


	bool checkForCheck(struct location loc, Teams team) {
		std::vector<struct moveOption>* allValidMoves = getAllValidMoves(team);
		for (int i = 0; i < allValidMoves->size(); i++) {
			if (loc.x == allValidMoves->at(i).destX && loc.y == allValidMoves->at(i).destY) {
				return true;
			}
		}
		return false;
	}


	std::vector<struct moveOption>* getAllValidMoves(Teams team) {
		std::vector<struct moveOption>* allValidMoves = new std::vector<struct moveOption>;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (piecePositions[i][j]->getTeam() == team) {
					std::vector<struct moveOption>* currValidMoves = getValidMoves(piecePositions[i][j], false);
					allValidMoves->insert(allValidMoves->end(), currValidMoves->begin(), currValidMoves->end());
				}
			}
		}
		return allValidMoves;
	}


	auto getPiecePositions() {
		return piecePositions;
	}


	void getValidDiagonalMoves(std::vector<struct moveOption>* returnVector, Teams opponent, Piece* piece) {
		bool scanPosXPosY = true;
		bool scanPosXNegY = true;
		bool scanNegXPosY = true;
		bool scanNegXNegY = true;

		std::tuple<int, int> loc = piece->getLocation();
		int x = std::get<0>(loc);
		int y = std::get<1>(loc);


		for (int i = 1; i < 8; i++) {


			if (scanPosXPosY && x + i <= 7 && y + i <= 7) {
				if (piecePositions[x + i][y + i]->getType() != PieceType::Empty) {
					if (piecePositions[x + i][y + i]->getTeam() == opponent) {
						returnVector->emplace_back(piece, x + i, y + i);
					}
					scanPosXPosY = false;
				}
				else {
					returnVector->emplace_back(piece, x + i, y + i);
				}
			}
			else { scanPosXPosY = false; }


			if (scanPosXNegY && x + i <= 7 && y - i >= 0) {
				if (piecePositions[x + i][y - i]->getType() != PieceType::Empty) {
					if (piecePositions[x + i][y - i]->getTeam() == opponent) {
						returnVector->emplace_back(piece, x + i, y - i);
					}
					scanPosXNegY = false;
				}
				else {
					returnVector->emplace_back(piece, x + i, y - i);
				}
			}
			else { scanPosXNegY = false; }


			if (scanNegXPosY && x - i >= 0 && y + i <= 7) {
				if (piecePositions[x - i][y + i]->getType() != PieceType::Empty) {
					if (piecePositions[x - i][y + i]->getTeam() == opponent) {
						returnVector->emplace_back(piece, x - i, y + i);
					}
					scanNegXPosY = false;
				}
				else {
					returnVector->emplace_back(piece, x - i, y + i);
				}
			}
			else { scanNegXPosY = false; }


			if (scanNegXNegY && x - i >= 0 && y - i >= 0) {
				if (piecePositions[x - i][y - i]->getType() != PieceType::Empty) {
					if (piecePositions[x - i][y - i]->getTeam() == opponent) {
						returnVector->emplace_back(piece, x - i, y - i);
					}
					scanNegXNegY = false;

				}
				else {
					returnVector->emplace_back(piece, x - i, y - i);
				}
			}
			else { scanNegXNegY = false; }
		}
		
	}


	void getValidFileRankMoves(std::vector<struct moveOption>* returnVector, Teams opponent, Piece* piece) {
		bool scanPosX = true;
		bool scanNegX = true;
		bool scanPosY = true;
		bool scanNegY = true;

		std::tuple<int, int> loc = piece->getLocation();
		int x = std::get<0>(loc);
		int y = std::get<1>(loc);

		for (int i = 1; i < 8; i++) {


			if (scanPosX && x + i <= 7) {
				if (piecePositions[x + i][y]->getType() != PieceType::Empty) {
					if (piecePositions[x + i][y]->getTeam() == opponent) {
						returnVector->emplace_back(piece, x + i, y);
					}
					scanPosX = false;
				}
				else {
					returnVector->emplace_back(piece, x + i, y);
				}
			}
			else { scanPosX = false; }


			if (scanNegX && x - i >= 0) {
				if (piecePositions[x - i][y]->getType() != PieceType::Empty) {
					if (piecePositions[x - i][y]->getTeam() == opponent) {
						returnVector->emplace_back(piece, x - i, y);
					}
					scanNegX = false;
				}
				else {
					returnVector->emplace_back(piece, x - i, y);
				}
			}
			else { scanNegX = false; }


			if (scanPosY && y + i <= 7) {
				if (piecePositions[x][y + i]->getType() != PieceType::Empty) {
					if (piecePositions[x][y + i]->getTeam() == opponent) {
						returnVector->emplace_back(piece, x, y + i);
					}
					scanPosY = false;
				}
				else {
					returnVector->emplace_back(piece, x, y + i);
				}
			}
			else { scanPosY = false; }


			if (scanNegY && y - i >= 0) {
				if (piecePositions[x][y - i]->getType() != PieceType::Empty) {
					if (piecePositions[x][y - i]->getTeam() == opponent) {
						returnVector->emplace_back(piece, x, y - i);
					}
					scanNegY = false;

				}
				else {
					returnVector->emplace_back(piece, x, y - i);
				}
			}
			else { scanNegY = false; }
		}
	}


	std::string getLayoutString() {
		std::string string = "+ - - - - - - - -+\n";
		for (int x = 7; x >= 0; x--) {
			string.append("|");
			for (int y = 0; y < 8; y++) {
				PieceType type = piecePositions[y][x]->getType();
				if (type == PieceType::Empty) { string.append("* "); }
				else if (type == PieceType::Pawn) { string.append("P "); }
				else if (type == PieceType::Bishop) { string.append("B "); }
				else if (type == PieceType::Knight) { string.append("N "); }
				else if (type == PieceType::Rook) { string.append("R "); }
				else if (type == PieceType::King) { string.append("K "); }
				else if (type == PieceType::Queen) { string.append("Q "); }
			}
			string.append("|\n");
		}
		string.append("+ - - - - - - - -+");
		return string;
	}

	void movePiece(Piece* piece, struct location destination ) {
		delete piecePositions[destination.x][destination.y];
		piecePositions[destination.x][destination.y] = piece;
		std::tuple<int, int> previousPosition = piece->getLocation();
		piece->setLocation(destination.x, destination.y);
		piecePositions[std::get<0>(previousPosition)][std::get<1>(previousPosition)] = new Blank(previousPosition);
	}

private:
	Piece* piecePositions[8][8] = {};

	void setStandardLayout() {
		//	PieceType layout[8][8] = {
		//		PieceType::Rook, PieceType::Knight, PieceType::Bishop, PieceType::Queen, PieceType::King, PieceType::Bishop, PieceType::Knight, PieceType::Rook,
		//		PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn,
		//		PieceType::Empty, PieceType::Empty, PieceType::Empty, PieceType::Empty, PieceType::Empty, PieceType::Empty, PieceType::Empty,
		//		PieceType::Empty, PieceType::Empty, PieceType::Empty, PieceType::Empty, PieceType::Empty, PieceType::Empty, PieceType::Empty,
		//		PieceType::Empty, PieceType::Empty, PieceType::Empty, PieceType::Empty, PieceType::Empty, PieceType::Empty, PieceType::Empty,
		//		PieceType::Empty, PieceType::Empty, PieceType::Empty, PieceType::Empty, PieceType::Empty, PieceType::Empty, PieceType::Empty,
		//		PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn, PieceType::Pawn,
		//		PieceType::Rook, PieceType::Knight, PieceType::Bishop, PieceType::Queen, PieceType::King, PieceType::Bishop, PieceType::Knight, PieceType::Rook
		//	};

		Teams player1_team = Teams::White;
		Teams player2_team = Teams::Black;

		piecePositions[0][0] = new Rook(player1_team, { 0,0 });
		piecePositions[1][0] = new Knight(player1_team, { 1,0 });
		piecePositions[2][0] = new Bishop(player1_team, { 2,0 });
		piecePositions[3][0] = new Queen(player1_team, { 3,0 });
		piecePositions[4][0] = new King(player1_team, { 4,0 });
		piecePositions[5][0] = new Bishop(player1_team, { 5,0 });
		piecePositions[6][0] = new Knight(player1_team, { 6,0 });
		piecePositions[7][0] = new Rook(player1_team, { 7,0 });

		for (int i = 0; i < 8; i++) {
			piecePositions[i][1] = new Pawn(player1_team, { i,1 });
		}

		for (int i = 2; i < 6; i++) {
			for (int j = 0; j < 8; j++) {
				piecePositions[j][i] = new Blank({ j,i });
			}
		}

		for (int i = 0; i < 8; i++) {
			piecePositions[i][6] = new Pawn(player2_team, { i,6 });
		}

		piecePositions[0][7] = new Rook(player2_team, { 0,7 });
		piecePositions[1][7] = new Knight(player2_team, { 1,7 });
		piecePositions[2][7] = new Bishop(player2_team, { 2,7 });
		piecePositions[3][7] = new Queen(player2_team, { 3,7 });
		piecePositions[4][7] = new King(player2_team, { 4,7 });
		piecePositions[5][7] = new Bishop(player2_team, { 5,7 });
		piecePositions[6][7] = new Knight(player2_team, { 6,7 });
		piecePositions[7][7] = new Rook(player2_team, { 7,7 });

		//// overrides
		//piecePositions[0][1] = new Blank({ 0,1 });
		//piecePositions[0][2] = new Pawn(player1_team, { 0,2 });
		//piecePositions[4][1] = new Blank({ 4,1 });
		//piecePositions[4][2] = new Pawn(player1_team, { 4,2 });
		//piecePositions[5][1] = new Rook(player2_team, { 5,1 });
		////
	}
};