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
    int code = get_random(1, 10);

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
    //cout << "I was created and i have x and y: " << x << " " << y << endl;
}
Rabbit::~Rabbit() {
    cout << "Rabbit was deleted" << endl;;
}



void Rabbit::move() {
    int code_movement = get_random(1, 9);

    if ((code_movement == 1) && (y != FIELD_Y_D)) {
        y -= 1;
    }
    if ((code_movement == 2) && (x != FIELD_X_D)) {
        x -= 1;
    }
    if ((code_movement == 3) && (y != FIELD_Y_U)) {
        y += 1;
    }
    if ((code_movement == 4) && (y != FIELD_X_U)) {
        x += 1;
    }
    if ((code_movement == 5) && (x != FIELD_X_D) && (y != FIELD_Y_U)) {
        x -= 1;
        y += 1;
    }
    if ((code_movement == 6) && (x != FIELD_X_D) && (y != FIELD_Y_D)) {
        x -= 1;
        y -= 1;
    }
    if ((code_movement == 7) && (x != FIELD_X_U) && (y != FIELD_Y_U)) {
        x += 1;
        y += 1;
    }
    if ((code_movement == 8) && (x != FIELD_X_U) && (y != FIELD_Y_D)) {
        x += 1;
        y -= 1;
    }
    if (code_movement == 9) {

    }
}
