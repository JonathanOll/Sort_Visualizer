#define _USE_MATH_DEFINES

#include <list.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include "main.hpp"


using namespace std;


int NUMBER_OF_TURN = 31;
float BASE_ANGLE = -90.f;
vector<Element> selected;


Element::Element(int v) {
    value = v;
}

bool Element::operator<(Element other) {
    selected.clear();
    tick(); selected.push_back(*this); selected.push_back(other);
    return value < other.value;
}

bool Element::operator<=(Element other) {
    selected.clear();
    tick(); selected.push_back(*this); selected.push_back(other);
    return value <= other.value;
}

bool Element::operator>(Element other) {
    selected.clear();
    tick(); selected.push_back(*this); selected.push_back(other);
    return value > other.value;
}

bool Element::operator>=(Element other) {
    selected.clear();
    tick(); selected.push_back(*this); selected.push_back(other);
    return value >= other.value;
}

bool Element::operator==(Element other) {
    return value == other.value;
}

void Element::operator=(Element other) {
    selected.clear();
    tick(); selected.push_back(*this); selected.push_back(other);
    value = other.value;
}

int Element::getValue() {
    return value;
}

ostream& operator<<(ostream& os, Element e) {
    os << e.getValue();
    return os;
}

vector<Element> genList(int size) {
    vector<Element> res;
    for (int i = 0; i < size; i++) res.push_back(Element(i+1));
    return res;
}

void swap(vector<Element> &l, int i, int j) {
    selected.clear();
    tick(); selected.push_back(l[i]); selected.push_back(l[j]);
    Element temp = l[i];
    l[i] = l[j];
    l[j] = temp;
}

void swap(vector<Element*> &l, int i, int j) {
    selected.clear();
    tick(); selected.push_back(*l[i]); selected.push_back(*l[j]);
    Element* temp = l[i];
    l[i] = l[j];
    l[j] = temp;
}

void insert(vector<Element*> &l, Element* e) {
    selected.clear();
    tick(); selected.push_back(*e);
    l.insert(l.begin(), e);
}

void insert(vector<Element*> &l, Element e) {
    selected.clear();
    tick(); selected.push_back(e);
    l.insert(l.begin(), &e);
}

void insert(vector<Element> &l, Element e) {
    tick(); selected.push_back(e);
    l.insert(l.begin(), e);
}

void insert(vector<Element> &l, Element* e) {
    selected.clear();
    tick(); selected.push_back(*e);
    l.insert(l.begin(), *e);
}

sf::Color getColor(int i, int ma) {
    int x = i / (float)ma * 767.f;
    int r = x < 256 ? 255 - x : x < 512 ? 0 : x - 512;
    int g = x < 256 ? x : x < 512 ? 511 - x : 0;
    int b = x < 256 ? 0 : x < 512 ? x - 256 : 767 - x;
    return sf::Color(r, g, b);
}

void draw_list(sf::RenderWindow* window, vector<Element> l) {
    
    int width = window->getSize().x, height = window->getSize().y;

    int element_per_turn = l.size() / (float) NUMBER_OF_TURN;

    for (int i = 0; i < l.size(); i++) {
        int dist = (height - 20 * 2) / 2.f / NUMBER_OF_TURN * l[i].getValue() / (float)l.size() + i / (float)element_per_turn * (height - 20 * 2) / 2.f / NUMBER_OF_TURN;
        float angle = BASE_ANGLE * M_PI / 180.f + i / (float)l.size() * 2.f * M_PI * NUMBER_OF_TURN;

        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(3.f, 3.f));
        rect.setPosition(sf::Vector2f(width / 2.f + dist * (float)cosf(angle), height / 2.0f + dist * (float)sinf(angle)));
        if (find(selected.begin(), selected.end(), l[i]) != selected.end()) {
            rect.setFillColor(sf::Color(255, 255, 255));
        }else {
            rect.setFillColor(getColor(l[i].getValue(), l.size()));
        }

        window->draw(rect);
    }

}


