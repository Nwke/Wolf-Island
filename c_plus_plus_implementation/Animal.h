#pragma once
class Animal
{
public:
    Animal();
    ~Animal();
    virtual void move();
    int get_random(int, int);
    int x;
    int y;
};

