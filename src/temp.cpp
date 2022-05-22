#include <iostream>
#include <typeinfo>
#include <vector>
#include <algorithm>

using namespace std;

string standardPosition(string pos)
{

    string r;
    char alpha[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    int x = (int)pos[0] - 48;
    int y = (int)pos[1] - 48;
    r += alpha[x];
    r += to_string(y + 1);
    return r;
}

#include "board/Piece.h"
#include "board/Board.h"

int main()
{

    Board dana;
    string input;
    cin>>input;


    int row;
    int col;

    char pieceType;
    char color;
    string h;

    string line;
    for (int i = 7; i >= 0; i--)
    {
        row = i;
        col = 0;
 
        for (int j = 0; j < 8; j++)
        {

            h = "";
            cin >> h;
            pieceType = h[0];
            color = h[1];
            if (pieceType != '-')
            {
                dana.addPiece(Piece(pieceType, color == 'W'), col, row);
            }
            col += 1;
        }
        h = "";
    }


    string finalResult;
    vector<string> finalItems;
    
    Piece p;
    cout<<dana.blackKingChecked();
    return 0;
}