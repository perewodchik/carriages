#ifndef CARRIAGES
        #define CARRIAGES
        #include <stdio.h>
        #include <stdlib.h>
        enum CARRIAGE {ANIMAL = 0, HUMAN = 1};
        typedef struct {
                char name[21];
                int id;
                int size;
        } Animal;
        typedef struct {
                char name[21];
                int id;
                int size;
                int animalsAmount;
                int* animalIDs;
                Animal** animals;
        } Human;
        typedef struct {
                int type;
                int amount;
                int size;
                union{
                        Animal** animals;
                        Human** humans;
                };
        } Carriage;
#endif
