// Chess.cpp : Defines the entry point for the application.
//
#include <time.h>
#include "Chess.h"
#include "Piece.h"
#include "Game.cpp"

int main()
{
    Game g = Game();
    auto pos = g.getPiecePositions();
    std::string s = g.getLayoutString();
    std::vector<struct location>* m = g.getAllValidMoves(Teams::White);
    std::cout << s << std::endl;

    std::cin.get();
}
