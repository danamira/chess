
class Board
{
public:
    Piece map[8][8];

    int blackKingX;
    int blackKingY;
    int whiteKingX;
    int whiteKingY;
    bool finished = false;
    int selectedX = -1;
    int selectedY = -1;
    string selectedAvailableMoves = "";

    bool whiteChecked = false;
    bool blackCheked = false;
    bool calculated = 0;

    string DangerousMoves = "";

    bool isWhiteTurn = true;

    Board()
    {
    }
    Board(string x)
    {
    }

    bool PieceSelected()
    {
        return (this->selectedX != -1 && this->selectedY != -1);
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

        // cout<<"Available moves"<<p.availableMoves(this->map);

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

    void setup()
    {

        int row;
        string map = defaultSetup();
        int col;
        char pieceType;
        char color;
        string h;

        for (int i = 0; i < 8; i++)
        {
            row = i;
            col = 0;

            for (int j = 7; j >= 0; j--)
            {

                h = map.substr((24 * i) + (3 * j), 2);
                pieceType = h[0];
                color = h[1];
                if (pieceType != '-')
                {
                    this->addPiece(Piece(pieceType, color == 'W'), 7 - col, 7 - row);
                }
                col += 1;
            }
            h = "";
        }
    }

    string calculateBlackDefense()
    {

        string k;
        Piece p = this->getPieceByPosition(this->selectedX, this->selectedY);
        string pr;

        string targets = this->properMoves(p.x, p.y);
        string destX;
        string destY;
        Board check;
        string src;
        for (int t = 0; t < targets.length(); t++)
        {
            if (t % 3 == 0)
            {
                destX = targets[t];
            }
            else if (t % 3 == 1)
            {
                destY = targets[t];
                src = to_string(this->selectedX * 10 + this->selectedY);
                if (this->selectedX == 0)
                {
                    src = '0' + src;
                }
                check = this->movePiece(src, destX + destY);
                bool IsMatedInTwo;
                if (check.blackMatedInOne() || check.blackMatedInTwo())
                {
                    pr += (src) + p.alias() + (destX + destY) + '-';
                }
            }
            else
            {
                // continue;
            }
        }

        return pr;
    }

    string calculateWhiteDefense()
    {
        string k;
        Piece p = this->getPieceByPosition(this->selectedX, this->selectedY);
        string pr;

        string targets = this->properMoves(p.x, p.y);
        string destX;
        string destY;
        Board check;
        string src;
        for (int t = 0; t < targets.length(); t++)
        {
            if (t % 3 == 0)
            {
                destX = targets[t];
            }
            else if (t % 3 == 1)
            {
                destY = targets[t];
                src = to_string(this->selectedX * 10 + this->selectedY);
                if (this->selectedX == 0)
                {
                    src = '0' + src;
                }
                check = this->movePiece(src, destX + destY);
                bool IsMatedInTwo;
                if (check.whiteMatedInOne() || check.whiteMatedInTwo())
                {
                    pr += (src) + p.alias() + (destX + destY) + '-';
                }
            }
            else
            {
                continue;
            }
        }

        return pr;
    }

    void render(sf::RenderWindow &window)
    {
        sf::RectangleShape board(sf::Vector2f(600.f, 600.f));
        board.setFillColor(sf::Color(173, 163, 151));
        board.setPosition(20, 20);
        window.draw(board);

        sf::Sprite turn;
        sf::Sprite calcBtn;
        sf::Texture turnTxt;
        sf::Texture calcTxt;

        if (this->PieceSelected())
        {
            if (this->calculated)
            {
                calcTxt.loadFromFile("../res/Buttons/Analyze-Done.png");
            }
            else
            {
                calcTxt.loadFromFile("../res/Buttons/Analyze.png");
            }
        }
        else
        {
            calcTxt.loadFromFile("../res/Buttons/Analyze-Disabled.png");
        }
        turn.setPosition(640, 40);
        calcBtn.setPosition(640, 80);
        if (this->whiteKingMated())
        {
            turnTxt.loadFromFile("../res/Texts/BWINS.png");
            this->finished = true;
        }
        else if (this->blackKingMated())
        {
            this->finished = true;
            turnTxt.loadFromFile("../res/Texts/WWINS.png");
        }
        else
        {
            if (this->isWhiteTurn)
            {
                turnTxt.loadFromFile("../res/Texts/WTM.png");
            }
            else
            {
                turnTxt.loadFromFile("../res/Texts/BTM.png");
            }
        }
        turn.setTexture(turnTxt);
        calcBtn.setTexture(calcTxt);
        window.draw(turn);
        if (!this->finished)
        {
            window.draw(calcBtn);
        }
        sf::Sprite menu;
        sf::Texture menuTxt;
        menuTxt.loadFromFile("../res/Buttons/Menu.png");
        menu.setTexture(menuTxt);
        menu.setPosition(640, 200);
        if (!this->finished)
        {
            window.draw(menu);
        }
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                int cx = 20 + 75 * (i);
                int cy = 20 + 75 * (7 - j);
                string srcCord = getCoordinates(this->selectedX, this->selectedY);
                string desCord = getCoordinates(i, j);

                sf::RectangleShape cell(sf::Vector2f(75.f, 75.f));
                if ((i + j) % 2 == 1)
                {
                    cell.setFillColor(sf::Color(147, 139, 127));
                }
                else
                {
                    cell.setFillColor(sf::Color(173, 163, 151));
                }

                cell.setPosition(cx, cy);
                if ((this->whiteChecked && i == this->whiteKingX && j == this->whiteKingY) || this->blackCheked && i == this->blackKingX && j == this->blackKingY)
                {
                    cell.setFillColor(sf::Color(138, 97, 89));
                }

                if (this->selectedAvailableMoves.find(getCoordinates(i, j)) != string::npos)
                {
                    if ((i + j) % 2 != 0)
                    {
                        cell.setFillColor(sf::Color(147, 147, 117));
                    }
                    else
                    {
                        cell.setFillColor(sf::Color(114, 114, 91));
                    }
                }

                if (i == this->selectedX && j == this->selectedY)
                {
                    cell.setFillColor(sf::Color(208, 187, 99));
                }

                window.draw(cell);
                if (this->DangerousMoves.find(srcCord + this->getPieceByPosition(this->selectedX, this->selectedY).alias() + desCord) != string::npos)
                {
                    sf::Sprite criticalIcon;
                    sf::Texture criticalTxt;
                    criticalTxt.loadFromFile("../res/Icons/Dangerous.png");
                    criticalIcon.setTexture(criticalTxt);
                    criticalIcon.setPosition(cx + 3, cy + 3);
                    window.draw(criticalIcon);
                }
                sf::Sprite piece;
                Piece position = this->getPieceByPosition(i, j);
                if (position.type != '!')
                {
                    piece.setPosition(20 + 75 * i, 20 + 75 * (7 - j));
                    sf::Texture txt;
                    txt.loadFromFile("../res/Pieces/" + position.alias() + ".png");
                    piece.setTexture(txt);
                    window.draw(piece);
                }
            }
        }
    }

    void selectPiece(int mouseX, int mouseY)
    {
        if (this->finished)
        {
            return;
        }
        int i = mouseX / 75;
        int j = 7 - (mouseY / 75);

        cout << i << j << std::endl;

        Piece chosen = this->getPieceByPosition(i, j);
        // something already selected
        if (this->selectedX != -1)
        {

            if (this->selectedAvailableMoves.find(getCoordinates(i, j)) != string::npos)
            {
                // this->map[i][j] = this->getPieceByPosition(this->selectedX, this->selectedY);
                // this->map[this->selectedX][this->selectedY] = Piece('!');
                Board newBoard = this->movePiece(getCoordinates(this->selectedX, this->selectedY), getCoordinates(i, j));
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        this->map[i][j] = newBoard.map[i][j];
                        this->whiteKingX = newBoard.whiteKingX;
                        this->whiteKingY = newBoard.whiteKingY;
                        this->blackKingX = newBoard.blackKingX;
                        this->blackKingY = newBoard.blackKingY;
                    }
                }

                this->isWhiteTurn = !this->isWhiteTurn;
                this->selectedX = -1;
                this->selectedY = -1;
                this->selectedAvailableMoves = "";
                this->calculated = false;
                this->DangerousMoves = "";
                this->whiteChecked = this->whiteKingChecked();
                this->blackCheked = this->blackKingChecked();
                cout << this->textFacade();
            }
            else
            {
                this->selectedX = -1;
                this->selectedY = -1;
                this->selectedAvailableMoves = "";
                this->calculated = false;
            }
        }
        else
        {

            if (chosen.type != '!')
            {
                if (chosen.isWhite == this->isWhiteTurn)
                {

                    this->selectedX = i;
                    this->selectedY = j;
                    this->selectedAvailableMoves = this->properMoves(i, j);
                }
                else
                {
                    this->selectedX = -1;
                    this->selectedY = -1;
                    this->selectedAvailableMoves = "";
                    this->calculated = false;
                }
            }
            else
            {
                this->selectedX = -1;
                this->selectedY = -1;
                this->selectedAvailableMoves = "";
                this->calculated = false;
            }
        }
    }
};
