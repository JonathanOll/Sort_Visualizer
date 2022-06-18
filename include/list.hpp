#ifndef __LIST_H__
#define __LIST_H__
#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include "main.hpp"


using namespace std;


class Element {
    private:
        int value;
    public:
        Element(int v);
        bool operator<(Element other);
        bool operator<=(Element other);
        bool operator>(Element other);
        bool operator>=(Element other);
        bool operator==(Element other);
        void operator=(Element other);
        int getValue();
};

ostream& operator<<(ostream& os, Element e);
vector<Element> genList(int size);
void swap(vector<Element> &l, int i, int j);
void swap(vector<Element*> &l, int i, int j);
void insert(vector<Element*> &l, Element* e);
void insert(vector<Element*> &l, Element e);
void insert(vector<Element> &l, Element e);
void insert(vector<Element> &l, Element* e);
void draw_list(sf::RenderWindow* window, vector<Element> l);


#endif