/* @uthor : Nathanael ROVERE & Michel YIP */

#include "../include/render.h"

/* Dimension de la fenetre */
static unsigned int WINDOW_WIDTH = 1600;
static unsigned int WINDOW_HEIGHT = 760;

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

	Level * level = loadLevel("level/testLevel.ppm");
	printLevel(*level);

	/* Vérification de l'initialisation de SDL, si echec : sort du programme */
	if (SDL_Init(SDL_INIT_VIDEO) == -1){
		fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
		return EXIT_FAILURE;
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
	resize_window();
	SDL_WM_SetCaption("Nathanael ROVERE & Michel YIP - Flapimac", NULL);
	transform();

	int loop = 1;

    glColor3ub(255,255,255);
	
	while(loop){
		Uint32 startTime = SDL_GetTicks();

		/* Echange les deux buffers */
		SDL_GL_SwapBuffers();
		/* On nettoie la fenetre */
		glClear(GL_COLOR_BUFFER_BIT);

		//draw Function
		renderLevel(*level);

		/* Gestion des évènements SDL */
		userInput(level);
		
		Uint32 elapsedTime = SDL_GetTicks() - startTime;
		if (elapsedTime < FRAMERATE_MILLISECONDS){
			SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
		}
	}

	SDL_Quit();
	return EXIT_SUCCESS;
}