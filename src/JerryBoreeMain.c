
#include <stdio.h>
#include <string.h>
#include "Jerry.h"
#include <stdlib.h>
#include "HashTable.h"
#include "MultiValueHashTable.h"
#include "KeyValuePair.h"
#include "LinkedList.h"
#include "Defs.h"
#include "math.h"


float CountJerryAndTrait(char *filename, float *numOfTrait) {
    int countJer = 0;
    char *jer = "Jerries";
    FILE *file;
    char line[100];
    file = fopen(filename, "r");
    fgets(line, 100, file);
    while (strcmp(line, jer) != 0) {
        fgets(line, 100, file);
        line[7] = '\0';
    }

    while (!feof(file)) {
        fgets(line, 100, file);
        if (line[0] != '\t') {
            countJer++;

        } else {
            *numOfTrait += 1;
        }

    }
    fclose(file);
    return countJer;
}


int closestPrimeNumber(int n) {
    int a, b, flag = 0;
    for (a = n + 1; a <= n + 100; a++) {
        flag = 0;
        for (b = 2; b < a; b++) {
            if (a % b == 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            return a;
        }
    }
}

static Jerry **creatPlaceForJerry(int numOfJer, Jerry **JerrysArr) {//no need for static

    if (JerrysArr == NULL || numOfJer == 1) {
        Jerry **jer;
        jer = (Jerry **) malloc(numOfJer * sizeof(Jerry *));
        if (jer == NULL) {
            return NULL;
        }
        return jer;
    }
    Jerry **temp;
    temp = (Jerry **) realloc(JerrysArr, numOfJer * sizeof(Jerry *));
    if (temp == NULL) {

        return JerrysArr;
    }
    return temp;
}

Planet *findPlanet(Planet **allPlanets, char *pName, int num) {
    if (allPlanets == NULL || pName == NULL) {
        return NULL;
    }
    for (int i = 0; i < num; i++) {
        if (allPlanets[i] == NULL) {
            return NULL;
        }
        if (strcmp(allPlanets[i]->plaName, pName) == 0) {
            return allPlanets[i];
        }
    }
    return NULL;
}

int findJerry(Jerry **allJerries, char *pName, int num) {
    if (allJerries == NULL || pName == NULL) {
        return -1;
    }
    for (int i = 0; i < num; i++) {
        if (allJerries[i] == NULL) {
            return -1;
        }
        if (strcmp(allJerries[i]->ID, pName) == 0) {
            return i;
        }
    }
    return -1;
}

Jerry **removeJerry(Jerry **JerrysArr, Jerry *jer, int numOfjer) {
    if (JerrysArr == NULL || jer == NULL) {
        return NULL;
    }
    if (numOfjer == 1) {
        destroyJerry(JerrysArr[0]);
        free(JerrysArr);
        return NULL;
    }
    int index = findJerry(JerrysArr, jer->ID, numOfjer);
    if (index == -1) {
        return NULL;
    }
    Jerry **newArr = (Jerry **) malloc(sizeof(Jerry *) * numOfjer - 1);
    if (newArr == NULL) {
        return NULL;
    }
    for (int i = 0; i < numOfjer; i++) {
        if (i == index) {
            continue;
        }
        if (i < index) {
            newArr[i] = JerrysArr[i];
        }
        if (i > index) {
            newArr[i - 1] = JerrysArr[i];
        }
    }
    destroyJerry(JerrysArr[index]);
    free(JerrysArr);
    return newArr;
}

static int
closeProgram(int numOfJerrys, Planet *Planarr[], int numOfPlanets, hashTable myHash, MultiValueHashTable htMulti) {
    if (Planarr != NULL) {

        for (int Index = numOfPlanets - 1; Index >= 0; Index--) {
            destroyPlanet(Planarr[Index]);
        }
    }
    list remove = lookupInMultiValueHashTable(htMulti, "jerryJoy");
    int size = getLengthList(remove);

    destroyHashTable(myHash);
    destroyMultiValueHashTable(htMulti);

}


void static
removeJerryFromSystem(hashTable htJerries, MultiValueHashTable htTraits, Jerry *returnJer, Jerry **JerrysArr,
                      int numOfJerrys) {
    list TempTairlist;
    for (int TraitIndex = 0; TraitIndex < returnJer->numOfTrant; TraitIndex++) {

        list TempTairlist = lookupInMultiValueHashTable(htTraits, returnJer->jerTrait[TraitIndex]->traitName);
        deleteNode(TempTairlist, returnJer);
    }
    // if system have that jerry, delete it.
    removeFromHashTable(htJerries, returnJer->ID);


}

int main(int argc, char *argv[]) {
    char *word;
    char line[300];
    char *tempstring;
    char token[5] = ",\r\n\t:";
    int numOfPlanets, numOfJerrys = 0, hashSizeJer, hashSizeTrait;
    float numOfJer = 0, numOfTrait = 0;
    char *jerryJoy = (char *) malloc(9);
    strcpy(jerryJoy, "jerryJoy");
    numOfJer = CountJerryAndTrait(argv[2], &numOfTrait);
    numOfPlanets = atoi(argv[1]);
    Planet *Planarr[numOfPlanets];

    numOfJerrys = numOfJer;
    numOfJer *= 1.3;
    numOfTrait *= 1.3;
    numOfTrait = (numOfTrait / numOfJerrys) * numOfJer;
    hashSizeJer = closestPrimeNumber((int) numOfJer);
    hashSizeTrait = closestPrimeNumber((int) numOfTrait);
    numOfJerrys = 0;

    FILE *fp;
    fp = fopen(argv[2], "r");
    if (fp == NULL) {
        printf("Could not open File ");
        return 0;
    }

    hashTable htJerries = createHashTable(copyKeyJer, freeKeyJer, printKeyJerName, copyValueJerry, freeValueJerry,
                                          printValueJerry, EqualKeyJer, TransformKeyIntoNumberKey, hashSizeJer);
    MultiValueHashTable htTraits = createMultiValueHashTable(copyKeyTrait, freeKeyTrait, printKeyTrait, destroyList,
                                                             destroyJerry, printValueJerry, EqualKeyTrait,
                                                             TransformKeyIntoNumberKey, hashSizeTrait);
    //Read Plantes From FILE
    char name[15];
    double x, y, z;
    fgets(line, 300, fp);
    while (!feof(fp)) {
        for (int i = 0; i < numOfPlanets; i++) {/// num of lines
            fgets(line, 300, fp);
            word = strtok(line, ",");
            for (int j = 0; j < 4; j++) {
                switch (j) {
                    case 0 :
                        strcpy(name, word);
                        word = strtok(NULL, token);
                        break;
                    case 1:
                        x = atof(word);
//                    x = strtod(word, tempstring);
                        word = strtok(NULL, token);
                        break;
                    case 2:
                        y = atof(word);
//                    y = strtod(word, tempstring);
                        word = strtok(NULL, token);
                        break;
                    case 3:
                        z = atof(word);
//                  z = strtod(word, tempstring);
                        word = strtok(NULL, token);
                        break;
                }
            }
            Planarr[i] = createPlanet(name, x, y, z);
        }
        /*discard the Jerries Line*/
        fgets(line, 300, fp);

        /* secound Part Of reading File */
        char *keyHash;
        Jerry *Jer;
        Trait *tra;
        Origin *ori;
        Planet *planet;
        int joy;
        double traitValue;
        char oriName[15];
        char TraitName[15];
        char planName[15];
        int i = 0;
        while (fgets(line, sizeof(line), fp)) {/* num of Jerries -- check if fp&&(!feof(fp)) NEEDED */
            if (line[0] != '\t') {
                numOfJerrys++;
                word = strtok(line, ",");
                for (int j = 0; j < 4; j++) {
                    switch (j) {
                        case 0 :
                            strcpy(name, word);
                            word = strtok(NULL, ",");
                            break;
                        case 1:

                            strcpy(oriName, word);
                            word = strtok(NULL, token);
                            break;
                        case 2:
                            strcpy(planName, word);
                            word = strtok(NULL, "j");
                            break;
                        case 3:
                            joy = atoi(word);
                            word = strtok(NULL, token);
                            break;
                    }
                }
                planet = findPlanet(Planarr, planName, numOfPlanets);
                ori = createOrigin(oriName, planet);
                Jer = createJerry(name, joy, ori);
                addToMultiValueHashTable(htTraits, jerryJoy, Jer);
                addToHashTable(htJerries, Jer->ID, Jer);
                i++;
            } else {/// read Trait From FILE
                for (int j = 0; j < 2; j++) {
                    if (j == 0) {
                        word = strtok(line, "\t");
                        word = strtok(word, ":");
                    }
                    switch (j) {
                        case 0 :
                            strcpy(TraitName, word);
                            word = strtok(NULL, ",\n");
                            break;
                        case 1:
                            traitValue = strtod(word, &tempstring);
                            word = strtok(NULL, token);
                            break;
                    }
                }
                tra = createTrait(TraitName, traitValue);
                addToMultiValueHashTable(htTraits, tra->traitName, Jer);
                addTraitToJerry(Jer, tra);
            }
        }

    }

    fclose(fp);

    char ch = '1';
    char planetName[20];
    char jerryDimension[20];
    char TraitName[20];
    double traitValue;
    int happiness;
    Jerry *temp;


    char tempRecive[30];
    char tempRecive1[30];
    while (ch != '0') {
        printf("Welcome Rick, what are your Jerry's needs today ? \n");
        printf("1 : Take this Jerry away from me \n");
        printf("2 : I think I remember something about my Jerry \n");
        printf("3 : Oh wait. That can't be right \n");
        printf("4 : I guess I will take back my Jerry now \n");
        printf("5 : I can't find my Jerry. Just give me a similar one \n");
        printf("6 : I lost a bet. Give me your saddest Jerry \n");
        printf("7 : Show me what you got \n");
        printf("8 : Let the Jerries play \n");
        printf("9 : I had enough. Close this place \n");

        scanf(" %s", &tempRecive);
        if (tempRecive[1] != '\0')
            ch = 'A';

        else {
            ch = tempRecive[0];
        }
        switch (ch) {
            //add jerry
            case '1':

                printf("What is your Jerry's ID ? \n");
                char jerryID[20];
                scanf("%s", jerryID);
                // if jerry is in system (search for jerry in hash table in O(1))
                temp = lookupInHashTable(htJerries, (Element) jerryID);
                if (temp != NULL) {
                    printf("Rick did you forgot ? you already left him here ! \n");
                    break;
                }
                // if jerry NOT in system(else)
                printf("What planet is your Jerry from ? \n");
                scanf("%s", planetName);
                Planet *tempPlanet = findPlanet(Planarr, planetName, numOfPlanets);
                if (tempPlanet == NULL) {
                    // if planet is NOT in system
                    printf("%s is not a known planet ! \n", planetName);
                    break;
                }
                //if is in system (else)
                printf("What is your Jerry's dimension ? \n");
                scanf("%s", jerryDimension);
                //create new dimension (Origin)
                Origin *origin = createOrigin(jerryDimension, tempPlanet);
                if (origin == NULL)
                    break;
                printf("How happy is your Jerry now ? \n");
                scanf("%d", &happiness);
                //create new Jerry
                temp = createJerry(jerryID, happiness, origin);
                if (temp == NULL) {
                    break;
                }
                //add new jerry to system (jerry id , jer*)
                if (addToHashTable(htJerries, jerryID, temp) == failure)
                    //do somthing
                    break;
                addToMultiValueHashTable(htTraits, jerryJoy, temp);
                numOfJerrys++;
                printJerry(temp);
                //print new jerry
                break;

                //add Trait to jerry
            case '2':
                printf("What is your Jerry's ID ? \n");
                char Jid[20];
                scanf("%s", Jid);
                // if jerry is NOT in system
                Jerry *tempJer;
                tempJer = lookupInHashTable(htJerries, (Element) Jid);
                if (tempJer == NULL) {
                    printf("Rick this Jerry is not in the daycare ! \n");
                    break;
                }
                //else, if jerry IS IN System
                printf("What physical characteristic can you add to Jerry - %s ? \n", Jid);
                scanf("%s", TraitName);
                // check if jerry already has this Trait, if he has trait, print
                if (isTraitExistByName(tempJer, TraitName) == success) {
                    printf("The information about his %s already available to the daycare ! \n", TraitName);
                    break;
                }
                // if he didnt have that trait name.
                printf("What is the value of his %s ? \n", TraitName);
                scanf("%lf", &traitValue);
                Trait *tempTrait = createTrait(TraitName, traitValue);
                // add trait to jerry
                addToMultiValueHashTable(htTraits, tempTrait->traitName, tempJer);
                addTraitToJerry(tempJer, tempTrait);
                printf("%s : \n", TraitName);
                list tempList = lookupInMultiValueHashTable(htTraits, TraitName);
                displayList(tempList);
                //print all jerry that have this trait (hashtable)
                //TraitName :
                // jerry 1
                //jerry 2
                break;

                //remove trait from jerry
            case '3':
                printf("What is your Jerry's ID ? \n");
                char JID[20];
                scanf("%s", JID);
                // if jerry is NOT in system
                Jerry *ans;
                ans = lookupInHashTable(htJerries, (Element) JID);
                if (ans == NULL) {
                    printf("Rick this Jerry is not in the daycare ! \n");
                    break;
                }
                //else, if jerry IS IN System
                printf("What physical characteristic do you want to remove from Jerry - %s ? \n", JID);
                scanf("%s", TraitName);
                //if jerry dont have this trait
                if (isTraitExistByName(ans, TraitName) == failure) {
                    printf("The information about his %s not available to the daycare ! \n", TraitName);
                    break;
                }
                //else, if he has this trait, delete it.
                rmTraitFromJerry(ans, TraitName);
                printJerry(ans);
                removeFromMultiValueHashTable(htTraits, TraitName, ans);
                //print jerry after update.

                break;

                //remove jerry from system
            case '4':
                printf("What is your Jerry's ID ? \n");
                char jerToRm[20];

                scanf("%s", jerToRm);
                Jerry *returnJer;
                // if jerry is NOT in system
                returnJer = lookupInHashTable(htJerries, (Element) jerToRm);
                if (returnJer == NULL) {
                    printf("Rick this Jerry is not in the daycare ! \n");
                    break;
                }

                for (int TraitIndex = 0; TraitIndex < returnJer->numOfTrant; TraitIndex++) {
                    removeFromMultiValueHashTable(htTraits, returnJer->jerTrait[TraitIndex]->traitName, returnJer);
                }
                // if system have that jerry, delete it.
                removeFromMultiValueHashTable(htTraits, jerryJoy, returnJer);
                removeFromHashTable(htJerries, returnJer->ID);
                numOfJerrys--;
                printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
                break;

                //find closest jerry by trait
            case '5':
                printf("What do you remember about your Jerry ? \n");
                scanf("%s", TraitName);
                //search for jerries that have this trait, if there is no jerries like that..
                list answer = lookupInMultiValueHashTable(htTraits, TraitName);
                if (answer == NULL || getLengthList(answer) == 0) {
                    printf("Rick we can not help you - we do not know any Jerry's %s ! \n", TraitName);
                    break;
                }
                // else
                printf("What do you remember about the value of his %s ? \n", TraitName);
                scanf("%lf", &traitValue);
                int size = getLengthList(answer);
                Jerry *Jer, *JerToReturn;
                double valueToCheck = 0, absMin, absToCheck;


                for (int jerIndex = 0; jerIndex < size; jerIndex++) {
                    Jer = (Jerry *) getDataByIndex(answer, jerIndex);
                    valueToCheck = geTraitFromJer(Jer, TraitName);
                    absToCheck = fabs((valueToCheck) - (traitValue));
                    if (jerIndex == 0) {
                        JerToReturn = Jer;
                        absMin = absToCheck;
                    } else {
                        if (absToCheck < absMin) {
                            absMin = absToCheck;
                            JerToReturn = Jer;
                        }
                    }
                }

                //find closest jerry by trait value.
                printf("Rick this is the most suitable Jerry we found : \n");

                printJerry(JerToReturn);
                // if system have that jerry, delete it.
                for (int TraitIndex = 0; TraitIndex < JerToReturn->numOfTrant; TraitIndex++) {
                    removeFromMultiValueHashTable(htTraits, JerToReturn->jerTrait[TraitIndex]->traitName, JerToReturn);
                }
                removeFromMultiValueHashTable(htTraits, jerryJoy, JerToReturn);
                removeFromHashTable(htJerries, JerToReturn->ID);

                numOfJerrys--;
                // print it, delete it.
                printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
                break;

            case '6':
                //if there is no jerries in system:
                if (numOfJerrys == 0) {
                    printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                    break;
                }
                list joyAns = lookupInMultiValueHashTable(htTraits, jerryJoy);
                // else
                int JoySize = getLengthList(joyAns);
                Jerry *Jertmp, *joyJer = NULL;
                valueToCheck = 0, absMin = 0, absToCheck = 0, traitValue = 0;


                for (int jerIndex = 0; jerIndex < JoySize; jerIndex++) {
                    Jertmp = (Jerry *) getDataByIndex(joyAns, jerIndex);
                    valueToCheck = getJoy(Jertmp);
                    absToCheck = fabs((valueToCheck) - (traitValue));
                    if (jerIndex == 0) {
                        joyJer = Jertmp;
                        absMin = absToCheck;
                    } else {
                        if (absToCheck < absMin) {
                            absMin = absToCheck;
                            joyJer = Jertmp;
                        }
                    }
                }

                //find closest jerry by trait value.
                printf("Rick this is the most suitable Jerry we found : \n");

                printJerry(joyJer);
                // if system have that jerry, delete it.
                removeFromMultiValueHashTable(htTraits, jerryJoy, joyJer);
                for (int TraitIndex = 0; TraitIndex < joyJer->numOfTrant; TraitIndex++) {
                    removeFromMultiValueHashTable(htTraits, joyJer->jerTrait[TraitIndex]->traitName, joyJer);
                }

                removeFromHashTable(htJerries, joyJer->ID);

                numOfJerrys--;
                printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
                //find saddest jerry(lowest happy value), print it, delete it
                break;

            case '7':
                printf("What information do you want to know ? \n");
                char ch1 = '1';
                while (ch1 != '0') {
                    printf("1 : All Jerries \n");
                    printf("2 : All Jerries by physical characteristics \n");
                    printf("3 : All known planets \n");
                    scanf(" %s", &tempRecive1);
                    if (tempRecive1[1] != '\0')
                        ch1 = 'A';

                    else {
                        ch1 = tempRecive1[0];
                    }
                    switch (ch1) {
                        case '1':
                            //if sys is empty
                            if (numOfJerrys == 0) {
                                printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                                break;
                            }
                            displayMultiValueHashElementsByKey(htTraits);
                            break;

                            //print jerries by Trait
                        case '2':
                            printf("What physical characteristics ? \n");
                            scanf("%s", TraitName);
                            // if Trait has no Jerries

                            //else
                            list *temp;
                            temp = lookupInMultiValueHashTable(htTraits, TraitName);
                            if (temp == NULL || getLengthList(temp) == 0) {
                                printf("Rick we can not help you - we do not know any Jerry's %s ! \n", TraitName);
                            } else {
                                printf("%s : \n", TraitName);
                                displayList(temp);
                            }
                            break;
                        case '3':
                            //print all planets
                            for (int i = 0; i < numOfPlanets; i++) {
                                printPlanet(Planarr[i]);
                            }
                            break;
                        default:
                            printf("Rick this option is not known to the daycare ! \n");
                    }
                    break;
                }
                break;

            case '8':
                //if there is no jerries in the system
                if (numOfJerrys == 0) {
                    printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                    break;
                }
                //else
                printf("What activity do you want the Jerries to partake in ? \n");
                ch1 = '1';
                while (ch1 != '0') {
                    printf("1 : Interact with fake Beth \n");
                    printf("2 : Play golf \n");
                    printf("3 : Adjust the picture settings on the TV \n");
                    scanf(" %s", &tempRecive1);
                    if (tempRecive1[1] != '\0')
                        ch1 = 'A';

                    else {
                        ch1 = tempRecive1[0];
                    }
                    switch (ch1) {
                        int size;
                        case '1':
                            // if jerry has 20+ joy, add 15
                            size = 0;
                            list listOfJerries = lookupInMultiValueHashTable(htTraits, jerryJoy);
                            size = getLengthList(listOfJerries);
                            Jerry *theKilled;
                            for (int i = 0; i < size; i++) {
                                theKilled = getDataByIndex(listOfJerries, i);
                                if (theKilled->jerryJoy >= 20) {
                                    updateJoy(theKilled, theKilled->jerryJoy + 15);
                                } else {
                                    updateJoy(theKilled, theKilled->jerryJoy - 5);
                                }
                            }
                            //else, sub 5
                            printf("The activity is now over ! \n");
                            displayMultiValueHashElementsByKey(htTraits);
                            //print all jerries after update
                            break;
                        case '2':
                            //if jerry has joy 50+, add 10
                            //else sub 10
                            size = 0;
                            listOfJerries = lookupInMultiValueHashTable(htTraits, jerryJoy);
                            size = getLengthList(listOfJerries);
                            for (int i = 0; i < size; i++) {
                                theKilled = getDataByIndex(listOfJerries, i);
                                if (theKilled->jerryJoy >= 50) {
                                    updateJoy(theKilled, theKilled->jerryJoy + 10);
                                } else {
                                    updateJoy(theKilled, theKilled->jerryJoy - 10);
                                }
                            }
                            //else, sub 5
                            printf("The activity is now over ! \n");
                            displayMultiValueHashElementsByKey(htTraits);
                            //print all jerries after update
                            break;
                        case '3':
                            //add 20 to all jerries
                            size = 0;
                            listOfJerries = lookupInMultiValueHashTable(htTraits, jerryJoy);
                            size = getLengthList(listOfJerries);
                            for (int i = 0; i < size; i++) {
                                theKilled = getDataByIndex(listOfJerries, i);
                                updateJoy(theKilled, theKilled->jerryJoy + 20);
                            }
                            printf("The activity is now over ! \n");
                            displayMultiValueHashElementsByKey(htTraits);
                            break;
                        default:
                            printf("Rick this option is not known to the daycare ! \n");
                    }
                    break;
                }
                break;

            case '9':
                //close program
                closeProgram(numOfJerrys, Planarr, numOfPlanets, htJerries, htTraits);
                free(jerryJoy);
                printf("The daycare is now clean and close ! \n");
                return 0;
            default:
                printf("Rick this option is not known to the daycare ! \n");
        }
    }
}



