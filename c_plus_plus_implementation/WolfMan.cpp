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
    this->x = value;
}

void WolfMan::sety(int value) {
    this->y = value;
}

int WolfMan::get_random(int from, int to) {
    int random;
    random = rand() % to + from;
    return random;
}


void WolfMan::move() {
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


void WolfMan::tick() {
    cout << "The wolfman with uid: " << this << " has coord like " << x << " " << y << endl;

    if (this->follow_rabbit) {

        if (find((*(this->all_rabbits)).begin(), (*(this->all_rabbits)).end(), this->followed_rabbit) != (*all_rabbits).end()) {
            this->follow_rabbit = false;
            this->followed_rabbit = 0;
        }
    }

    this->search_rabbit();

    if (this->follow_rabbit) {

        if (this->x < (*followed_rabbit).getx()) {
            this->x += 1;
        }
        else if (this->x > (*followed_rabbit).getx()) {
            this->x -= 1;
        }


        if (this->y < (*followed_rabbit).gety()) {
            this->y += 1;
        }
        else if (this->y > (*followed_rabbit).gety()) {
            this->y -= 1;
        }

        if ((this->x == (*followed_rabbit).getx()) && (this->y == (*followed_rabbit).gety())) {
            cout << "RABBIT HAS BEEN DIED ON COORD" << x << " " << y << " BY " << " The wolfman with uid: " << this << " has coord like " << x << " " << y << endl;


            if (find((*(this->all_rabbits)).begin(), (*(this->all_rabbits)).end(), this->followed_rabbit) != (*(this->all_rabbits)).end()) {
                (*(this->all_rabbits)).erase(remove((*(this->all_rabbits)).begin(), (*(this->all_rabbits)).end(), this->followed_rabbit));
            }

            this->life_points += 1;
        }
        else {
            this->life_points -= 0.1;

            if (this->life_points == 0) {
                cout << "The wolfgirl has been died with uid: " << this << " has coord like " << x << " " << y << endl;
                shared_ptr<WolfMan> tmp(this);
                (*(this->all_wolfmans)).erase(remove((*(this->all_wolfmans)).begin(), (*(this->all_wolfmans)).end(), tmp));

            }
        }
    }
    else if (!this->follow_rabbit) {
        this->search_wolfgirls();
    }


    if (this->follow_wolfgirl) {
        cout << "FOLLOW WOLF GIRL" << endl;

        if (this->x < (*followed_wolfgirl).getx()) {
            this->x += 1;
        }
        else if (this->x > (*followed_wolfgirl).getx()) {
            this->x -= 1;
        }


        if (this->y < (*followed_wolfgirl).gety()) {
            this->y += 1;
        }
        else if (this->y > (*followed_wolfgirl).gety()) {
            this->y -= 1;
        }



        if ((this->x == (*followed_wolfgirl).getx()) && (this->y == (*followed_wolfgirl).gety())) {
            int sex = this->get_random(0, 1);

            if (sex == 0) {
                shared_ptr<WolfMan> tmp(new WolfMan(((this->x + 10) % 20) + 1, ((this->y + 10) % 20) + 1, this->all_rabbits, this->all_wolfmans, this->all_wolfgirls));

                (*(this->all_wolfmans)).push_back(tmp);
            }
            else {
                shared_ptr<WolfGirl> tmp(new WolfGirl(((this->x + 10) % 20) + 1, ((this->y + 10) % 20) + 1, this->all_rabbits, this->all_wolfgirls));
                (*(this->all_wolfgirls)).push_back(tmp);
            }

        }

    }
    else {
        this->move();
    }




}

void WolfMan::search_wolfgirls() {

    if (!this->follow_wolfgirl) {
        for (auto wolfgirl : *this->all_wolfgirls) {


            if ((!this->follow_wolfgirl) && (sqrt(pow(this->x - (*wolfgirl).getx(), 2) + pow(this->y - (*wolfgirl).gety(), 2) < 2))) {
                cout << "WOLF WITH UID " << this << " "<< "STARTED TO FOLLOW TO WOLFGIRL " << endl;
                this->follow_wolfgirl = true;
                this->followed_wolfgirl = wolfgirl;
                break;
            }
        }
    }

}

void WolfMan::search_rabbit() {
    if (!this->follow_rabbit) {
        for (auto rab : *this->all_rabbits) {


            if ((!this->follow_rabbit) && (sqrt(pow(this->x - (*rab).getx(), 2) + pow(this->y - (*rab).gety(), 2) < 2))) {


                this->follow_rabbit = true;
                this->followed_rabbit = rab;

                this->follow_wolfgirl = false;
                this->followed_wolfgirl = 0;

                cout << "WE FOUND A RABBIT FOR EAT" << endl;
            }
        }
    }

}