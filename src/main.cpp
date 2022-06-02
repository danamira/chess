
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
    cout << ">> Start from the beginning or enter a board manually? Choose an option." << std::endl;
    cout << "-- D | Start with the default board." << std::endl;
    cout << "-- M | Enter the board manually." << std::endl;
    cout << " -> ";

    char ask;
    cin >> ask;
    string givenBoard;
    string line;
    char askTurn;
    if (ask == 'M' || ask == 'm')
    {
        for (int i = 0; i < 8; i++)
        {

            for (int j = 0; j < 8; j++)
            {
                line = "";
                cin >> line;
                givenBoard += line;
                if (j != 7)
                {
                    givenBoard += ' ';
                }
            }
            givenBoard += '\n';
        }
        cout << ">> Whose turn is it? (Enter `B` for black and `W` for white.)" << std::endl;

        cout << "->";
        cin >> askTurn;
    }

    sf::RenderWindow window(sf::VideoMode(1010, 640), "Smart Chess", sf::Style::Titlebar | sf::Style::Close);
    window.RenderTarget::clear(sf::Color(43.f, 35.f, 33.f));

    sf::Texture texture;

    texture.loadFromFile("back.png");
    sf::Vector2u size = texture.getSize();
    texture.setSmooth(true);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setOrigin(0, 0);
    Board chessBoard;

    if (givenBoard.length() == 0)
    {
        chessBoard.setup();
    }
    else
    {
        chessBoard.setup(givenBoard, askTurn == 'W' || askTurn == 'w');
    }
    // cout << chessBoard.textFacade();

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
                        chessBoard.flipped = !chessBoard.flipped;
                    }
                    if (mouseX > 825 && mouseX < 1000 && mouseY > 200 && mouseY < 350)
                    {
                        if (chessBoard.isWhiteTurn)
                        {
                            chessBoard.blackWon = true;
                        }
                        else
                        {
                            chessBoard.whiteWon = true;
                        }
                        chessBoard.finished = true;
                    }
                    if (mouseX > 825 && mouseX < 1000 && mouseY > 350 && mouseY < 500)
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