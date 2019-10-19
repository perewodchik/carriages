#include "functions.h"

void ReadAnimals(Animal** animals, int *animalAmount){
        FILE* animalInput = fopen("animals.txt", "r");
        if(animalInput == NULL){
                printf("Could not open file animals.txt");
                exit(1);
        }
        fscanf(animalInput, "%d\n", animalAmount);
        *animals = (Animal*)malloc(*animalAmount * sizeof(Animal));
        int i,j;
        for(i = 0; i < *animalAmount; i++)
                fscanf(animalInput, "name=%s\nid=%d\nsize=%d\n",
                &(*animals)[i].name, &(*animals)[i].id, &(*animals)[i].size);
        fclose(animalInput);
}

void ReadHumans(Human** humans, int* humanAmount){
        FILE* humanInput = fopen("humans.txt", "r");
        if(humanInput == NULL){
                printf("Could not open file humans.txt");
                exit(1);
        }
        fscanf(humanInput, "%d\n", humanAmount);
        *humans = (Human*)malloc(*humanAmount * sizeof(Human));
        int i,j;
        for(i = 0; i < *humanAmount; i++){
                fscanf(humanInput, "name=%s\nid=%d\nsize=%d\nanimals=%d\n",
                &((*humans)[i].name), &((*humans)[i].id),
                &((*humans)[i].size), &((*humans)[i].animalsAmount));
                (*humans)[i].animalIDs = (int*)malloc((*humans)[i].animalsAmount*sizeof(int));
                for(j = 0; j < (*humans)[i].animalsAmount; j++)
                        fscanf(humanInput, "%d ", &((*humans)[i].animalIDs[j]));
                fscanf(humanInput, "\n");
        }
        fclose(humanInput);
}

void ReadCarriages(Carriage** carriages, int* carriageAmount, int* capacity){
        int i;
        FILE* input = fopen("carriages.txt", "r");
        if(input == NULL){
                printf("Could not open carriages.txt");
                exit(1);
        }
        fscanf(input, "%d %d", carriageAmount, capacity);
        *carriages = (Carriage*)malloc(*carriageAmount * sizeof(Carriage));
        for(i = 0; i < *carriageAmount; i++)
                fscanf(input, "%d", &((*carriages)[i].type));
        fclose(input);
}

void PrintHumans(Human* humans, int humanAmount){
        int i,j;
        FILE* output = fopen("output.txt", "a");
        for(i = 0; i < humanAmount; i++){
                fprintf(output,"Human number: %d, Name: %s, ID: %d\n", i, humans[i].name, humans[i].id);
                if(humans[i].animalsAmount == 0){
                        fprintf(output,"This human has no animals\n");
                        continue;
                }
                fprintf(output,"+--------------------+----+------+\n");
                fprintf(output,"|        NAME        | ID |SIZE  |\n");
                fprintf(output,"+--------------------+----+------+\n");
                for(j = 0; j < humans[i].animalsAmount; j++){
                        fprintf(output,"|%-20s|%-4d|%-6d|\n",
                        (*(humans[i].animals[j])).name,
                        (*(humans[i].animals[j])).id,
                        (*(humans[i].animals[j])).size);
                }
                fprintf(output,"+--------------------+----+------+\n");
        }
        fclose(output);
}

void PrintCarriages(Carriage* carriages, int carriageAmount, int capacity){
        int i,j;
        FILE* output = fopen("output.txt", "a");
        for(i = 0; i < carriageAmount; i++){
                fprintf(output,"Carriage number: %d\n", i+1);
                if(carriages[i].amount == 0){
                        fprintf(output,"There are no passengers\n");
                        continue;
                }
                fprintf(output,"+--------------------+----+------+\n");
                fprintf(output,"|        NAME        | ID | SIZE |\n");
                fprintf(output,"+--------------------+----+------+\n");
                        for(j = 0; j < carriages[i].amount; j++)
                                if(carriages[i].type == HUMAN)
                                        fprintf(output,"|%-20s|%-4d|%-6d|\n",
                                        (*(carriages[i].humans[j])).name,
                                        (*(carriages[i].humans[j])).id,
                                        (*(carriages[i].humans[j])).size);
                                else
                                        fprintf(output,"|%-20s|%-4d|%-6d|\n",
                                        (*(carriages[i].animals[j])).name,
                                        (*(carriages[i].animals[j])).id,
                                        (*(carriages[i].animals[j])).size);
                fprintf(output,"+--------------------+----+------+\n");
        }
        fclose(output);
}

void SortHumansBySize(Human* humans, int humanAmount){
        int i,j;
        for(i = humanAmount-1; i > 0; i--)
                for(j = 0; j < i; j++)
                        if(humans[j].size > humans[i].size){
                                Human tmp = humans[j];
                                humans[j] = humans[i];
                                humans[i] = tmp;
                        }
}

void SortAnimalsBySize(Animal* animals, int animalAmount){
        int i,j;
        for(i = animalAmount-1; i > 0; i--)
                for(j = 0; j < i; j++)
                        if(animals[j].size > animals[i].size){
                                Animal tmp = animals[j];
                                animals[j] = animals[i];
                                animals[i] = tmp;
                        }
}

void AllocateCarriages(Carriage** carriages, int carriageAmount, int capacity,
Animal* animals, int animalAmount, Human* humans, int humanAmount){
        int i;
        int animalPtr = 0;
        for(i = 0; i < carriageAmount; i++){
                if((*carriages)[i].type != ANIMAL)
                        continue;
                (*carriages)[i].animals = (Animal**)malloc(1 * sizeof(Animal*));
                (*carriages)[i].amount = 0;
                (*carriages)[i].size = 0;
                while(animalPtr < animalAmount
                && ((*carriages)[i].size + animals[animalPtr].size) < capacity){
                        if((*carriages)[i].amount >= 1)
                                (*carriages)[i].animals = (Animal**)realloc(
                                (*carriages)[i].animals,
                                ((*carriages)[i].amount + 1) * sizeof(Animal*));
                        (*carriages)[i].size += animals[animalPtr].size;
                        (*carriages)[i].animals[(*carriages)[i].amount] = &(animals[animalPtr]);
                        (*carriages)[i].amount++;
                        animalPtr++;
                }
        }
        int humanPtr = 0;
        for(i = 0; i < carriageAmount; i++){
                if((*carriages)[i].type != HUMAN)
                        continue;
                (*carriages)[i].humans = (Human**)malloc(1 * sizeof(Human*));
                (*carriages)[i].amount = 0;
                (*carriages)[i].size = 0;
                while(humanPtr < humanAmount
                && ((*carriages)[i].size + humans[humanPtr].size) < capacity){
                        if((*carriages)[i].amount >= 1)
                                (*carriages)[i].humans = (Human**)realloc(
                                (*carriages)[i].humans,
                                ((*carriages)[i].amount + 1) * sizeof(Human*));
                        (*carriages)[i].size += humans[humanPtr].size;
                        (*carriages)[i].humans[(*carriages)[i].amount] = &(humans[humanPtr]);
                        (*carriages)[i].amount++;
                        humanPtr++;
                }
        }
}

void MatchAnimals(Human** humans, int humanAmount, Animal* animals, int animalAmount){
        int i,j,k;
        int currentAnimals = 0;
        for(i = 0; i < humanAmount; i++){
                (*humans)[i].animals = (Animal**)malloc( 1 * sizeof(Animal*));
                for(j = 0; j < (*humans)[i].animalsAmount; j++){
                        for(k = 0; k < animalAmount; k++){
                                if((*humans)[i].animalIDs[j] == animals[k].id){
                                        if(currentAnimals >= 1)
                                                (*humans)[i].animals = (Animal**)realloc(
                                                (*humans)[i].animals, (currentAnimals + 1)*sizeof(Animal*));
                                        (*humans)[i].animals[j] = &animals[k];
                                        currentAnimals++;
                                        break;
                                }
                        }
                }
        }
}

void FreeAll(Human* humans, int humanAmount, Animal* animals, int animalAmount,
                Carriage* carriages, int carriageAmount){
        int i,j;
        for(i = 0; i < humanAmount; i++){
                free(humans[i].animals);
                free(humans[i].animalIDs);
        }
        for(i = 0; i < carriageAmount; i++)
                if(carriages[i].type == HUMAN)
                        free(carriages[i].humans);
                else
                        free(carriages[i].animals);
        free(carriages);
        free(humans);
        free(animals);
}
