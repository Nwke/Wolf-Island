#include "pch.h"
#include <iostream>
#include <vector>
#include <memory>
#include <stdlib.h>
#include <time.h> 
#include <algorithm>
#include <cmath>

#include "Rabbit.h"
#include "WolfGirl.h"

#include "Constants.h"



WolfGirl::WolfGirl(int x, int y, vector<shared_ptr<Rabbit>> *all_rabbits, vector<shared_ptr<WolfGirl>> *all_wolfgirls) {
    this->x = x;
    this->y = y;
    this->all_rabbits = all_rabbits;
    this->all_wolfgirls = all_wolfgirls;


}


WolfGirl::~WolfGirl() {
    cout << "Wolf girl was deleted" << endl;;
}


int WolfGirl::getx() {
    return x;
}

int WolfGirl::gety() {
    return y;
}

void WolfGirl::setx(int value) {
    this->x = value;
}

void WolfGirl::sety(int value) {
    y = value;
}

int WolfGirl::get_random(int from, int to) {
    int random;
    random = rand() % to + from;
    return random;
}

void WolfGirl::search_rabbit() {
    if (!follow_rabbit) {
        for (auto rab : *this->all_rabbits) {


            if ((!follow_rabbit) && (sqrt(pow(x - (*rab).getx(), 2) + pow(y - (*rab).gety(), 2) < 2))) {


                follow_rabbit = true;
                followed_rabbit = rab;
                break;



                cout << "WE FOUND A RABBIT FOR EAT" << endl;
            }
        }
    }
}

void WolfGirl::tick() {
    cout << "The wolfgirl with uid: " << this << " has coord like " << x << " " << y << endl;

    if (follow_rabbit) {

        if (find((*all_rabbits).begin(), (*all_rabbits).end(), followed_rabbit) != (*all_rabbits).end()) {
            follow_rabbit = false;
            followed_rabbit = 0;
        }
    }

    search_rabbit();

    if (follow_rabbit) {

        if (x < (*followed_rabbit).getx()) {
            x += 1;
        }
        else if (x > (*followed_rabbit).getx()) {
            x -= 1;
        }


        if (y < (*followed_rabbit).gety()) {
            y += 1;
        }
        else if (y > (*followed_rabbit).gety()) {
            y -= 1;
        }

        if ((x == (*followed_rabbit).getx()) && (y == (*followed_rabbit).gety())) {
            cout << "RABBIT HAS BEEN DIED ON COORD" << x << " " << y << " BY " << " The wolfgirl with uid: " << this << " has coord like " << x << " " << y << endl;

            if (find((*all_rabbits).begin(), (*all_rabbits).end(), followed_rabbit) != (*all_rabbits).end()) {
                (*all_rabbits).erase(remove((*all_rabbits).begin(), (*all_rabbits).end(), followed_rabbit));
            }

            life_points += 1;
        }
        else {
            life_points -= 0.1;

            if (life_points == 0) {
                cout << "The wolfgirl has been died with uid: " << this << " has coord like " << x << " " << y << endl;
                shared_ptr<WolfGirl> tmp(this);
                (*all_wolfgirls).erase(remove((*all_wolfgirls).begin(), (*all_wolfgirls).end(), tmp));

            }
        }
    }
    else {
        move();
    }
}

void WolfGirl::move() {
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
