
class Board
{
public:
    Piece map[8][8];

    int blackKingX;
    int blackKingY;
    int whiteKingX;
    int whiteKingY;

    Board()
    {
    }
    Board(string x)
    {
    }

    Piece getPieceByPosition(int x, int y)
    {
        return this->map[x][y];
    }

    string textFacade()
    {
        string r = "\n\n";
        Piece c;
        for (int i = 7; i >= 0; i--)
        {
            r += to_string(i + 1) + "   ";
            for (int j = 0; j < 8; j++)
            {

                c = this->getPieceByPosition(j, i);
                r += c.alias();
                if (j != 7)
                {
                    r += ' ';
                }
            }
            if (i != 0)
            {
                r += '\n';
            }
        }
        r += "\n \n    A  B  C  D  E  F  G  H\n\n";
        return r;
    }

    Board movePiece(string source, string dest)
    {

        int sourceX = (int)source[0] - 48;
        int sourceY = (int)source[1] - 48;
        int destX = (int)dest[0] - 48;
        int destY = (int)dest[1] - 48;

        Board board;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                board.map[i][j] = this->map[i][j];
            }
        }
        Piece empty;
        Piece piece = this->getPieceByPosition(sourceX, sourceY);
        piece.x = destX;
        piece.y = destY;

        board.blackKingX = this->blackKingX;
        board.blackKingY = this->blackKingY;
        board.whiteKingX = this->whiteKingX;
        board.whiteKingY = this->whiteKingY;

        if (piece.type == 'K')
        {
            if (piece.isWhite)
            {
                board.whiteKingX = destX;
                board.whiteKingY = destY;
            }
            else
            {
                board.blackKingX = destX;
                board.blackKingY = destY;
            }
        }
        board.map[destX][destY] = piece;
        board.map[sourceX][sourceY] = empty;

        return board;
    }

    void addPiece(Piece piece, int x, int y)
    {

        piece.x = x;
        piece.y = y;
        this->map[x][y] = piece;

        if (piece.type == 'K')
        {
            if (piece.isWhite)
            {
                this->whiteKingX = x;
                this->whiteKingY = y;
            }
            else
            {
                this->blackKingX = x;
                this->blackKingY = y;
            }
        }
    }

    bool whiteKingChecked()
    {

        if (this->getPieceByPosition(this->whiteKingX, this->whiteKingY).isThreatened(this->map))
        {
            return true;
        }

        return false;
    }

    string properMoves(int x, int y)
    {
        Piece p = this->getPieceByPosition(x, y);
        string proper;
        string targets = p.availableMoves(this->map);
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
                if (p.isWhite)
                {
                    string mnt = to_string(10 * x + y);
                    if (x == 0)
                    {
                        mnt = '0' + mnt;
                    }
                    if (!this->movePiece(mnt, destX + destY).whiteKingChecked())
                    {
                        proper += destX + destY + '-';
                    }
                }
                else
                {

                    string mnt = to_string(10 * x + y);
                    if (x == 0)
                    {
                        mnt = '0' + mnt;
                    }
                    if (!this->movePiece(mnt, destX + destY).blackKingChecked())
                    {

                        proper += destX + destY + "-";
                    }
                }
            }
            else
            {
                continue;
            }
        }
        proper = proper.substr(0, proper.length() - 1);
        return proper;
    }

    bool whiteKingMated()
    {

        if (!this->whiteKingChecked())
        {
            return false;
        }
        Piece king = this->getPieceByPosition(whiteKingX, whiteKingY);

        Piece p;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                p = this->getPieceByPosition(i, j);
                if (p.type == '!' || !p.isWhite)
                {
                    continue;
                }
                string targets = this->properMoves(p.x, p.y);

                string destX;
                string destY;
                Board check;
                for (int t = 0; t < targets.length(); t++)
                {
                    if (t % 3 == 0)
                    {
                        destX = targets[t];
                    }
                    else if (t % 3 == 1)
                    {
                        destY = targets[t];
                        string src = to_string(i * 10 + j);
                        if (i == 0)
                        {
                            src = '0' + src;
                        }
                        check = this->movePiece(src, destX + destY);
                        if (!check.whiteKingChecked())
                        {
                            return false;
                        }
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
        return true;
    }

    bool blackKingChecked()
    {

        if (this->getPieceByPosition(this->blackKingX, this->blackKingY).isThreatened(this->map))
        {
            return true;
        }

        return false;
    }

    bool blackKingMated()
    {

        if (!this->blackKingChecked())
        {
            return false;
        }
        Piece king = this->getPieceByPosition(blackKingX, blackKingY);

        Piece p;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                p = this->getPieceByPosition(i, j);
                if (p.type == '!' || p.isWhite)
                {
                    continue;
                }
                string targets = this->properMoves(p.x, p.y);

                string destX;
                string destY;
                Board check;
                for (int t = 0; t < targets.length(); t++)
                {
                    if (t % 3 == 0)
                    {
                        destX = targets[t];
                    }
                    else if (t % 3 == 1)
                    {
                        destY = targets[t];
                        string src = to_string(i * 10 + j);
                        if (i == 0)
                        {
                            src = '0' + src;
                        }
                        check = this->movePiece(src, destX + destY);
                        if (!check.blackKingChecked())
                        {
                            // cout<<std::endl;
                            // cout<<"HERE IS HOW BLACK KING CAN ESCAPE "<<destX+destY;
                            // cout<<std::endl;
                            return false;
                        }
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
        return true;
    }

    // .:: Declares whether white can mate the black in the current board ::.

    bool blackMatedInOne(bool analyze = false)
    {
        Piece king = this->getPieceByPosition(blackKingX, blackKingY);

        Piece p;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                p = this->getPieceByPosition(i, j);
                if (p.type == '!' || !p.isWhite)
                {
                    continue;
                }
                string targets = this->properMoves(p.x, p.y);

                string destX;
                string destY;
                Board check;
                for (int t = 0; t < targets.length(); t++)
                {
                    if (t % 3 == 0)
                    {
                        destX = targets[t];
                    }
                    else if (t % 3 == 1)
                    {
                        destY = targets[t];
                        string src = to_string(i * 10 + j);
                        if (i == 0)
                        {
                            src = '0' + src;
                        }
                        check = this->movePiece(src, destX + destY);
                        if (check.blackKingMated())
                        {
                            return true;
                        }
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
        return false;
    }

    bool blackMatedInTwo(bool analyze = false)
    {

        Piece king = this->getPieceByPosition(blackKingX, blackKingY);

        Piece p;

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                p = this->getPieceByPosition(i, j);
                if (p.type == '!' || !p.isWhite)
                {
                    continue;
                }
                string targets = this->properMoves(p.x, p.y);

                string destX;
                string destY;
                Board check;

                for (int t = 0; t < targets.length(); t++)
                {
                    if (t % 3 == 0)
                    {
                        destX = targets[t];
                    }
                    else if (t % 3 == 1)
                    {
                        destY = targets[t];
                        string src = to_string(i * 10 + j);
                        if (i == 0)
                        {
                            src = '0' + src;
                        }
                        check = this->movePiece(src, destX + destY);
                        bool allMate = true;

                        ///// .:: Move every black piece to every position possible to see whether there's a way to escape. ::.
                        for (int s = 0; s < 8; s++)
                        {
                            for (int o = 0; o < 8; o++)
                            {
                                Piece u = check.getPieceByPosition(s, o);
                                if (u.type == '!' || u.isWhite)
                                {
                                    continue;
                                }
                                string utargets = check.properMoves(u.x, u.y);
                                string dux;
                                string duy;
                                Board finalCheck;
                                for (int r = 0; r < utargets.length(); r++)
                                {
                                    if (r % 3 == 0)
                                    {
                                        dux = utargets[r];
                                    }
                                    else if (r % 3 == 1)
                                    {
                                        duy = utargets[r];
                                        string src = to_string(s * 10 + o);
                                        if (s == 0)
                                        {
                                            src = '0' + src;
                                        }
                                        finalCheck = check.movePiece(src, dux + duy);
                                        if (allMate && !finalCheck.blackMatedInOne())
                                        {
                                            allMate = false;
                                        }
                                    }
                                }
                            }
                        }

                        if (allMate)
                        {
                            return true;
                        }
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
        return false;
    }

    bool whiteMatedInOne()
    {
        Piece king = this->getPieceByPosition(blackKingX, blackKingY);

        Piece p;
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                p = this->getPieceByPosition(i, j);
                if (p.type == '!' || p.isWhite)
                {
                    continue;
                }
                string targets = this->properMoves(p.x, p.y);

                string destX;
                string destY;
                Board check;

                for (int t = 0; t < targets.length(); t++)
                {
                    if (t % 3 == 0)
                    {
                        destX = targets[t];
                    }
                    else if (t % 3 == 1)
                    {
                        destY = targets[t];
                        string ksrc = to_string(10 * i + j);
                        if (i == 0)
                        {
                            ksrc = '0' + ksrc;
                        }

                        check = this->movePiece(ksrc, destX + destY);
                        if (check.whiteKingMated())
                        {
                            return true;
                        }
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
        return false;
    }

    bool whiteMatedInTwo(bool analyze = false)
    {

        Piece p;

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                p = this->getPieceByPosition(i, j);
                if (p.type == '!' || p.isWhite)
                {
                    continue;
                }
                string targets = this->properMoves(p.x, p.y);

                string destX;
                string destY;
                Board check;

                for (int t = 0; t < targets.length(); t++)
                {
                    if (t % 3 == 0)
                    {
                        destX = targets[t];
                    }
                    else if (t % 3 == 1)
                    {
                        destY = targets[t];
                        string src = to_string(i * 10 + j);
                        if (i == 0)
                        {
                            src = '0' + src;
                        }
                        check = this->movePiece(src, destX + destY);
                        bool allMate = true;

                        ///// .:: Move every black piece to every position possible to see whether there's a way to escape. ::.
                        for (int s = 0; s < 8; s++)
                        {
                            for (int o = 0; o < 8; o++)
                            {
                                Piece u = check.getPieceByPosition(s, o);
                                if (u.type == '!' || !u.isWhite)
                                {
                                    continue;
                                }
                                string utargets = check.properMoves(u.x, u.y);
                                string dux;
                                string duy;
                                Board finalCheck;

                                for (int r = 0; r < utargets.length(); r++)
                                {
                                    if (r % 3 == 0)
                                    {
                                        dux = utargets[r];
                                    }
                                    else if (r % 3 == 1)
                                    {
                                        duy = utargets[r];
                                        string src = to_string(s * 10 + o);
                                        if (s == 0)
                                        {
                                            src = '0' + src;
                                        }
                                        finalCheck = check.movePiece(src, dux + duy);
                                        if (allMate && !finalCheck.whiteMatedInOne())
                                        {
                                            allMate = false;
                                        }
                                    }
                                }
                            }
                        }

                        if (allMate)
                        {
                            return true;
                        }
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
        return false;
    }

    vector<string> getAttacks(char side = 'W')
    {

        bool whiteExpected = (side == 'W');

        string result;
        vector<string> finalItems;

        Piece p;

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                p = this->getPieceByPosition(i, j);
                if (p.type == '!' || !p.isWhite == whiteExpected)
                {
                    continue;
                }
                string targets = this->properMoves(p.x, p.y);
                


                // cout<<std::endl;

                // cout<<"TALKING ABOUT: "<<p.alias();
                // cout<<std::endl;
                // cout<<targets;
                // cout<<std::endl;
                
                
                string destX;
                string destY;
                Board check;

                for (int t = 0; t < targets.length(); t++)
                {
                    if (t % 3 == 0)
                    {
                        destX = targets[t];
                    }
                    else if (t % 3 == 1)
                    {
                        destY = targets[t];
                        
                        
                        string src = to_string(i * 10 + j);
                        
                        
                        if (i == 0)
                        {
                            src = '0' + src;
                        }

                        // cout<<"TO :"<<destX+destY;
                        // cout<<std::endl;
                        check = this->movePiece(src, destX + destY);

                        bool allMate = true;

                        ///// .:: Move every black piece to every position possible to see whether there's a way to escape. ::.
                        for (int s = 0; s < 8; s++)
                        {
                            for (int o = 0; o < 8; o++)
                            {
                                Piece u = check.getPieceByPosition(s, o);
                                if (u.type == '!' || u.isWhite == whiteExpected)
                                {
                                    continue;
                                }
                                string utargets = check.properMoves(u.x, u.y);
                                string dux;
                                string duy;
                                Board finalCheck;

                                for (int r = 0; r < utargets.length(); r++)
                                {
                                    if (r % 3 == 0)
                                    {
                                        dux = utargets[r];
                                    }
                                    else if (r % 3 == 1)
                                    {
                                        duy = utargets[r];
                                        string src = to_string(s * 10 + o);
                                        if (s == 0)
                                        {
                                            src = '0' + src;
                                        }
                                        finalCheck = check.movePiece(src, dux + duy);

                                        if (whiteExpected)
                                        {
                                            if (allMate && !finalCheck.blackMatedInOne())
                                            {

                                                // cout<<"ESCAPE FOR BLACK: "<<u.alias()<<" TO "<<dux+duy<<" AND "<<finalCheck.blackKingMated();
                                                // cout<<std::endl;
                                                allMate = false;
                                            }
                                        }
                                        else
                                        {
                                            if (allMate && !finalCheck.whiteMatedInOne())
                                            {
                                                allMate = false;
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        if (allMate)
                        {
                            finalItems.push_back(standardPosition(src) + p.alias() + standardPosition(destX + destY));
                        }
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
        return finalItems;
    }
};
