#include "pch.h"
#include <iostream>
#include <vector>
#include <memory>
#include <stdlib.h>
#include <time.h> 
#include <algorithm>
#include <cmath>

#include "Rabbit.h"
#include "Constants.h"



void Rabbit::try_create_new_rab() {
    int code = get_random(1, 1103);

    if (code == 2) {
        shared_ptr<Rabbit> p1(new Rabbit(this->x, this->y, this->all_rabits));
        (*all_rabits).push_back(p1);
    }


}

void Rabbit::tick() {
    try_create_new_rab();
    move();
}


int Rabbit::getx() {
    return x;
}

int Rabbit::gety() {
    return y;
}

void Rabbit::setx(int value) {
    x = value;
}

void Rabbit::sety(int value) {
    y = value;
}

int Rabbit::get_random(int from, int to) {
    int random;
    random = rand() % to + from;
    return random;
}

Rabbit::Rabbit(int x, int y, vector<shared_ptr<Rabbit>> *all_rabits) {
    this->x = x;
    this->y = y;
    this->all_rabits = all_rabits;
}
Rabbit::~Rabbit() {
}



