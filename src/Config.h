// std::string defaultChessSetup="RB NB BB QB KB BB NB RB\nPB PB PB PB PB PB PB PB\n-- -- -- -- -- -- -- --\n-- -- -- -- -- -- -- --\n-- -- -- -- -- -- -- --\n-- -- -- -- -- -- -- --\nPW PW PW PW PW PW PW PW\nRW NW BW QW KW BW NW RW";
std::string defaultChessSetup="-- -- BW -- KB -- -- RB\n-- -- KW -- PB PB PB --\n-- -- -- -- -- -- -- --\n-- -- -- -- -- QW -- --\n-- -- -- -- PW -- -- --\n-- -- -- -- -- -- -- --\n-- -- -- -- -- -- -- --\n-- -- -- -- -- -- -- --";
int getConfig(string key) {
    if(key=="boardPositionX") {return 20;}
    if(key=="boardPositionY") {return 20;}
    if(key=="boardWith") {return 600;}
    if(key=="boardHeight") {return 600;}

}