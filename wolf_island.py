import random
import math
import time

FIELD_X_D = 1
FIELD_X_U = 20

FIELD_Y_D = 1
FIELD_Y_U = 20


class Animal:
    all_animals = []

    all_rabbits = []
    all_wolfman = []
    all_wolfgirl = []

    def __init__(self, x: int = 1, y: int = 1):
        Animal.all_animals.append(self)

        self.x = x
        self.y = y
        self.life_points = 1

    def move(self) -> None:
        code_movement: int = random.randint(1, 9)

        if code_movement == 1 and self.y != FIELD_Y_D:
            self.y -= 1
        elif code_movement == 2 and self.x != FIELD_X_D:
            self.x -= 1
        elif code_movement == 3 and self.y != FIELD_Y_U:
            self.y += 1
        elif code_movement == 4 and self.x != FIELD_X_U:
            self.x += 1

        elif code_movement == 5 and self.x != FIELD_X_D and self.y != FIELD_Y_U:
            self.x -= 1
            self.y += 1
        elif code_movement == 6 and self.x != FIELD_X_D and self.y != FIELD_Y_D:
            self.x -= 1
            self.y -= 1
        elif code_movement == 7 and self.x != FIELD_X_U and self.y != FIELD_Y_U:
            self.x += 1
            self.y += 1
        elif code_movement == 8 and self.x != FIELD_X_U and self.y != FIELD_Y_D:
            self.x += 1
            self.y -= 1
        elif code_movement == 9:
            pass


class WolfGirl(Animal):
    def __init__(self, x: int, y: int) -> None:
        super().__init__(x=x, y=y)
        self.all_wolfgirl.append(self)

        self.follow_rabbit = False
        self.followed_rabbit = None

        self.name = 'wolf Girl'

    def tick(self) -> None:

        if self.follow_rabbit:
            if self.followed_rabbit not in self.all_rabbits:
                self.follow_rabbit = False
                self.followed_rabbit = None

        self.search_rabbit()

        if self.follow_rabbit:
            if self.x < self.followed_rabbit.x:
                self.x += 1
            elif self.x > self.followed_rabbit.x:
                self.x -= 1

            if self.y < self.followed_rabbit.y:
                self.y += 1
            elif self.y > self.followed_rabbit.y:
                self.y -= 1

            if self.x == self.followed_rabbit.x and self.y == self.followed_rabbit.y:
                try:
                    Animal.all_animals.remove(self.followed_rabbit)
                except ValueError:
                    pass
                self.life_points += 1
                self.follow_rabbit = False
                self.followed_rabbit = None
            else:
                self.life_points -= 0.1

                if self.life_points == 0:
                    Animal.all_animals.remove(self)
        else:
            self.move()

    def search_rabbit(self):
        if not self.follow_rabbit:

            for rabbit in Animal.all_rabbits:
                if not self.follow_rabbit and math.sqrt(((self.x - rabbit.x) ** 2) + ((self.y - rabbit.y) ** 2)) < 2:
                    self.follow_rabbit = True
                    self.followed_rabbit = rabbit


class WolfMan(Animal):
    def __init__(self, x, y):
        super().__init__(x=x, y=y)
        self.all_wolfman.append(self)

        self.follow_rabbit = False
        self.follow_wolfgirl = False

        self.followed_rabbit = None
        self.followed_wolfgirl = None

        self.name = 'wolf MAN'

    def tick(self) -> None:
        if self.follow_rabbit:
            if self.followed_rabbit not in self.all_rabbits:
                self.follow_rabbit = False
                self.followed_rabbit = None

        self.search_rabbit()

        if self.follow_rabbit:
            if self.x < self.followed_rabbit.x:
                self.x += 1
            elif self.x > self.followed_rabbit.x:
                self.x -= 1

            if self.y < self.followed_rabbit.y:
                self.y += 1
            elif self.y > self.followed_rabbit.y:
                self.y -= 1

            if self.x == self.followed_rabbit.x and self.y == self.followed_rabbit.y:
                Animal.all_rabbits.remove(self.followed_rabbit)

                self.life_points += 1
                self.follow_rabbit = False
                self.followed_rabbit = None
            else:
                self.life_points -= 0.1

                if self.life_points == 0:
                    Animal.all_animals.remove(self)

        elif not self.follow_rabbit:
            self.search_wolfgirls()

        if self.follow_wolfgirl:
            if self.x < self.followed_wolfgirl.x:
                self.x += 1
            elif self.x > self.followed_wolfgirl.x:
                self.x -= 1

            if self.y < self.followed_wolfgirl.y:
                self.y += 1
            elif self.y > self.followed_wolfgirl.y:
                self.y -= 1

            if self.x == self.followed_wolfgirl.x and self.y == self.followed_wolfgirl.y:
                sex = random.randint(0, 1)
                if sex == 0:
                    Animal.all_wolfgirl.append(WolfGirl(((self.x + 10) % 20) + 1, ((self.y + 15) % 20) + 1))
                elif sex == 1:
                    Animal.all_wolfman.append(WolfMan(((self.x + 10) % 20) + 1, ((self.y + 15) % 20) + 1))

                self.follow_wolfgirl = False
                self.followed_wolfgirl = None

        else:
            self.move()

    def search_rabbit(self):
        if not self.follow_rabbit:

            for rabbit in Animal.all_rabbits:
                if not self.follow_rabbit and math.sqrt(((self.x - rabbit.x) ** 2) + ((self.y - rabbit.y) ** 2)) < 2:
                    self.follow_rabbit = True
                    self.followed_rabbit = rabbit

    def search_wolfgirls(self):
        if not self.follow_wolfgirl:
            for wolfgirl in Animal.all_wolfgirl:

                if not self.follow_wolfgirl and \
                        math.sqrt(((self.x - wolfgirl.x) ** 2) + ((self.y - wolfgirl.y) ** 2)) < 2:
                    self.follow_wolfgirl = True
                    self.followed_wolfgirl = wolfgirl


class Rabbit(Animal):
    def __init__(self, x, y):
        super().__init__(x=x, y=y)

        self.all_rabbits.append(self)
        self.name = 'Rabbit'

    def tick(self) -> None:
        self.try_create_new_rab()
        self.move()

    def try_create_new_rab(self) -> None:
        code = random.randint(1, 10)
        if code == 1:
            Animal.all_rabbits.append(Rabbit(self.x, self.y))


def run_main():
    Rabbit(1, 1)

    WolfGirl(20, 20)
    WolfMan(15, 15)

    while len(Animal.all_rabbits) != 0:
        for animal in Animal.all_animals:
            animal.tick()


if __name__ == '__main__':
    run_main()
