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
	int i;
	if (unit->type == PLAYER) reload = HERO_RELOAD;
	else if (unit->type == ENEMY) reload = ENEMY_RELOAD;
	else if (unit->type == BOSS) reload = BOSS_RELOAD;
	if (SDL_GetTicks() >= unit->shotTime + reload){
		if (unit->fire % 2 == 0){
			for (i = 1; i <= unit->fire/2; i++){
				addProjectile(projectiles, *unit, -i*2.5);
				addProjectile(projectiles, *unit, i*2.5);
			}
		} 
		else {
			for (i = 1; i <= unit->fire/2; i++){
				addProjectile(projectiles, *unit, -i*5);
				addProjectile(projectiles, *unit, i*5);
			}
			addProjectile(projectiles, *unit, 0);
		}
		unit->shotTime = SDL_GetTicks();
	} 
	if (SDL_GetTicks() < unit->shotTime + reload && unit -> type == PLAYER) {
		printf("unable to shoot !%d < %d\n",SDL_GetTicks(),unit->shotTime + reload);
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
