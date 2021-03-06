/* @uthor : Nathanael ROVERE & Michel YIP */

#include "../include/action.h"

static int shooting = 0;

/* Move a unit  */
void moveUnit(Unit * unit){
	if (unit->y + unit->y_velocity < ELEM_SIZE/2 || unit->y + unit->y_velocity > WINDOW_HEIGHT-ELEM_SIZE/2){
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
	int i;
	int angle = (unit->type == PLAYER) ? unit->y_velocity*3 : 0;
	if (unit->type == PLAYER) reload = HERO_RELOAD;
	else if (unit->type == ENEMY) reload = ENEMY_RELOAD;
	else if (unit->type == BOSS) reload = BOSS_RELOAD;
	if (SDL_GetTicks() >= unit->shotTime + reload){
		if (unit->fire % 2 == 0){
			for (i = 1; i <= unit->fire/2; i++){
				addProjectile(projectiles, *unit, -i*3+angle);
				addProjectile(projectiles, *unit, i*3+angle);
			}
		} 
		else {
			for (i = 1; i <= unit->fire/2; i++){
				addProjectile(projectiles, *unit, -i*8+angle);
				addProjectile(projectiles, *unit, i*8+angle);
			}
			addProjectile(projectiles, *unit, angle);
		}
		unit->shotTime = SDL_GetTicks();
	} 
}

/* Control the user input */
void userInput(Level * level){
	SDL_Event e;
	if (level->player == NULL){
		return;
	}
	if (shooting){
		shoot(&(level->projectiles), level->player);
	}
	if (level->halt){
		while(SDL_PollEvent(&e)) {
			switch(e.type){
				case SDL_KEYUP:
					switch(e.key.keysym.sym){
						case CUSTOM_SDLK_ENTER:
							Mix_VolumeMusic(MIX_MAX_VOLUME / 3);
			            	level->halt = 0;
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
	} else {
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
			            	shooting = 1;
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
			            case SDLK_SPACE:
			            	shooting = 0;
			            	break;
			            case CUSTOM_SDLK_ENTER:
			            	if (level->halt == 0){
			            		Mix_VolumeMusic(MIX_MAX_VOLUME / 6);
			            		level->halt = 1;
			            	}
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
}
