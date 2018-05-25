/* @uthor : Nathanael ROVERE & Michel YIP */

#include "../include/bonus.h"

static int bonusID = 0;

/* Add a bonus */
void addBonus(BonusList * list, float x, float y){
	Bonus * newBonus;
	if ((newBonus = malloc(sizeof(Bonus))) == NULL){
		fprintf(stderr, "error while allocating memory for addBonus\n");
		exit(EXIT_FAILURE);
	}
	newBonus -> id = bonusID++;
	newBonus -> x = x;
	newBonus -> y = y;
	newBonus -> type = rand()%2;
	newBonus -> boundingBoxes = initBoundingBox(x - BONUS_SIZE/2,
										 	y - BONUS_SIZE/2, 
										 	x + BONUS_SIZE/2, 
										 	y + BONUS_SIZE/2);
	if (list != NULL){
		newBonus -> next = (*list);	
	} else {
		newBonus -> next = NULL;
	}
	(*list) = newBonus;
}

/* Print the list of Bonus in the level */
void printBonus(BonusList list){
	while (list != NULL){
		printf("%f, %f\n",list->x, list->y);
		list = list->next;
	}
}

/* Remove a bonus */ 
void removeBonus(BonusList * list, int id){
	Bonus * tmp = *list;
	Bonus * prev;
	if (tmp == NULL){
		return;
	}
	if (tmp != NULL && tmp->id == id){
		(*list) = (*list)->next;
		free(tmp);
		return;
	}
	prev = tmp;
	while(tmp != NULL && tmp->id != id){
		prev = tmp;
		tmp = tmp -> next;
	}
	if (tmp == NULL){
		return;
	}
	prev->next = tmp->next;
	free(tmp);
	return;
}

/* Apply a bonus to the player */
void applyBonus(Bonus * bonus, Unit * player){
	switch(bonus->type){
		case (HEART):
			if (player->hitpoint < HERO_MAX_HEALTH) player->hitpoint++;
			break;
		case (FIRE_UPGRADE):
			if (player->fire < HERO_MAX_FIRE) player->fire++;
			break;
		default:
			break;
	}
}