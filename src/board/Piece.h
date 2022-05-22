
class Piece
{

public:
    Piece(char type='!',bool isWhite=true)
    {
        this->type = type;
        this->isWhite=isWhite;
    }
    

    
    bool isWhite;
    char type;

    int x;
    int y;

    string alias() {
        string r;
        if(this->type=='!') {
            return "--";
        }
        r+=this->type;
        if(this->isWhite) {
            r+='W';
        }
        else {r+='B';}
        return r ;
    }
    
    string id() {
        return standardPosition(to_string(10*this->x+this->y))+' '+this->alias();
    }
    

    bool isThreatened(Piece map[8][8])
    {
        Piece piece;

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {

                piece = map[i][j];

                if (piece.type == '!' || (piece.x == this->x && piece.y == this->y))
                {
                    continue;
                }

                string targets = piece.availableMoves(map, false);
                // cout<<std::endl;
                // cout<<"I AM "<<piece.alias()<<" AND I CAN GO TO:"<<targets;
                // cout<<std::endl;
                if (targets.find(to_string(this->x) + to_string(this->y)) != string::npos)
                
                {
                    return true;
                }
            }
        }

        return false;
    }
    string availableMoves(Piece map[8][8], bool removeDangerousOnes = true)
    {
        switch (this->type)
        {
        case 'Q':
            return this->queenAvailableMoves(map);

        case 'P':
            return this->pawnAvailableMooves(map);

        case 'B':
            return this->bishopAvailableMoves(map);

        case 'R':
            return this->rookAvailableMoves(map);

        case 'N':
            return this->knightAvailableMoves(map);

        case 'K':
            return this->kingAvailableMoves(map, removeDangerousOnes);
        }
        return "";
    }

private:
    string pawnAvailableMooves(Piece map[8][8])
    {
        string r;

        int posX;
        int posY;

        if (this->isWhite)
        {
            posX = this->x;
            posY = this->y + 1;
            if (map[posX][posY].type == '!' && posY >= 0 && posY < 8)
            {
                r += to_string(posX) + to_string(posY) + '-';
            }
            posY = 3;
            if (this->y == 1 && map[posX][posY].type == '!' && map[posX][2].type=='!')
            {
                r += to_string(posX) + to_string(posY) + '-';
            }
            posX = this->x + 1;
            posY = this->y + 1;
            Piece dist = map[posX][posY];
            if (posX < 8 && posY < 8 && dist.type != '!' && dist.isWhite != this->isWhite)
            {
                r += to_string(posX) + to_string(posY) + '-';
            }
            posX = this->x - 1;
            dist = map[posX][posY];
            if (posX >= 0 && posY < 8 && dist.type != '!' && dist.isWhite != this->isWhite)
            {
                r += to_string(posX) + to_string(posY) + '-';
            }
        }
        else
        {
            posX = this->x;
            posY = this->y - 1;
            if (map[posX][posY].type == '!' && posY >= 0 && posY < 8)
            {
                r += to_string(posX) + to_string(posY) + '-';
            }
            posY = 4;
            if (this->y == 6 && map[posX][posY].type == '!' && map[posX][5].type=='!')
            {
                r += to_string(posX) + to_string(posY) + '-';
            }
            posX = this->x + 1;
            posY = this->y - 1;
            Piece dist = map[posX][posY];
            if (posX < 8 && posY < 8 && posY >= 0 && dist.type != '!' && dist.isWhite != this->isWhite)
            {
                r += to_string(posX) + to_string(posY) + '-';
            }
            posX = this->x - 1;
            dist = map[posX][posY];
            if (posX >= 0 && posY < 8 && posY >= 0 && dist.type != '!' && dist.isWhite != this->isWhite)
            {
                r += to_string(posX) + to_string(posY) + '-';
            }
        }

        r = r.substr(0, r.length() - 1);
        return r;
    }

    string knightAvailableMoves(Piece map[8][8])
    {
        string r;
        int options[8] = {1121, 1221, 2121, 2221, 1112, 1212, 2112, 2212};
        for (int i = 0; i < 8; i++)
        {
            int o = options[i];
            int xSign = o / 1000;
            int ySign = o / 100 - (10 * xSign);
            int xMove = (o / 10 - ((o / 100) * 10));
            int yMove = o % 10;
            if (xSign == 1)
            {
                xMove = -xMove;
            }
            if (ySign == 1)
            {
                yMove = -yMove;
            }
            int posX = this->x + xMove;
            int posY = this->y + yMove;
            if (posX >= 0 && posX < 8 && posY >= 0 && posY < 8)
            {
                Piece dest = map[posX][posY];
                if (dest.type == '!' || dest.isWhite != this->isWhite)
                {
                    r += std::to_string(posX);
                    r += std::to_string(posY);
                    r += '-';
                }
            }
        }
        r = r.substr(0, r.length() - 1);
        return r;
    }

    string queenAvailableMoves(Piece map[8][8])
    {
        string r;
        int h = this->y - this->x;
        int u = this->y + this->x;
        int posX;
        int posY;
        for (int i = this->x + 1; i < 8; i++)
        {
            posX = i;
            posY = i + h;
            if (posX >= 0 && posX < 8 && posY >= 0 && posY < 8)
            {
                Piece dest = map[posX][posY];
                if (dest.type == '!' || dest.isWhite != this->isWhite)
                {
                    r += std::to_string(posX);
                    r += std::to_string(posY);
                    r += '-';
                    if (dest.type != '!')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }

        for (int i = this->x - 1; i >= 0; i--)
        {
            posX = i;
            posY = i + h;
            if (posX >= 0 && posX < 8 && posY >= 0 && posY < 8)
            {
                Piece dest = map[posX][posY];
                if (dest.type == '!' || dest.isWhite != this->isWhite)
                {
                    r += std::to_string(posX);
                    r += std::to_string(posY);
                    r += '-';
                    if (dest.type != '!')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }

        for (int i = this->x + 1; i < 8; i++)
        {
            posX = i;
            posY = -i + u;
            if (posX >= 0 && posX < 8 && posY >= 0 && posY < 8)
            {
                Piece dest = map[posX][posY];
                if (dest.type == '!' || dest.isWhite != this->isWhite)
                {
                    r += std::to_string(posX);
                    r += std::to_string(posY);
                    r += '-';
                    if (dest.type != '!')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }

        for (int i = this->x - 1; i >= 0; i--)
        {
            posX = i;
            posY = -i + u;
            if (posX >= 0 && posX < 8 && posY >= 0 && posY < 8)
            {
                Piece dest = map[posX][posY];
                if (dest.type == '!' || dest.isWhite != this->isWhite)
                {
                    r += std::to_string(posX);
                    r += std::to_string(posY);
                    r += '-';
                    if (dest.type != '!')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }

        posY = this->y;
        for (int i = this->x + 1; i < 8; i++)
        {
            posX = i;
            if (posX >= 0 && posX < 8 && posY >= 0 && posY < 8)
            {
                Piece dest = map[posX][posY];
                if (dest.type == '!' || dest.isWhite != this->isWhite)
                {
                    r += std::to_string(posX);
                    r += std::to_string(posY);
                    r += '-';
                    if (dest.type != '!')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }

        posY = this->y;
        for (int i = this->x - 1; i >= 0; i--)
        {
            posX = i;
            if (posX >= 0 && posX < 8 && posY >= 0 && posY < 8)
            {
                Piece dest = map[posX][posY];
                if (dest.type == '!' || dest.isWhite != this->isWhite)
                {
                    r += std::to_string(posX);
                    r += std::to_string(posY);
                    r += '-';
                    if (dest.type != '!')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }

        posX = this->x;
        for (int i = this->y + 1; i < 8; i++)
        {
            posY = i;
            if (posX >= 0 && posX < 8 && posY >= 0 && posY < 8)
            {
                Piece dest = map[posX][posY];
                if (dest.type == '!' || dest.isWhite != this->isWhite)
                {
                    r += std::to_string(posX);
                    r += std::to_string(posY);
                    r += '-';
                    if (dest.type != '!')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }

        posX = this->x;
        for (int i = this->y - 1; i >= 0; i--)
        {
            posY = i;
            if (posX >= 0 && posX < 8 && posY >= 0 && posY < 8)
            {
                Piece dest = map[posX][posY];
                if (dest.type == '!' || dest.isWhite != this->isWhite)
                {
                    r += std::to_string(posX);
                    r += std::to_string(posY);
                    r += '-';
                    if (dest.type != '!')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }

        r = r.substr(0, r.length() - 1);
        return r;
    }

    string kingAvailableMoves(Piece map[8][8], bool removeDangerousOnes = true)
    {
        string r;
        int posX;
        int posY;
        Piece dist;
        for (int i = -1; i < 2; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                posX = this->x + i;
                posY = this->y + j;
                dist = map[posX][posY];

                if (i == 0 && j == 0)
                {
                    continue;
                }
                if (posX >= 0 && posY >= 0 && posX < 8 && posY < 8 && (dist.isWhite != this->isWhite || dist.type == '!'))
                {
                    Piece newMap[8][8];

                    Piece empty;
                    empty.x = this->x;
                    empty.y = this->y;
                    empty.type = '!';

                    Piece me;
                    me.x = this->x;
                    me.y = this->y;
                    me.type = this->type;
                    me.isWhite = this->isWhite;
                    r += std::to_string(posX);
                    r += std::to_string(posY);
                    r += '-';
                }
            }
        }

        r = r.substr(0, r.length() - 1);
        return r ;
    }

    string bishopAvailableMoves(Piece map[8][8])
    {

        string r;
        int h = this->y - this->x;
        int u = this->y + this->x;
        int posX;
        int posY;
        for (int i = this->x + 1; i < 8; i++)
        {
            posX = i;
            posY = i + h;
            if (posX >= 0 && posX < 8 && posY >= 0 && posY < 8)
            {
                Piece dest = map[posX][posY];
                if (dest.type == '!' || dest.isWhite != this->isWhite)
                {
                    r += std::to_string(posX);
                    r += std::to_string(posY);
                    r += '-';
                    if (dest.type != '!')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }

        for (int i = this->x - 1; i >= 0; i--)
        {
            posX = i;
            posY = i + h;
            if (posX >= 0 && posX < 8 && posY >= 0 && posY < 8)
            {
                Piece dest = map[posX][posY];
                if (dest.type == '!' || dest.isWhite != this->isWhite)
                {
                    r += std::to_string(posX);
                    r += std::to_string(posY);
                    r += '-';
                    if (dest.type != '!')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }

        for (int i = this->x + 1; i < 8; i++)
        {
            posX = i;
            posY = -i + u;
            if (posX >= 0 && posX < 8 && posY >= 0 && posY < 8)
            {
                Piece dest = map[posX][posY];
                if (dest.type == '!' || dest.isWhite != this->isWhite)
                {
                    r += std::to_string(posX);
                    r += std::to_string(posY);
                    r += '-';
                    if (dest.type != '!')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }

        for (int i = this->x - 1; i >= 0; i--)
        {
            posX = i;
            posY = -i + u;
            if (posX >= 0 && posX < 8 && posY >= 0 && posY < 8)
            {
                Piece dest = map[posX][posY];
                if (dest.type == '!' || dest.isWhite != this->isWhite)
                {
                    r += std::to_string(posX);
                    r += std::to_string(posY);
                    r += '-';
                    if (dest.type != '!')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }

        r = r.substr(0, r.length() - 1);
        return r;
    }

    string rookAvailableMoves(Piece map[8][8])
    {

        string r;
        int h = this->y - this->x;
        int u = this->y + this->x;
        int posX;
        int posY;
        posY = this->y;
        for (int i = this->x + 1; i < 8; i++)
        {
            posX = i;
            if (posX >= 0 && posX < 8 && posY >= 0 && posY < 8)
            {
                Piece dest = map[posX][posY];
                if (dest.type == '!' || dest.isWhite != this->isWhite)
                {
                    r += std::to_string(posX);
                    r += std::to_string(posY);
                    r += '-';
                    if (dest.type != '!')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }

        posY = this->y;
        for (int i = this->x - 1; i >= 0; i--)
        {
            posX = i;
            if (posX >= 0 && posX < 8 && posY >= 0 && posY < 8)
            {
                Piece dest = map[posX][posY];
                if (dest.type == '!' || dest.isWhite != this->isWhite)
                {
                    r += std::to_string(posX);
                    r += std::to_string(posY);
                    r += '-';
                    if (dest.type != '!')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }

        posX = this->x;
        for (int i = this->y + 1; i < 8; i++)
        {
            posY = i;
            if (posX >= 0 && posX < 8 && posY >= 0 && posY < 8)
            {
                Piece dest = map[posX][posY];
                if (dest.type == '!' || dest.isWhite != this->isWhite)
                {
                    r += std::to_string(posX);
                    r += std::to_string(posY);
                    r += '-';
                    if (dest.type != '!')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }

        posX = this->x;
        for (int i = this->y - 1; i >= 0; i--)
        {
            posY = i;
            if (posX >= 0 && posX < 8 && posY >= 0 && posY < 8)
            {
                Piece dest = map[posX][posY];
                if (dest.type == '!' || dest.isWhite != this->isWhite)
                {
                    r += std::to_string(posX);
                    r += std::to_string(posY);
                    r += '-';
                    if (dest.type != '!')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }

        r = r.substr(0, r.length() - 1);
        return r;
    }
};
