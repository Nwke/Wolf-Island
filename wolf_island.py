from .animal import Rabbit, WolfGirl, WolfMan, Animal


def run_main():
    Rabbit(1, 1)

    WolfGirl(20, 20)
    WolfMan(15, 15)

    while len(Animal.all_rabbits) != 0:
        for animal in Animal.all_animals:
            animal.tick()


if __name__ == '__main__':
    run_main()
