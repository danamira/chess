std::string defaultChessSetup="RB NB BB QB KB BB NB RB\nPB PB PB PB PB PB PB PB\n-- -- -- -- -- -- -- --\n-- -- -- -- -- -- -- --\n-- -- -- -- -- -- -- --\n-- -- -- -- -- -- -- --\nPW PW PW PW PW PW PW PW\nRW NW BW QW KW BW NW RW";

int getConfig(string key) {
    if(key=="boardPositionX") {return 20;}
    if(key=="boardPositionY") {return 20;}
    if(key=="boardWith") {return 600;}
    if(key=="boardHeight") {return 600;}

}