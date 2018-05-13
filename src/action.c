/* @uthor : Nathanael ROVERE & Michel YIP */

#include "../include/action.h"

/* Move a unit  */
void moveUnit(Unit * unit){
	moveBoundingBoxes(&(unit->boundingBoxes), unit->x_velocity, unit->y_velocity);
	unit->x += unit->x_velocity;
	unit->y += unit->y_velocity;
}

/* Shoot a bullet */
void shoot(Level * level, Unit unit){
	addProjectile(&(level->projectiles), unit);
	printProjectiles(level->projectiles);
}

/* Control the user input */
void userInput(Level * level){
	SDL_Event e;
	while(SDL_PollEvent(&e)) {
		switch(e.type){
			case SDL_KEYDOWN:
				switch(e.key.keysym.sym){
					case SDLK_UP:
		               	level->player->y_velocity = -HERO_VELOCITY;
		          		break;
		            case SDLK_RIGHT:
		               	level->player->x_velocity = HERO_VELOCITY;
		                break;
		            case SDLK_DOWN:
		                level->player->y_velocity = HERO_VELOCITY;
		                break;
		            case SDLK_LEFT:
		                level->player->x_velocity = -HERO_VELOCITY;
		                break;
		            case SDLK_SPACE:
		            	shoot(level, (*level->player));
		            	break;
		            default:
		                break;
				}
				break;
			case SDL_KEYUP:
				switch(e.key.keysym.sym){
					case SDLK_UP:
						level->player->y_velocity = 0;
		    	      	break;
		            case SDLK_RIGHT:
			            level->player->x_velocity = SCROLLSPEED;
		                break;
		            case SDLK_DOWN:
						level->player->y_velocity = 0;
		               	break;
		            case SDLK_LEFT:
		                level->player->x_velocity = SCROLLSPEED;
		                break;
		            default:
		                break;
				}
				break;
			default:
				break;
		}
	}
	moveUnit(level->player);
}
