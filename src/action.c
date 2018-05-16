/* @uthor : Nathanael ROVERE & Michel YIP */

#include "../include/action.h"

/* Move a unit  */
void moveUnit(Unit * unit){
	if (unit->y + unit->y_velocity < UNIT_SIZE/2 || unit->y + unit->y_velocity > WINDOW_HEIGHT-UNIT_SIZE/2){
		moveBoundingBoxes(&(unit->boundingBoxes), unit->x_velocity, 0);
		unit->x += unit->x_velocity;
		return;
	}
	moveBoundingBoxes(&(unit->boundingBoxes), unit->x_velocity, unit->y_velocity);
	unit->x += unit->x_velocity;
	unit->y += unit->y_velocity;
}

/* Shoot a bullet */
void shoot(ProjectileList * projectiles, Unit * unit){
	int reload = 0;
	if (unit->type == PLAYER) reload = HERO_RELOAD;
	else if (unit->type == ENEMY) reload = ENEMY_RELOAD;
	else if (unit->type == BOSS) reload = BOSS_RELOAD;
	if (SDL_GetTicks() >= unit->shotTime + reload){
		//Add projectile Type 
		if (unit->fire == BULLET){
			addProjectile(projectiles, *unit, 0);
		}
		else if (unit->fire == VOLLEY){
			addProjectile(projectiles, *unit, 10);
			addProjectile(projectiles, *unit, 5);
			addProjectile(projectiles, *unit, 0);
			addProjectile(projectiles, *unit, -5);
			addProjectile(projectiles, *unit, -10);
		}
		unit->shotTime = SDL_GetTicks();
		printProjectiles(*projectiles);
	}
}

/* Control the user input */
void userInput(Level * level){
	SDL_Event e;
	if (level->player == NULL){
		return;
	}
	while(SDL_PollEvent(&e)) {
		switch(e.type){
			case SDL_KEYDOWN:
				switch(e.key.keysym.sym){
					case SDLK_UP:
		               	level->player->y_velocity = -HERO_VELOCITY;
		          		break;
		            case SDLK_DOWN:
		                level->player->y_velocity = HERO_VELOCITY;
		                break;
		            case SDLK_SPACE:
		            	shoot(&(level->projectiles), level->player);
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
		            case SDLK_DOWN:
						level->player->y_velocity = 0;
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
