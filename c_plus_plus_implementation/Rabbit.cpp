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
    this->x = value;
}

void Rabbit::sety(int value) {
    this->y = value;
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

    if ((code_movement == 1) && (this->y != FIELD_Y_D)) {
        this->y -= 1;
    }
    if ((code_movement == 2) && (this->x != FIELD_X_D)) {
        this->x -= 1;
    }
    if ((code_movement == 3) && (this->y != FIELD_Y_U)) {
        this->y += 1;
    }
    if ((code_movement == 4) && (this->y != FIELD_X_U)) {
        this->x += 1;
    }
    if ((code_movement == 5) && (this->x != FIELD_X_D) && (this->y != FIELD_Y_U)) {
        this->x -= 1;
        this->y += 1;
    }
    if ((code_movement == 6) && (this->x != FIELD_X_D) && (this->y != FIELD_Y_D)) {
        this->x -= 1;
        this->y -= 1;
    }
    if ((code_movement == 7) && (this->x != FIELD_X_U) && (this->y != FIELD_Y_U)) {
        this->x += 1;
        this->y += 1;
    }
    if ((code_movement == 8) && (this->x != FIELD_X_U) && (this->y != FIELD_Y_D)) {
        this->x += 1;
        this->y -= 1;
    }
    if (code_movement == 9) {

    }
}
