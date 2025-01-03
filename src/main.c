#include <SDL2/SDL_events.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <SDL2/SDL.h>

#include "snake.h"

#define WIDTH 12
#define HEIGHT 4
const int Width = WIDTH;
const int Height = HEIGHT;
const int SCALE = 20;
const double MS_PER_FRAME = 1000.0 / 60.0;

uint8_t screen[HEIGHT][WIDTH] = {0};

double
getmsec() {
	struct timeval time;
	gettimeofday(&time, NULL);
	return (double)time.tv_sec * 1000 + (time.tv_usec/1000.0);
}

void
draw_screen(void)
{
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
		}
	}
}


int
main(void)
{
	struct Snake snake = {0};
	snake.dir = LEFT;
	snake.body = append(snake.body, 1, 0);

	if (SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "unable to init SDL: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow("Snake", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	if (win == NULL) {
		fprintf(stderr, "unable to create sdl win: %s\n", SDL_GetError());
		return 1;
	}


	double timer = getmsec();

	while (1) {
		double dt = getmsec() - timer;
		if (dt < MS_PER_FRAME)
			continue;
		map_snake(&snake, screen);
		draw_screen();

		SDL_Event e;
		SDL_PollEvent(&e);
		if (e.type == SDL_QUIT)
			break;

		timer = getmsec();
	}

	return 0;
}
