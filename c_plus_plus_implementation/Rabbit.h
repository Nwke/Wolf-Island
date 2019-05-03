#pragma once
#include "pch.h"


using namespace std;

class Rabbit
{
public:
    Rabbit(int, int, vector<shared_ptr<Rabbit>>*);
    ~Rabbit();

    int getx();

    int gety();

    void setx(int);

    void sety(int);

    int get_random(int, int);

    void move();
    void try_create_new_rab();
    void tick();


    vector<shared_ptr<Rabbit>> *all_rabits;

private:
    int x;
    int y;
};

