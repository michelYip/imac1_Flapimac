/* @uthor : Nathanael ROVERE & Michel YIP */

#include "../include/action.h"

/* Move a unit  */
void moveUnit(float x_accel, float y_accel, Unit * unit){
	unit->x += x_accel;
	unit->y += y_accel;
	moveBoundingBoxes(unit->boundingBoxes, x_accel, y_accel);
}

/* Shoot a bullet */
void shoot(Unit * unit);

/* Control the user input */
void userInput(Level * level){
	float x_accel = 0;
	float y_accel = 0;
	int loop = 0;
	SDL_Event e;
	while(SDL_PollEvent(&e)) {
		do{
			switch(e.type){
				case SDL_KEYDOWN:
					loop = 1;
					switch(e.key.keysym.sym){
						case SDLK_UP:
	                       	y_accel = -HERO_ACCEL;
	                		break;
	                    case SDLK_RIGHT:
	                       	x_accel = HERO_ACCEL;
	                       	break;
	                    case SDLK_DOWN:
	                       	y_accel = HERO_ACCEL;
	                       	break;
	                    case SDLK_LEFT:
	                      	x_accel = -HERO_ACCEL;
	                       	break;
	                    default:
	                        break;
					}
					break;
				case SDL_KEYUP:
					if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_LEFT){
						loop = 0;
					}
					break;
				default:
					break;
			}
			moveUnit(x_accel, y_accel, level->player);
			printf("x : %f, y : %f\n", level->player->x, level->player->y);
		}while(loop == 1);
	}
}
