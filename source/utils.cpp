#include "utils.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include "SFML/Graphics.hpp"

using namespace std;


void draw_text(sf::RenderWindow* window, sf::Font font, wstring t, int x, int y) {
    sf::Text text;
    text.setCharacterSize(20);
    text.setString(t);
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(x, y));
    window->draw(text); 
};
