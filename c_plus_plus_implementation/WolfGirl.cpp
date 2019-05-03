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
    this->y = value;
}

int WolfGirl::get_random(int from, int to) {
    int random;
    random = rand() % to + from;
    return random;
}

void WolfGirl::search_rabbit() {
    if (!this->follow_rabbit) {
        for (auto rab : *this->all_rabbits) {


            if ((!this->follow_rabbit) && (sqrt(pow(this->x - (*rab).getx(), 2) + pow(this->y - (*rab).gety(), 2) < 2))) {


                this->follow_rabbit = true;
                this->followed_rabbit = rab;
                break;



                cout << "WE FOUND A RABBIT FOR EAT" << endl;
            }
        }
    }
}

void WolfGirl::tick() {
    cout << "The wolfgirl with uid: " << this << " has coord like " << x << " " << y << endl;

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
            cout << "RABBIT HAS BEEN DIED ON COORD" << x << " " << y << " BY " << " The wolfgirl with uid: " << this << " has coord like " << x << " " << y << endl;

            if (find((*(this->all_rabbits)).begin(), (*(this->all_rabbits)).end(), this->followed_rabbit) != (*(this->all_rabbits)).end()) {
                (*(this->all_rabbits)).erase(remove((*(this->all_rabbits)).begin(), (*(this->all_rabbits)).end(), this->followed_rabbit));
            }

            this->life_points += 1;
        }
        else {
            this->life_points -= 0.1;

            if (this->life_points == 0) {
                cout << "The wolfgirl has been died with uid: " << this << " has coord like " << x << " " << y << endl;
                shared_ptr<WolfGirl> tmp(this);
                (*(this->all_wolfgirls)).erase(remove((*(this->all_wolfgirls)).begin(), (*(this->all_wolfgirls)).end(), tmp));

            }
        }
    }
    else {
        this->move();
    }
}

void WolfGirl::move() {
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
