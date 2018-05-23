/* @uthor : Nathanael ROVERE & Michel YIP */

#include "../include/action.h"

/* Nombre de bits par pixel de la fenetre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecond separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000/60;

void resize(){
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1600, 760, 0);
}

void resize_window(){
	if (SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE | SDL_GL_DOUBLEBUFFER) == NULL){
		fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
		exit(EXIT_FAILURE);
	}
	resize();
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapBuffers();
}

void transform(){
	glMatrixMode(GL_MODELVIEW);
}

int main (int argc, char ** argv){
	srand(time(NULL));
	
	Level * level;

	if (SDL_Init(SDL_INIT_VIDEO) == -1){
		fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
		return EXIT_FAILURE;
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
	resize_window();
	SDL_WM_SetCaption("Nathanael ROVERE & Michel YIP - Flapimac", NULL);
	transform();

	SDL_Surface * textures[TEXTURES_SIZE];
    loadTextures(textures);
    GLuint textureID[TEXTURES_SIZE];
    glGenTextures(TEXTURES_SIZE, textureID);
    configTextures(textures, textureID);

	int loop = 1;
	int inMenu = 1;
	int victory = 0;
	int defeat = 0;
	int choice = 0;

    glColor3ub(255,255,255);
    glPushMatrix();
	
	while(loop){
		Uint32 startTime = SDL_GetTicks();

		/* InMenu */
		if(inMenu){
			victory = 0;
			defeat = 0;
			drawTitleScreen();
			if (!choice){
				glPushMatrix();
					glTranslatef(250, 575, 0);
					drawArrow();
				glPopMatrix();
			} else {
				glPushMatrix();
					glTranslatef(1000, 575, 0);
					drawArrow();
				glPopMatrix();
			}	
			SDL_Event e;
			while(SDL_PollEvent(&e)) {
				switch(e.type){
					case SDL_KEYUP:
						switch(e.key.keysym.sym){
							case SDLK_SPACE:
								if (!choice){
									inMenu = 0;
									level = loadLevel("level/testLevel.ppm");
								} else {
									loop = 0;
									break;
								}
				    	      	break;
				    	    case SDLK_LEFT:
				    	    	choice = 0;
				    	    	break;
				    	    case SDLK_RIGHT:
				    	    	choice = 1;
				    	    	break;
				            default:
				                break;
						}
						break;
					default:
						break;
				}
			}
		}
		else if (defeat && !victory){
			drawGameOverScreen();
			if (!choice){
				glPushMatrix();
					glTranslatef(250, 575, 0);
					drawArrow();
				glPopMatrix();
			} else {
				glPushMatrix();
					glTranslatef(1000, 575, 0);
					drawArrow();
				glPopMatrix();
			}	
			SDL_Event e;
			while(SDL_PollEvent(&e)) {
				switch(e.type){
					case SDL_KEYUP:
						switch(e.key.keysym.sym){
							case SDLK_SPACE:
								if (!choice){
									inMenu = 1;
								} else {
									loop = 0;
									break;
								}
				    	      	break;
				    	    case SDLK_LEFT:
				    	    	choice = 0;
				    	    	break;
				    	    case SDLK_RIGHT:
				    	    	choice = 1;
				    	    	break;
				            default:
				                break;
						}
						break;
					default:
						break;
				}
			}
		}
		else if (!defeat && victory){
			drawVictoryScreen();
			if (!choice){
				glPushMatrix();
					glTranslatef(250, 575, 0);
					drawArrow();
				glPopMatrix();
			} else {
				glPushMatrix();
					glTranslatef(1000, 575, 0);
					drawArrow();
				glPopMatrix();
			}	
			SDL_Event e;
			while(SDL_PollEvent(&e)) {
				switch(e.type){
					case SDL_KEYUP:
						switch(e.key.keysym.sym){
							case SDLK_SPACE:
								if (!choice){
									inMenu = 1;
								} else {
									loop = 0;
									break;
								}
				    	      	break;
				    	    case SDLK_LEFT:
				    	    	choice = 0;
				    	    	break;
				    	    case SDLK_RIGHT:
				    	    	choice = 1;
				    	    	break;
				            default:
				                break;
						}
						break;
					default:
						break;
				}
			}
		}

		/* InGame */
		else{
			/* Draw Function */
			scroll(level, textureID);
			renderLevel(*level, textureID);
			updateElementsPosition(level);
			
			if (level->player == NULL){
				printf("Game Over !\n");
				glPopMatrix();
				glPushMatrix();
				defeat = 1;
				victory = 0;
				continue;
			}

			/* SDL_Event */
			userInput(level);

			if (level->enemies == NULL && getState(level->terminal)){
				openBarrier(level->terminal);
			}

			if (level->player->x >= UNIT_SIZE * level->width){
				printf("VICTORY !!!\n");
				glPopMatrix();
				glPushMatrix();
				victory = 1;
				defeat = 0;
				continue;
			}
		}

		Uint32 elapsedTime = SDL_GetTicks() - startTime;
		if (elapsedTime < FRAMERATE_MILLISECONDS){
			SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
		}

		SDL_GL_SwapBuffers();
		glClear(GL_COLOR_BUFFER_BIT);
	}

	glPopMatrix();

	SDL_Quit();
	return EXIT_SUCCESS;
}