#ifndef FUNCTIONS
        #define FUNCTIONS
        #include <string.h>
        #include "structure.h"
        void ReadAnimals(Animal** animals, int* animalAmount);
        void ReadHumans(Human** humans, int* humanAmount);
        void ReadCarriages(Carriage** carriages, int* carriageAmount, int* capacity);
        void PrintHumans(Human* humans, int humanAmount);
        void PrintCarriages(Carriage* carriages, int carriageAmount, int capacity);
        void SortHumansBySize(Human* humans, int humanAmount);
        void SortAnimalsBySize(Animal* animals, int animalAmount);
        void AllocateCarriages(Carriage** carriages, int carriageAmount, int capacity,
                Animal* animals, int animalAmount, Human* humans, int humanAmount);
        void MatchAnimals(Human** humans, int humanAmount, Animal* animals, int animalAmount);
        void FreeAll(Human* humans, int humanAmount, Animal* animals, int animalAmount,
                Carriage* carriages, int carriageAmount);
#endif
