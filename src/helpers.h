
// .: Helpers header: This file includes helper functions which are used often across the program. :. //
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
