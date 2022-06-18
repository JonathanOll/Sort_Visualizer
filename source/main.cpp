#define _USE_MATH_DEFINES

#include "main.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <random>
#include <thread>
#include <cmath>
#include "SFML/Graphics.hpp"
#include <utils.hpp>
#include <list.hpp>
#include "tri.hpp"

using namespace std;

sf::RenderWindow* window;
int SCREEN_WIDTH = 1280, SCREEN_HEIGHT = 720;


sf::Font font;
sf::Clock tick_clock;
sf::Clock fps_clock;

vector<Element>* current_list = nullptr;
int current_sort = 0;

void setup(){

    static vector<Element> l = genList(10000);
    random_shuffle(l.begin(), l.end());
    current_list = &l;

    init();

    font.loadFromFile("res/font.ttf");

    srand(time(0));
    
    window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Sort Visualizer", sf::Style::Close);

}


void handleEvent(sf::Event event) {
    if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape)) {
        window->close();
        exit(0);
    } else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Key::Space) launch_function(current_sort, *current_list);
        else if (event.key.code == sf::Keyboard::Key::Left){
            current_sort -= 1;
            if (current_sort < 0) current_sort = sort_count() - 1;
        } else if (event.key.code == sf::Keyboard::Key::Right) {
            current_sort += 1;
            if (current_sort > sort_count() - 1) current_sort = 0;
        }
    }
}

void draw() {

    if (fps_clock.getElapsedTime().asSeconds() < 1/25.f) {
        return;
    }

    window->clear();

    if (current_list != nullptr) {
        draw_list(window, *current_list);
    }
    

    draw_text(window, font, name(current_sort), 5, 5);

    window->display();

    fps_clock.restart();

}

void update(float dt) {
    
    sf::Event event;

    while(window->pollEvent(event)){
        handleEvent(event);
    }

    tick_clock.restart();

}

void tick() {

    if (tick_clock.getElapsedTime().asSeconds() >= 1/60.f) update(tick_clock.restart().asSeconds());
   
    draw();
    
}


int main(){

    setup();

    srand(time(0));

    while(window->isOpen()){
        
        tick();

    }

    return EXIT_SUCCESS;
}



