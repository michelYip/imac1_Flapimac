/* @uthor : Nathanael ROVERE & Michel YIP */

#include "../include/action.h"

/* Nombre de bits par pixel de la fenetre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecond separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000/80;

/**/
static Uint32 special_game_over_time = 0;

void resize(){
	if (SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE | SDL_GL_DOUBLEBUFFER) == NULL){
		fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
		exit(EXIT_FAILURE);
	}
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1600, 950, -110);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	SDL_GL_SwapBuffers();
}

int main (int argc, char ** argv){
	int loop = 1;
	int inMenu = 1;
	int levelSelect = 0;
	int victory = 0;
	int defeat = 0;
	int choice = 1;
	int levelNumber = 0;
	int pleaseValidate = 0;
	char * levelName;

	Mix_Music * BGM;

	TTF_Init();

	SDL_Surface * textures[TEXTURES_SIZE];
    GLuint textureID[TEXTURES_SIZE];

	Level * level = NULL;
	srand(time(NULL));

	/* Initialize Mixer */
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
	   printf("%s", Mix_GetError());
	}

	BGM = Mix_LoadMUS("sound/space-shooter.mp3");
	Mix_PlayMusic(BGM, -1);
	Mix_VolumeMusic(MIX_MAX_VOLUME / 3);

	/* Initialize Window */
	if (SDL_Init(SDL_INIT_VIDEO) == -1){
		fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
		return EXIT_FAILURE;
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
	resize();
	SDL_WM_SetCaption("Nathanael ROVERE & Michel YIP - Flapimac", NULL);
    loadTextures(textures);
    glGenTextures(TEXTURES_SIZE, textureID);
    configTextures(textures, textureID);

    glColor3ub(255,255,255);
    glPushMatrix();
	
	while(loop){
		Uint32 startTime = SDL_GetTicks();

		glClear(GL_COLOR_BUFFER_BIT);

		/***************** InMenu *****************/
		if (pleaseValidate){
			drawGameOverSpecialScreen();
			if (SDL_GetTicks() >= special_game_over_time + GAME_OVER_SPECIAL_DURATION){
				pleaseValidate = 0;
				inMenu = 0;
				levelSelect = 0;
				defeat = 1;
				victory = 0;
				choice = 1;
			}
		}
		else if(inMenu){
			victory = 0;
			defeat = 0;
			drawTitleScreen();
			drawArrow(1090, 340, choice);
			int input = menuInput(&choice, 2);
			if(input == 1){
				inMenu = 0;
				levelSelect = 1;
			} else if(input == 2){
				loop = 0;
			}
		}
		else if (levelSelect){
			drawLevelSelectScreen();
			drawArrow(1035, 75, choice);
			int input = menuInput(&choice, 4);
			if(input == 1){
				levelSelect = 0;
				levelNumber = 1;
				level = loadLevel("level/testLevel.ppm");
			} else if(input == 2){
				levelSelect = 0;
				levelNumber = 2;
				level = loadLevel("level/2.ppm");
			} else if (input == 3){
				levelSelect = 0;
				levelNumber = 3;
				level = loadLevel("level/3.ppm");
			} else if (input == 4){
				levelSelect = 0;
				choice = 1;
				inMenu = 1;
			}
		}
		else if (defeat && !victory){
			drawGameOverScreen();
			drawArrow(1025, 200, choice);
			int input = menuInput(&choice, 3);
			if(input == 1){
				victory = 0;
				defeat = 0;
				inMenu = 0;
				if ((levelName = malloc(sizeof(char)*11)) == NULL){
					exit(EXIT_FAILURE);
				}
				sprintf(levelName, "level/%d.ppm", levelNumber);
				level = loadLevel(levelName);
			} else if(input == 2){
				choice = 1;
				inMenu = 1;
			} else if (input == 3){
				loop = 0;
			}
		}
		else if (!defeat && victory){
			drawVictoryScreen();
			drawArrow(1025, 200, choice);
			int input = menuInput(&choice, 3);
			if(input == 1){
				victory = 0;
				defeat = 0;
				inMenu = 0;
				levelNumber++;
				if (levelNumber > 3) levelNumber = 3;
				if ((levelName = malloc(sizeof(char)*11)) == NULL){
					exit(EXIT_FAILURE);
				}
				sprintf(levelName, "level/%d.ppm", levelNumber);
				level = loadLevel(levelName);
			} else if(input == 2){
				choice = 1;
				inMenu = 1;
			} else if (input == 3){
				loop = 0;
			}
		}

		/***************** InGame *****************/
		else{
			/* Draw Function */	
			scroll(level, textureID);
			//renderBroken(*level, textureID);
			renderLevel(*level, textureID);

			updateElementsPosition(level);
			
			if  (level->player != NULL && 
				(intersect(level->player->boundingBoxes, level->terminal->upperBarrier->boundingBox) || 
				intersect(level->player->boundingBoxes, level->terminal->lowerBarrier->boundingBox))){
				pleaseValidate = 1;
				special_game_over_time = SDL_GetTicks();
				removeUnit(&(level->player), level->player->id);
			}
			
			if (level->player == NULL){
				free(level);
				glPopMatrix();
				glPushMatrix();
				defeat = 1;
				victory = 0;
				choice = 1;
				continue;
			}

			/* SDL_Event */
			userInput(level);

			if (level->enemies == NULL && getState(level->terminal)){
				openBarrier(level->terminal);
			}

			if (level->player->x >= UNIT_SIZE * level->width){
				free(level);
				glPopMatrix();
				glPushMatrix();
				victory = 1;
				defeat = 0;
				inMenu = 0;
				choice = 1;
				continue;
			}
		}

		Uint32 elapsedTime = SDL_GetTicks() - startTime;
		if (elapsedTime < FRAMERATE_MILLISECONDS){
			SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
		}

		SDL_GL_SwapBuffers();

	}

	glPopMatrix();

	Mix_FreeMusic(BGM);
	Mix_CloseAudio();

	SDL_Quit();
	return EXIT_SUCCESS;
}