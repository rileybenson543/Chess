#include "Piece.h"

Piece::Piece(Teams t, std::tuple<int, int> l)
	: team(t), x(std::get<0>(l)), y(std::get<1>(l)) {}
Piece::~Piece() {}
std::tuple<int, int> Piece::getLocation() {
	return {x,y};
}
void Piece::setLocation(int _x, int _y) {
	x = _x;
	y = _y;
}
PieceType Piece::getType() {
	return PieceType::Empty;
}
Teams Piece::getTeam() { return team; }

Pawn::Pawn(Teams t, std::tuple<int,int> l)
	: Piece(t, l) {}
PieceType Pawn::getType() {
	return PieceType::Pawn;
}
bool Pawn::getHasMoved() { return hasMoved; }
struct enPassant Pawn::getEnPassant() { return enPassant; }

Rook::Rook(Teams t, std::tuple<int,int> l)
	: Piece(t, l) {}
PieceType Rook::getType() {
	return PieceType::Rook;
}

Bishop::Bishop(Teams t, std::tuple<int,int> l)
	: Piece(t, l) {}
PieceType Bishop::getType() {
	return PieceType::Bishop;
}

Knight::Knight(Teams t, std::tuple<int,int> l)
	: Piece(t, l) {}
PieceType Knight::getType() {
	return PieceType::Knight;
}

King::King(Teams t, std::tuple<int,int> l)
	: Piece(t, l) {}
PieceType King::getType() {
	return PieceType::King;
}

Queen::Queen(Teams t, std::tuple<int,int> l)
	: Piece(t, l) {}
PieceType Queen::getType() {
	return PieceType::Queen;
}

Blank::Blank(std::tuple<int, int> l)
	: Piece(Teams::Empty, l) {} 
PieceType Blank::getType() {
	return PieceType::Empty;
}