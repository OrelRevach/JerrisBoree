//
// Created by orelpc on 11/13/20.
//
#include "Jerry.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Defs.h"
#include "math.h"
#define FALIURE -1
#define MAGICNUM 9858462


Jerry *createJerry(char *Name, int joy, Origin *ori) {
    Jerry *Jer;
    if (Name == NULL || ori == NULL) {
        return NULL;
    }
    Jer = (Jerry *) malloc(sizeof(Jerry));
    if (Jer == NULL) {
        return NULL;
    }
    Jer->ID = (char *) malloc(strlen(Name) + 1);
    if (Jer->ID == NULL) {
        free(Jer);
        return NULL;
    }
    strcpy(Jer->ID, Name);
    Jer->jerryJoy = joy;
    Jer->jerTrait = NULL;
    Jer->numOfTrant = 0;
    Jer->born = ori;
    Jer->magicNum = MAGICNUM;
    return Jer;
}

Planet *createPlanet(char *Name, double x, double y, double z) {
    Planet *Pla;
    if (Name == NULL) {
        return NULL;
    }
    Pla = (Planet *) malloc(sizeof(Planet));
    if (Pla == NULL) {
        return NULL;
    }
    Pla->plaName = (char *) malloc(strlen(Name) + 1);
    if (Pla->plaName == NULL) {
        free(Pla);
        return NULL;
    }
    strcpy(Pla->plaName, Name);
    Pla->x = x;
    Pla->y = y;
    Pla->z = z;
    Pla->magicNum = MAGICNUM;
    return Pla;
}

Trait *createTrait(char *Name, double Value) {
    Trait *Tran;
    if (Name == NULL) {
        return NULL;
    }
    Tran = (Trait *) malloc(sizeof(Trait));
    if (Tran == NULL) {
        return NULL;
    }
    Tran->traitName = (char *) malloc(strlen(Name) + 1);
    if (Tran->traitName == NULL) {
        free(Tran);
        return NULL;
    }
    strcpy(Tran->traitName, Name);
    Tran->value = Value;
    Tran->magicNum = MAGICNUM;
    return Tran;
}

Origin *createOrigin(char *Name, Planet *plan) {
    Origin *org;
    if (Name == NULL) {
        return NULL;
    }
    org = (Origin *) malloc(sizeof(Origin));
    if (org == NULL) {
        return NULL;
    }
    org->oriName = (char *) malloc(strlen(Name) + 1);
    if (org->oriName == NULL) {
        free(org);
        return NULL;
    }
    strcpy(org->oriName, Name);
    org->origPlanet = plan;
    org->magicNum = MAGICNUM;
    return org;
}


enum e_status isTraitExistByName(Jerry *jer, char *name) {
    if (jer == NULL || name == NULL) {
        return failure;
    }
    for (int i = 0; i < jer->numOfTrant; i++) {
        if (strcmp(jer->jerTrait[i]->traitName, name) == 0) {
            return success;
        }
    }
    return failure;
}

enum e_status isJerryInPlanet(Jerry *jer, char *pName) {
    if (jer == NULL || pName == NULL) {
        return failure;
    }
    if (strcmp(jer->born->origPlanet->plaName, pName) == 0) {
        return success;
    }
    return failure;
}

enum e_status addTraitToJerry(Jerry *jer, Trait *tran) {
    if (jer == NULL || tran->traitName == NULL) {
        return failure;
    } else {
        if (jer->jerTrait == NULL && jer->numOfTrant == 0) {
            jer->jerTrait = (Trait **) malloc(sizeof(Trait *));
        } else {
            Trait **temp;
            temp = jer->jerTrait;
            jer->jerTrait = realloc(jer->jerTrait, sizeof(Trait) * jer->numOfTrant + 1);
            if (jer->jerTrait == NULL) {
                jer->jerTrait = temp;
                return failure;
            }
        }
        jer->jerTrait[jer->numOfTrant] = tran;
        jer->numOfTrant++;
        return success;
    }
}

enum e_status rmTraitFromJerry(Jerry *jer, char *name) {
    if (jer == NULL || name == NULL) {
        return failure;
    }
    if (jer->numOfTrant == 1) {
        destroyTrait(jer->jerTrait[0]);
        //free(jer->jerTrait);
        free(jer->jerTrait);
        jer->jerTrait = NULL;
        jer->numOfTrant--;
        return success;
    }
    int index;
    for (int i = 0; i < jer->numOfTrant; i++) {
        if (strcmp(jer->jerTrait[i]->traitName, name) == 0) {
            index = i;
        }
    }
    Trait **newTraits = (Trait **) malloc(sizeof(Trait) * jer->numOfTrant - 1);
    if (newTraits == NULL) {
        return failure;
    }
    for (int i = 0; i < jer->numOfTrant; i++) {
        if (i == index) {
            continue;
        }
        if (i < index) {
            newTraits[i] = jer->jerTrait[i];
        }
        if (i > index) {
            newTraits[i - 1] = jer->jerTrait[i];
        }
    }
    free(jer->jerTrait[index]);
    free(jer->jerTrait);
    jer->numOfTrant--;
    jer->jerTrait = newTraits;
}


enum e_status printPlanet(Planet *pl) {
    if (pl == NULL) {
        return failure;
    }
    printf("Planet : %s (%.2f,%.2f,%.2f) \n", pl->plaName, pl->x, pl->y, pl->z);
    return success;
}

enum e_status printJerry(Jerry *jer) {
    printf("Jerry , ID - %s : \n", jer->ID);
    printf("Happiness level : %d \n", jer->jerryJoy);
    printf("Origin : %s \n", (jer->born->oriName));
    printPlanet(jer->born->origPlanet);
    if (jer->jerTrait == NULL && jer->numOfTrant == 0) {
        return failure;
    }
    for (int i = 0; i < jer->numOfTrant; i++) {
        if (i == 0) {
            printf("Jerry's physical Characteristics available : \n");
            printf("\t");
        }
        if (i == jer->numOfTrant - 1) {
            printf("%s : %.2f \n", jer->jerTrait[i]->traitName, jer->jerTrait[i]->value);
            return success;
        }
        printf("%s : %.2f , ", jer->jerTrait[i]->traitName, jer->jerTrait[i]->value);

    }

}

void updateJoy(Jerry *jer, int newJoy) {
    if (newJoy > 100) {
        jer->jerryJoy = 100;
    } else if (newJoy < 0) {
        jer->jerryJoy = 0;
    } else {
        jer->jerryJoy = newJoy;
    }
    return;
}

void destroyJerry(Jerry *jer) {
    if (jer == NULL) {
        return;
    }
    if (jer->magicNum == MAGICNUM) {
        jer->magicNum = 0;
        if (jer->jerTrait != NULL) {
            for (int i = jer->numOfTrant - 1; i >= 0; i--) {
                if (jer->jerTrait[i] != NULL) {
                    destroyTrait(jer->jerTrait[i]);
                }
            }
            free(jer->jerTrait);
        }

        if (jer->born != NULL) {
            destroyOrigin(jer->born);
        }
        free(jer->ID);
        free(jer);
    }
}

void destroyOrigin(Origin *ori) {
    if (ori == NULL || ori->magicNum != MAGICNUM) {
        return;
    }
    ori->magicNum = 0;
    free(ori->oriName);
    free(ori);
}

void destroyTrait(Trait *tr) {
    if (tr == NULL) {
        return;
    }
    if (tr->magicNum == MAGICNUM) {
        tr->magicNum = 0;
        free(tr->traitName);
        free(tr);
    }
}

void destroyPlanet(Planet *pl) {
    if (pl->magicNum != MAGICNUM || pl == NULL) {
        return;
    }
    pl->magicNum = 0;
    free(pl->plaName);
    free(pl);
}


int TransformKeyIntoNumberKey(Element key) {
    char *hash = (char *) key;
    int sum = 0, i, len;
    len = strlen(hash);
    for (i = 0; i < len; i++)
        sum = sum + hash[i];
    return sum;
}

status printKeyJerName(Element elem) {
    char *JerName = (char *) elem;
    char *ans = (char *) malloc(sizeof(char) * strlen(JerName) + 1);
    if (ans == NULL)
        return failure;
    strcpy(ans, JerName);
    printf("%s", ans);
    free(ans);
    return success;
}

status printValueJerry(Element elem) {

    Jerry *jer = (Jerry *) elem;
    if (jer == NULL)
        return failure;
    printJerry(jer);
    return success;
}

Element copyKeyJer(Element elem) {
    char *JerName = (char *) elem;
    char *ans = (char *) malloc(strlen(JerName) + 1);
    if (ans == NULL)
        return NULL;
    strcpy(ans, JerName);
    return (Element) ans;
}

Element copyValueJerry(Element elem) {
    Jerry *jer = (Jerry *) elem;
    Jerry *ans;
    ans = jer;
    if (ans == NULL) {
        return NULL;
    }
    return (Element) ans;
}

status freeKeyJer(Element elem) {
    char *Jername = (char *) elem;
    free(Jername);
    return success;
}

status freeValueJerry(Element elem) {
    Jerry *jer = (Jerry *) elem;
    if (jer == NULL)
        return failure;
    destroyJerry(jer);
    return success;
}

enum e_bool EqualKeyJer(Element elem1, Element elem2) {//reciving jerry->JerryID
    if (elem1 == NULL || elem2 == NULL) {
        return false;
    }
    char *key1 = (char *) elem1;
    char *key2 = (char *) elem2;
//
//    char ans2[strlen(key2) + 1];
//    strcpy(ans2, key2);
    if (strcmp(key2, key1) == 0) {
        return true;
    }
    return false;
}

double geTraitFromJer(Jerry *Jer, char *traitName) {
    if (Jer == NULL) {
        return FALIURE;
    }
    for (int i = 0; i < Jer->numOfTrant; i++) {
        if (strcmp(Jer->jerTrait[i]->traitName, traitName) == 0) {
            return Jer->jerTrait[i]->value;
        }

    }

}



Element copyKeyTrait(Element elem) {
    char *traitName = (char *) elem;
    char *ans = (char *) malloc(strlen(traitName) + 1);
    if (ans == NULL)
        return NULL;
    strcpy(ans, traitName);
    return (Element) ans;
}

status freeKeyTrait(Element elem) {
    char *traitName = (char *) elem;
    free(traitName);
    return success;
}

status printKeyTrait(Element elem) {
    char *traitName = (char *) elem;
    if (traitName == NULL) {
        return failure;
    }
    printf("%s : \n", traitName);
    return success;
}

int getJoy(Jerry *Jer) {
    if (Jer == NULL) {
        return 101;
    }
    return Jer->jerryJoy;
}

enum e_bool EqualKeyTrait(Element elem1, Element elem2) {//reciving jerry->JerryID
    if (elem1 == NULL || elem2 == NULL) {
        return JoyFailure;
    }
    char *key1 = (char *) elem1;
    char *key2 = (char *) elem2;
//    char ans2[strlen(key2) + 1];
//    strcpy(ans2, key2);
    if (strcmp(key2, key1) == 0) {
        return true;
    }
    return false;
}