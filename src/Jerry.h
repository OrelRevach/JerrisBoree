//
// Created by orelpc on 11/13/20.
//
#include "Defs.h"

#ifndef AP_JERRY_H
#define AP_JERRY_H

typedef struct sTrait {
    char *traitName;
    double value;
    int magicNum;

} Trait;

typedef struct sPlanet {
    char *plaName;
    double x, y, z;
    int magicNum;
} Planet;

typedef struct sOrigin {
    char *oriName;
    Planet *origPlanet;
    int magicNum;
} Origin;

typedef struct sJerry {
    char *ID;
    int jerryJoy;
    Trait **jerTrait;
    int numOfTrant;
    Origin *born;
    int magicNum;
} Jerry;

/*Description:
Receiving: pointer to Jerry Name (char*), JerryJoy level(int) and Origin pointer.
Creating Jerry- if it succeed- returning Jerry *.
If it fail- returning null.
*/
Jerry *createJerry(char *, int, Origin *);
/*Description:
Receiving: pointer to Planet name (char*) and three  double coordinates(x,y,z).
Creating Planet - if it succeed- returning planet *.
If it fail- returning null.
*/
Planet *createPlanet(char *, double, double, double);
/*Description:
Receiving: pointer to Trait name (char*) and the Trait value  (double) .
Creating Trait - if it succeed- returning Trait *.
If it fail- returning null.
*/
Trait *createTrait(char *, double);
/*Description:
Receiving: pointer to Origin name (char*) and the Planet* (pointer to Planet) .
Creating Origin - if it succeed- returning Origin *.
If it fail- returning null.
*/
Origin *createOrigin(char *, Planet *);
/*Description:
Receiving: pointer to Jerry (Jerry*) and name of Trait (char *).
Checking if Trait by name  for specific Jerry is existing.
Returning status: if it exists - returning success.
If it is not - returning failure.
*/
enum e_status isTraitExistByName(Jerry *, char *);
/*Description:
Receiving: pointer to Jerry (Jerry*) and Trait* .
Adding Trait to Jerry .
Returning status: if it succeed - returning success.
If it is not - returning failure.
*/
enum e_status addTraitToJerry(Jerry *, Trait *);
/*Description:
Receiving: pointer to Jerry (Jerry*) and Trait name(char*) .
Removing Trait from Jerry .
Returning status: if it succeed - returning success.
If it is not - returning failure.
*/
enum e_status rmTraitFromJerry(Jerry *, char *);
/*Description:
Receiving: pointer to Jerry (Jerry*)  .
Printiing Jerry .
Returning status: if it succeed - returning success.
If it is not - returning failure.
*/
enum e_status printJerry(Jerry *);
/*Description:
Receiving: pointer to Planet (Planet*)  .
Printiing Planet .
Returning status: if it succeed - returning success.
If it is not - returning failure.
*/
enum e_status printPlanet(Planet *);
/*Description:
Receiving: pointer to Jerry (Jerry*) and new level of joy for Jerry(int) .
 Jerry .
Updating the new level of joy.
*/
void updateJoy(Jerry *, int);
/*Description:
Receiving: pointer to Jerry (Jerry*) .
Destroying the Jerry* .
*/
void destroyJerry(Jerry *);
/*Description:
Receiving: pointer to Origin (Origin*) .
Destroying the Origin* .
*/
void destroyOrigin(Origin *);
/*Description:
Receiving: pointer to Planet (Planet*) .
Destroying the Planet* .
*/
void destroyPlanet(Planet *);
/*Description:
Receiving: pointer to Trait (Trait*) .
Destroying the Trait* .
*/
void destroyTrait(Trait *);
/*Description:
Receiving: 2 (generic) Element from Jerry type  .
Checking if the two elements are Equal .
Returning true - if they are the same, or
false if they are not.
*/
bool EqualKeyJer(Element elem1, Element elem2);
/*Description:
Receiving:Element  .
Freeing Jerry Value(Jerry*) .
Returning status: if it succeed - returning success.
If it is not - returning failure.
*/
status freeValueJerry(Element elem);
/*Description:
Receiving:Element  .
Freeing Key  of the keyValuePair .
Returning status: if it succeed - returning success.
If it is not - returning failure.
*/
status freeKeyJer(Element elem);
/*Description:
Receiving:Element   .
copying  Value of the Pair (Jerry) .
Returning status: if it succeed - returning success.
If it is not - returning failure.
*/
Element copyValueJerry(Element elem);

/*Description:
Receiving:Element   .
Copying Key Value Pair /id(key) .
Returning status: if it succeed - returning success.
If it is not - returning failure.
*/
Element copyKeyJer(Element elem);
/*Description:
Receiving:Element(Value)  .
Printing the Value(print Jerry)
Returning status: if it succeed - returning success.
If it is not - returning failure.
*/
status printValueJerry(Element elem);
/*Description:
Receiving:Element(Jerry name )  .
Printing Jerry name(ID).
Returning status: if it succeed - returning success.
If it is not - returning failure.
*/
status printKeyJerName(Element elem);
/*Description: (Hush function)
Receiving: Element key (Jerry i.d ) doing on it a Mathematical manipulation and returning
the mathematical result. This result is a unic value by key(ID) .
Returning int - the unic result.
*/
int TransformKeyIntoNumberKey(Element key);

/*Description:
Receiving:Element(Trait Name)  .
Copying the Trait Name and Returning As Element.
*/
Element copyKeyTrait(Element elem);
/*Description:
Receiving:Element(name of Trait )  .
Freeing the Trait(trait Name)
Returning status: if it succeed - returning success.
If it is not - returning failure.
*/
status freeKeyTrait(Element elem);
/*Description:
Receiving:Element(name of Trait )  .
Printing the Trait Name.
Returning status: if it succeed - returning success.
If it is not - returning failure.
*/
status printKeyTrait(Element elem);
/*Description:
Receiving:Jerry *.
Returning  int- the value of Trait that Jerry had By name.
Return failure if not found (failure = -1.0)
*/
double geTraitFromJer(Jerry *Jer, char *traitName);
/*Description:
Receiving:Jerry *.
Returning  int- the value of Jerry joy.
 returning JoyFailure if fail (101)

*/
int getJoy(Jerry *Jer);
/*Description:
Receiving: 2 (generic) Element names of Traits  .
Checking if the two elements(namesof Traits) are Equal .
Returning true - if they are the same, or
false if they are not.
*/
enum e_bool EqualKeyTrait(Element elem1, Element elem2);

#endif //AP_JERRY_H
