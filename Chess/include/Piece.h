#pragma once

#include <tuple>


enum class Teams { White, Black, Empty };
enum class PieceType { Pawn, Rook, Knight, Bishop, King, Queen, Empty };
struct location { // look into this
	int x;
	int y;
};
struct enPassant { 
	bool valid = false; 
	int x = 0; 
	int y = 0; 
};

class Piece {
public:
	Piece(Teams team, std::tuple<int,int> location);
	~Piece();
	std::tuple<int, int> getLocation(); // TODO - change to use location struct
	void setLocation(int x, int y);
	virtual PieceType getType();
	Teams getTeam();

private:
	Teams team;
	int x;
	int y;
};

class Pawn : public Piece {
public:
	Pawn(Teams t, std::tuple<int, int> location);
	PieceType getType();
	bool getHasMoved();
	struct enPassant getEnPassant();
private:
	bool hasMoved = false;
	struct enPassant enPassant;
};

class Rook : public Piece {
public:
	Rook(Teams t, std::tuple<int, int> location);
	PieceType getType();
private:
	bool hasMoved = false;
};

class Knight : public Piece {
public:
	Knight(Teams t, std::tuple<int, int> location);
	PieceType getType();
};

class Bishop : public Piece {
public:
	Bishop(Teams t, std::tuple<int, int> location);
	PieceType getType();
};

class King : public Piece {
public:
	King(Teams t, std::tuple<int, int> location);
	PieceType getType();
private:
	bool hasMoved = false;
};

class Queen : public Piece {
public:
	Queen(Teams t, std::tuple<int, int> location);
	PieceType getType();
};

class Blank : public Piece {
public:
	Blank(std::tuple<int, int> location);
	PieceType getType();
};