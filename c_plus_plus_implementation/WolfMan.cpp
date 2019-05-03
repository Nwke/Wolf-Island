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
#include "WolfMan.h"

#include "Constants.h"




WolfMan::WolfMan(int x, int y, vector<shared_ptr<Rabbit>> *all_rabbits, vector<shared_ptr<WolfMan>> *all_wolfmans, vector<shared_ptr<WolfGirl>> *all_wolfgirls) {
    this->x = x;
    this->y = y;
    this->all_rabbits = all_rabbits;
    this->all_wolfmans = all_wolfmans;
    this->all_wolfgirls = all_wolfgirls;


}
WolfMan::~WolfMan() {
    cout << "Wolf girl was deleted" << endl;;
}

int WolfMan::getx() {
    return x;
}

int WolfMan::gety() {
    return y;
}

void WolfMan::setx(int value) {
    x = value;
}

void WolfMan::sety(int value) {
    y = value;
}

int WolfMan::get_random(int from, int to) {
    int random;
    random = rand() % to + from;
    return random;
}


void WolfMan::move() {
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


void WolfMan::tick() {
    cout << "The wolfman with uid: " << this << " has coord like " << x << " " << y << endl;

    if (this->follow_rabbit) {

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
            cout << "RABBIT HAS BEEN DIED ON COORD" << x << " " << y << " BY " << " The wolfman with uid: " << this << " has coord like " << x << " " << y << endl;


            if (find((*all_rabbits).begin(), (*all_rabbits).end(), followed_rabbit) != (*all_rabbits).end()) {
                (*all_rabbits).erase(remove((*all_rabbits).begin(), (*all_rabbits).end(), followed_rabbit));
            }

            life_points += 1;
        }
        else {
            life_points -= 0.1;

            if (life_points == 0) {
                cout << "The wolfgirl has been died with uid: " << this << " has coord like " << x << " " << y << endl;
                shared_ptr<WolfMan> tmp(this);
                (*all_wolfmans).erase(remove((*all_wolfmans).begin(), (*all_wolfmans).end(), tmp));

            }
        }
    }
    else if (!follow_rabbit) {
        search_wolfgirls();
    }


    if (follow_wolfgirl) {
        cout << "FOLLOW WOLF GIRL" << endl;

        if (x < (*followed_wolfgirl).getx()) {
            x += 1;
        }
        else if (x > (*followed_wolfgirl).getx()) {
            x -= 1;
        }


        if (y < (*followed_wolfgirl).gety()) {
            y += 1;
        }
        else if (y > (*followed_wolfgirl).gety()) {
            y -= 1;
        }



        if ((x == (*followed_wolfgirl).getx()) && (y == (*followed_wolfgirl).gety())) {
            int sex = get_random(0, 1);

            // coords of next childs are a little random

            if (sex == 0) {
                shared_ptr<WolfMan> tmp(new WolfMan(((x + 10) % 20) + 1, ((y + 10) % 20) + 1, all_rabbits, all_wolfmans, all_wolfgirls));

                (*all_wolfmans).push_back(tmp);
            }
            else {
                shared_ptr<WolfGirl> tmp(new WolfGirl(((x + 10) % 20) + 1, ((y + 10) % 20) + 1, all_rabbits, all_wolfgirls));
                (*all_wolfgirls).push_back(tmp);
            }

        }
    }
    else {
        this->move();
    }
}

void WolfMan::search_wolfgirls() {

    if (!follow_wolfgirl) {
        for (auto wolfgirl : *all_wolfgirls) {


            if ((!follow_wolfgirl) && (sqrt(pow(x - (*wolfgirl).getx(), 2) + pow(y - (*wolfgirl).gety(), 2) < 2))) {
                cout << "WOLF WITH UID " << this << " "<< "STARTED TO FOLLOW TO WOLFGIRL " << endl;
                follow_wolfgirl = true;
                followed_wolfgirl = wolfgirl;
                break;
            }
        }
    }

}

void WolfMan::search_rabbit() {
    if (!follow_rabbit) {
        for (auto rab : *all_rabbits) {
            if ((!follow_rabbit) && (sqrt(pow(x - (*rab).getx(), 2) + pow(y - (*rab).gety(), 2) < 2))) {
                follow_rabbit = true;
                followed_rabbit = rab;

                follow_wolfgirl = false;
                followed_wolfgirl = 0;

                cout << "WE FOUND A RABBIT FOR EAT" << endl;
            }
        }
    }

}