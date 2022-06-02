
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

#include <vector>
#include "Helpers.h"
#include "Piece.h"
#include "Board.h"
#include "Config.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1010, 640), "Smart Chess",sf::Style::Titlebar | sf::Style::Close);
    window.RenderTarget::clear(sf::Color(43.f, 35.f, 33.f));

    sf::Texture texture;

    texture.loadFromFile("back.png");
    sf::Vector2u size = texture.getSize();
    texture.setSmooth(true);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setOrigin(0, 0);
    Board chessBoard;
    chessBoard.setup();
    cout << chessBoard.textFacade();

    window.setFramerateLimit(30);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    int mouseX = event.mouseButton.x;
                    int mouseY = event.mouseButton.y;

                    if (mouseX > 20 && mouseX < 620 && mouseY > 20 && mouseY < 620)
                    {
                        chessBoard.selectPiece(mouseX - 20, mouseY - 20);
                    }
                    if (mouseX > 640 && mouseX < 940 && mouseY > 80 && mouseY < 110)
                    {
                        // chessBoard.calculateDefenses = !chessBoard.calculateDefenses;
                        if (chessBoard.DangerousMoves.length() == 0 && chessBoard.PieceSelected())
                        {
                            if (chessBoard.isWhiteTurn)
                            {
                                chessBoard.DangerousMoves = chessBoard.calculateWhiteDefense();
                            }
                            else
                            {
                                chessBoard.DangerousMoves = chessBoard.calculateBlackDefense();
                            }
                            chessBoard.calculated = true;
                        }
                    }
                    if (mouseX > 640 && mouseX < 825 && mouseY > 200 && mouseY < 350)
                    {
                        chessBoard.setup();
                    }
                    if (mouseX > 640 && mouseX < 825 && mouseY > 350 && mouseY < 500)
                    {
                        chessBoard.flipped=!chessBoard.flipped;
                    }
                     if (mouseX > 825 && mouseX < 1000 && mouseY > 200 && mouseY <350)
                    {
                        if(chessBoard.isWhiteTurn) {
                            chessBoard.blackWon=true;
                        }
                        else {
                            chessBoard.whiteWon=true;
                        }
                        chessBoard.finished=true;
                    }
                    if (mouseX > 825 && mouseX <1000 && mouseY > 350 && mouseY < 500)
                    {
                        window.close();
                        break;
                    }
                }
                break;
            }
        }

        window.clear();
        window.draw(sprite);

        // cout<<chessBoard.getPieceByPosition(1,0).alias();
        chessBoard.render(window);
        window.display();
    }
    return 0;
}