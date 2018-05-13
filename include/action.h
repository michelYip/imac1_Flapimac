/* @uthor : Nathanael ROVERE & Michel YIP */
#ifndef __ACTION__
#define __ACTION__

#include "level.h"

/* Move a unit  */
void moveUnit(Unit * unit);

/* Shoot a bullet */
void shoot(Level * level, Unit unit);

/* Control the user input */
void userInput(Level * level);

#endif