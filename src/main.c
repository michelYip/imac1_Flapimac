#include "../include/element.h"

/* Dimension de la fenetre */
static unsigned int WINDOW_WIDTH = 1400;
static unsigned int WINDOW_HEIGHT = 900;

/* Nombre de bits par pixel de la fenetre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecond separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000/60;

void resize(){
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-700, 700, -450, 450);
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
	BoundingBox * boxes1 = initBoundingBox(0,0,20,20);
	BoundingBox * boxes2 = initBoundingBox(0,0,40,40);

	addBoundingBox(&boxes2, 40,40,60,60);
	addBoundingBox(&boxes2, 30,10,60,30);

	/* Vérification de l'initialisation de SDL, si echec : sort du programme */
	if (SDL_Init(SDL_INIT_VIDEO) == -1){
		fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
		return EXIT_FAILURE;
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
	resize_window();
	SDL_WM_SetCaption("Michel YIP - OpenGL_TP03", NULL);
	transform();

	int loop = 1;

    glColor3ub(255,255,255);
	
	while(loop){
		Uint32 startTime = SDL_GetTicks();

		/* Echange les deux buffers */
		SDL_GL_SwapBuffers();
		/* On nettoie la fenetre */
		glClear(GL_COLOR_BUFFER_BIT);

		drawBoundingBoxes(boxes1);
		drawBoundingBoxes(boxes2);

		/* Gestion des évènements SDL */
		SDL_Event e;
		while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT){
                loop = 0;
                break;
            }
			switch(e.type){
				case SDL_KEYUP:
                    switch(e.key.keysym.sym){
                        case SDLK_q:
                            printf("Quit...\n");
                            loop = 0;
                            break;
                        case SDLK_UP:
                        	boxes1->y1 += 10;
                        	boxes1->y2 += 10;
                        	printf("%d\n", intersect(boxes1, boxes2));
                        	break;
                        case SDLK_DOWN:
                        	boxes1->y1 -= 10;
                        	boxes1->y2 -= 10;
                        	printf("%d\n", intersect(boxes1, boxes2));
                        	break;
                        case SDLK_LEFT:
                        	boxes1->x1 -= 10;
                        	boxes1->x2 -= 10;
                        	printf("%d\n", intersect(boxes1, boxes2));
                        	break;
                        case SDLK_RIGHT:
                        	boxes1->x1 += 10;
                        	boxes1->x2 += 10;
                        	printf("%d\n", intersect(boxes1, boxes2));
                        	break;
                        default:
                            break;
                        }
					break;
				case SDL_VIDEORESIZE:
					WINDOW_WIDTH = e.resize.w;
					WINDOW_HEIGHT= e.resize.h;
					resize_window();
				default:
					break;
			}
		}
		Uint32 elapsedTime = SDL_GetTicks() - startTime;
		if (elapsedTime < FRAMERATE_MILLISECONDS){
			SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
		}
	}

	SDL_Quit();
	return EXIT_SUCCESS;
}