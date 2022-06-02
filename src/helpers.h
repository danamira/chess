
// .: Helpers header: This file includes helper functions which are used often across the program. :. //
string getCoordinates(int x, int y)
{
    string mnt = to_string(10 * x + y);
    if (x == 0)
    {
        mnt = '0' + mnt;
    }
    return mnt;
}

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

string defaultSetup()
{
    return "RB NB BB QB KB BB NB RB\nPB PB PB PB PB PB PB PB\n-- -- -- -- -- -- -- --\n-- -- -- -- -- -- -- --\n-- -- -- -- -- -- -- --\n-- -- -- -- -- -- -- --\nPW PW PW PW PW PW PW PW\nRW NW BW QW KW BW NW RW";
    // return "-- -- BW -- KB -- -- RB\n-- -- KW -- PB PB PB --\n-- -- -- -- -- -- -- --\n-- -- -- -- -- QW -- --\n-- -- -- -- PW -- -- --\n-- -- -- -- -- -- -- --\n-- -- -- -- -- -- -- --\n-- -- -- -- -- -- -- --";
}