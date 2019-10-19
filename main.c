#include "functions.h"
int main(){
        int animalAmount,
            humanAmount,
            carriageAmount,
            capacity;
        Animal* animals;
        Human* humans;
        Carriage* carriages;
        ReadAnimals(&animals, &animalAmount);
        ReadHumans(&humans, &humanAmount);
        MatchAnimals(&humans, humanAmount, animals, animalAmount);
        ReadCarriages(&carriages, &carriageAmount, &capacity);
        SortAnimalsBySize(animals, animalAmount);
        SortHumansBySize(humans, humanAmount);
        AllocateCarriages(&carriages, carriageAmount, capacity,
                animals, animalAmount, humans, humanAmount);
        PrintCarriages(carriages, carriageAmount, capacity);
        PrintHumans(humans, humanAmount);
        FreeAll(humans,humanAmount, animals, animalAmount,
                carriages, carriageAmount);
        return 0;
}