#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#define BLANK 0
#define CROSS 1
#define ZERO 2

using namespace sf;
using namespace std;

int main()
{
    RenderWindow window(sf::VideoMode(850, 850), "Tic Tac Toe");
    
    Texture field_tex;
    field_tex.loadFromFile("../image/field.png");
    Sprite field_spr;
    field_spr.setTexture(field_tex);
    
    Texture cross_tex;
    cross_tex.loadFromFile("../image/cross.png");

    Texture zero_tex;
    zero_tex.loadFromFile("../image/zero.png");

    vector<int> board(9, BLANK);
    int cnt = 0;
    bool game_over = false;

    while (window.isOpen())
    {
        if (board[0] == CROSS && board[1] == CROSS && board[2] == CROSS ||
            board[3] == CROSS && board[4] == CROSS && board[5] == CROSS ||
            board[6] == CROSS && board[7] == CROSS && board[8] == CROSS ||
            board[0] == CROSS && board[3] == CROSS && board[5] == CROSS ||
            board[1] == CROSS && board[4] == CROSS && board[7] == CROSS ||
            board[2] == CROSS && board[5] == CROSS && board[8] == CROSS ||
            board[0] == CROSS && board[4] == CROSS && board[8] == CROSS ||
            board[2] == CROSS && board[4] == CROSS && board[6] == CROSS)
        { cout << "CROSS won!" << endl; game_over = true; }

        if (board[0] == ZERO && board[1] == ZERO && board[2] == ZERO ||
            board[3] == ZERO && board[4] == ZERO && board[5] == ZERO ||
            board[6] == ZERO && board[7] == ZERO && board[8] == ZERO ||
            board[0] == ZERO && board[3] == ZERO && board[5] == ZERO ||
            board[1] == ZERO && board[4] == ZERO && board[7] == ZERO ||
            board[2] == ZERO && board[5] == ZERO && board[8] == ZERO ||
            board[0] == ZERO && board[4] == ZERO && board[8] == ZERO ||
            board[2] == ZERO && board[4] == ZERO && board[6] == ZERO)
        { cout << "ZERO won!" << endl; game_over = true; }

        if (cnt == 9) { cout << "TIE!" << endl; game_over = true; }

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed: window.close(); break;
            case Event::KeyPressed:
                if (event.key.code == Keyboard::R)
                {
                    board = vector<int>(9, BLANK);
                    cnt = 0; game_over = false;
                    system("cls");
                }
            case Event::MouseButtonPressed:
                if (game_over) continue;
                if (event.mouseButton.button == Mouse::Left || event.mouseButton.button == Mouse::Right)
                {
                    Vector2f ev = Vector2f(event.mouseButton.x < 825 ? event.mouseButton.x : 825,
                        event.mouseButton.y < 825 ? event.mouseButton.y : 825);
                    int b = cnt % 2 ? ZERO : CROSS;
                    int index = int((ev.y) / 275) * 3 + int((ev.x) / 275);
                    if (board[index] == BLANK) { board[index] = b; cnt++; }
                }
            }
        }
        vector<Sprite> sprites(9);
        for (int i = 0; i < 9; i++)
        {
            if (board[i] == CROSS) sprites[i].setTexture(cross_tex);
            if (board[i] == ZERO)  sprites[i].setTexture(zero_tex);
            sprites[i].setPosition(Vector2f(25 + 275 * (i % 3), 25 + 275 * (i / 3)));
        }

        window.clear();
        window.draw(field_spr);
        for (auto i : sprites) window.draw(i);
        window.display();
    }

    return 0;
}