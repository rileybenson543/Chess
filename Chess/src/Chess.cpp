// Chess.cpp : Defines the entry point for the application.
//
#include <time.h>
#include "Chess.h"
#include "Piece.h"
#include "Game.cpp"

//#define RAND_MAX 1000

int main()
{
    Game g = Game();
    auto pos = g.getPiecePositions();
    std::string s = g.getLayoutString();
    std::vector<struct moveOption>* m = g.getAllValidMoves(Teams::White);
    std::cout << s << std::endl;

    int t = 1;
    Teams team;
    while (true) {
        if (t == 1) {
            team = Teams::White;
        }
        else if (t == -1) {
            team = Teams::Black;
        }

        std::vector<moveOption>* options = g.getAllValidMoves(team);

        int r = (float(rand()) / float(RAND_MAX)) * options->size();
        struct moveOption selected = options->at(r);


        g.movePiece(selected.piece, { selected.destX, selected.destY });
        std::cout << g.getLayoutString() << std::endl;
        
        t = t * -1;

        std::cin.get();
    }

    std::cin.get();
}
