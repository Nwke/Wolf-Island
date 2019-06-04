#pragma once
#include "pch.h"
#include "Animal.h"


class WolfMan : public Animal
{
public:
    WolfMan(int x, int y, vector<shared_ptr<Rabbit>> *all_rabbits, vector<shared_ptr<WolfMan>> *all_wolfman, vector<shared_ptr<WolfGirl>> *all_wolfgirls);
    ~WolfMan();

    vector<shared_ptr<Rabbit>> *all_rabbits;
    vector<shared_ptr<WolfMan>> *all_wolfmans;
    vector<shared_ptr<WolfGirl>> *all_wolfgirls;


    double life_points = 1;

    bool follow_rabbit = false;
    bool follow_wolfgirl = false;


    shared_ptr<Rabbit> followed_rabbit;
    shared_ptr<WolfGirl> followed_wolfgirl;


    int getx();

    int gety();

    void setx(int);

    void sety(int);

    int get_random(int, int);

    void tick();

    void search_rabbit();
    void search_wolfgirls();

};

