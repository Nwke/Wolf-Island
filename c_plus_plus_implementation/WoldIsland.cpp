#include "pch.h"
#include <iostream>
#include <vector>
#include <memory>
#include <stdlib.h>
#include <time.h> 
#include <algorithm>
#include <cmath>

const int FIELD_X_D = 1;
const int FIELD_X_U = 20;
 
const int FIELD_Y_D = 1;
const int FIELD_Y_U = 20;

using namespace std;



class Animal {
public:

    virtual void move() {
        
    }

    virtual ~Animal() {

    }

};



class Rabbit : public Animal {
private:
    int x;
    int y;
public:

    vector<shared_ptr<Rabbit>> *all_rabits;

    int getx() {
        return x;
    }

    int gety() {
        return y;
    }

    void setx(int value) {
        this->x = value;
    }

    void sety(int value) {
        this->y = value;
    }

    int get_random(int from, int to) {
        int random;
        random = rand() % to + from;
        return random;
    }

    Rabbit(int x, int y, vector<shared_ptr<Rabbit>> *all_rabits) {
        this->x = x;
        this->y = y;
        this->all_rabits = all_rabits;
        //cout << "I was created and i have x and y: " << x << " " << y << endl;
    }
    ~Rabbit() {
        cout << "Rabbit was deleted" << endl;;
    }



    void move() {
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


    void try_create_new_rab() {
        int code = get_random(1, 10);
       
        if (code == 2) { 
            shared_ptr<Rabbit> p1(new Rabbit(this->x, this->y, this->all_rabits));
            (*all_rabits).push_back(p1);
        }
       

    }

    void tick() {
        try_create_new_rab();
        move();
    }

};


class WolfGirl : public Animal {
private:
    int x;
    int y;
public:

    vector<shared_ptr<Rabbit>> *all_rabbits;
    vector<shared_ptr<WolfGirl>> *all_wolfgirl;


    double life_points = 1;

    bool follow_rabbit = false;
    shared_ptr<Rabbit> followed_rabbit;


    int getx() {
        return x;
    }

    int gety() {
        return y;
    }

    void setx(int value) {
        this->x = value;
    }

    void sety(int value) {
        this->y = value;
    }

    int get_random(int from, int to) {
        int random;
        random = rand() % to + from;
        return random;
    }



    WolfGirl(int x, int y, vector<shared_ptr<Rabbit>> *all_rabbits, vector<shared_ptr<WolfGirl>> *all_wolfgirl) {
        this->x = x;
        this->y = y;
        this->all_rabbits = all_rabbits;
        this->all_wolfgirl = all_wolfgirl;
    

    }
    ~WolfGirl() {
        cout << "Wolf girl was deleted" << endl;;
    }

    void move() {
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


    void tick() {

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
                    (*(this->all_wolfgirl)).erase(remove((*(this->all_wolfgirl)).begin(), (*(this->all_wolfgirl)).end(), tmp));

                }
            }
        }
        else {
            this->move();
        }
    }

   void search_rabbit() {

       if (!this->follow_rabbit) {
           
           
           // cout << this->all_wolfgirl.size();
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
};


class WolfMan : public Animal {
private:
    int x;
    int y;
public:

    vector<shared_ptr<Rabbit>> *all_rabbits;
    vector<shared_ptr<WolfMan>> *all_wolfman;
    vector<shared_ptr<WolfGirl>> *all_wolfgirls;


    double life_points = 1;

    bool follow_rabbit = false;
    bool follow_wolfgirl = false;

    
    shared_ptr<Rabbit> followed_rabbit;
    shared_ptr<WolfGirl> followed_wolfgirl;

    int getx() {
        return x;
    }

    int gety() {
        return y;
    }

    void setx(int value) {
        this->x = value;
    }

    void sety(int value) {
        this->y = value;
    }

    int get_random(int from, int to) {
        int random;
        random = rand() % to + from;
        return random;
    }



    WolfMan(int x, int y, vector<shared_ptr<Rabbit>> *all_rabbits, vector<shared_ptr<WolfMan>> *all_wolfman, vector<shared_ptr<WolfGirl>> *all_wolfgirls) {
        this->x = x;
        this->y = y;
        this->all_rabbits = all_rabbits;
        this->all_wolfman = all_wolfman;
        this->all_wolfgirls = all_wolfgirls;


    }
    ~WolfMan() {
        cout << "Wolf girl was deleted" << endl;;
    }

    void move() {
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


    void tick() {
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
                    (*(this->all_wolfman)).erase(remove((*(this->all_wolfman)).begin(), (*(this->all_wolfman)).end(), tmp));

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
                    shared_ptr<WolfMan> tmp(new WolfMan(((this->x + 10) % 20) + 1, ((this->y + 10) % 20) + 1, this->all_rabbits, this->all_wolfman, this->all_wolfgirls));

                    (*(this->all_wolfman)).push_back(tmp);
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

    void search_wolfgirls() {

        if (!this->follow_wolfgirl) {
            // cout << this->all_wolfgirl.size();
            for (auto wolfgirl : *this->all_wolfgirls) {


                if ((!this->follow_wolfgirl) && (sqrt(pow(this->x - (*wolfgirl).getx(), 2) + pow(this->y - (*wolfgirl).gety(), 2) < 2))) {
                    cout << "TOOOK" << endl;
                    this->follow_wolfgirl = true;
                    this->followed_wolfgirl = wolfgirl;
                    break;

                   
                }
            }
        }

    }

    void search_rabbit() {
        if (!this->follow_rabbit) {
            // cout << this->all_wolfgirl.size();
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
};



int main()
{
    vector<shared_ptr<Rabbit>> all_rabbits;
    vector<shared_ptr<WolfGirl>> all_wolfgirl;
    vector<shared_ptr<WolfMan>> all_wolfman;
    
    shared_ptr<Rabbit> rabbit1(new Rabbit(1, 1, &all_rabbits));
    shared_ptr<WolfGirl> wolfgirl1(new WolfGirl(20, 20, &all_rabbits, &all_wolfgirl));
    shared_ptr<WolfMan> wolfman1(new WolfMan(15, 15, &all_rabbits, &all_wolfman, &all_wolfgirl));

    all_rabbits.push_back(rabbit1);
    all_wolfgirl.push_back(wolfgirl1);
    all_wolfman.push_back(wolfman1);

    // cout << all_rabbits.size();

    
    

    while (all_rabbits.size() != 0) {
        // all rabbits
        vector<shared_ptr<Rabbit>> rabbits_copy(all_rabbits);
        vector<shared_ptr<WolfGirl>> wolfgirl_copy(all_wolfgirl);
        vector<shared_ptr<WolfMan>> wolfman_copy(all_wolfman);

  

        for (auto rab : rabbits_copy) {
            (*rab).tick();
        }



        for (auto wolf_girl : wolfgirl_copy) {
            (*wolf_girl).tick();
            cout << "POINTS: WOLFGIRL: " << (*wolf_girl).life_points << endl;
        }

        for (auto wolf_man : wolfman_copy) {
            (*wolf_man).tick();
            cout << "Size all rabits is: " << all_rabbits.size() << endl;
            cout << "POINTS: WOLFMAN: " << (*wolf_man).life_points << endl;
        }

        cout << "Size all rabits is: " << all_rabbits.size() << endl;
        cout << "Size all wolfgirl is: " << all_wolfgirl.size() << endl;
        cout << "Size all wolfman is: " << all_wolfman.size() << endl;
        
        
    }

    cout << "=========================" << endl;
    cout << "Size all rabits is: " << all_rabbits.size() << endl;
    cout << "Size all wolfgirl is: " << all_wolfgirl.size() << endl;
    cout << "Size all wolfman is: " << all_wolfman.size() << endl;





    std::cout << "Hello World!\n"; 
    all_rabbits.clear();
}


