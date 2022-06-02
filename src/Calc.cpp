#include <iostream>
#include <typeinfo>
#include <vector>
#include <algorithm>

using namespace std;

#include "Helpers.h"
#include "Piece.h"
#include "Board.h"

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
    if (input == "BD")
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                p = dana.getPieceByPosition(i, j);
                if (p.type == '!' || p.isWhite)
                {
                    continue;
                }
                string targets = dana.properMoves(p.x, p.y);
                string destX;
                string destY;
                Board check;
                string src;
                string k;
                string pr;
                for (int t = 0; t < targets.length(); t++)
                {
                    if (t % 3 == 0)
                    {
                        destX = targets[t];
                    }
                    else if (t % 3 == 1)
                    {
                        destY = targets[t];
                        src = to_string(i * 10 + j);
                        if (i == 0)
                        {
                            src = '0' + src;
                        }
                        check = dana.movePiece(src, destX + destY);
                        bool IsMatedInTwo;
                        if (check.blackMatedInOne() || check.blackMatedInTwo())
                        {
                            k += destX + destY + '-';
                            pr += standardPosition(src) + p.alias() + standardPosition(destX + destY);
                        }
                    }
                    else
                    {
                        continue;
                    }
                }

                if (k == targets + '-')
                {
                    // finalResult += standardPosition(src) + p.alias() + '\n';
                    finalItems.push_back(standardPosition(src) + p.alias());
                }
                else
                {
                    if (pr.length() > 0)
                    {
                        // finalResult += pr + '\n';
                        finalItems.push_back(pr);
                    }
                }
            }
        }
    }
    if (input == "WD")
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                p = dana.getPieceByPosition(i, j);
                if (p.type == '!' || !p.isWhite)
                {
                    continue;
                }
                string targets = dana.properMoves(p.x, p.y);
                string destX;
                string destY;
                Board check;
                string src;
                string k;
                string pr;
                for (int t = 0; t < targets.length(); t++)
                {
                    if (t % 3 == 0)
                    {
                        destX = targets[t];
                    }
                    else if (t % 3 == 1)
                    {
                        destY = targets[t];
                        src = to_string(i * 10 + j);
                        if (i == 0)
                        {
                            src = '0' + src;
                        }
                        check = dana.movePiece(src, destX + destY);
                        bool IsMatedInTwo;
                        if (check.whiteMatedInOne() || check.whiteMatedInTwo())
                        {
                            k += destX + destY + '-';
                            pr += standardPosition(src) + p.alias() + standardPosition(destX + destY);
                        }
                    }
                    else
                    {
                        continue;
                    }
                }

                if (k == targets + '-')
                {

                    // finalResult+= standardPosition(src) + p.alias()+'\n';
                    finalItems.push_back(standardPosition(src) + p.alias());
                }
                else
                {
                    // finalResult+=pr+'\n';
                    finalItems.push_back(pr);
                }
            }
        }
    }

    if (input[1] == 'M')
    {
        finalItems = dana.getAttacks(input[0]);
        
    }

    
    
    std::sort(finalItems.begin(),finalItems.end());
    
    if(finalItems.empty()) {
        cout<<"No Answer!";
        return 0;
    }
    for(int i=0;i<finalItems.size();i++){
        cout<<finalItems.at(i);
        if(i!=finalItems.size()-1) {
            cout<<std::endl;
        }
    }
    return 0;
}