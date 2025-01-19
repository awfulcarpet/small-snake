#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <SDL2/SDL.h>

#include "snake.h"
#include "apple.h"

#define WIDTH 12
#define HEIGHT 4
const int Width = WIDTH;
const int Height = HEIGHT;
const int SCALE = 40;
const double MS_PER_FRAME = 1000.0 / 7.0;

enum STATE {
	GAME,
	SCORE
};

uint8_t screen[HEIGHT][WIDTH] = {0};

SDL_Surface *surface = NULL;

double
getmsec() {
	struct timeval time;
	gettimeofday(&time, NULL);
	return (double)time.tv_sec * 1000 + (time.tv_usec/1000.0);
}

int handle_input(struct Snake *snake)
{
	SDL_Event e;
	SDL_PollEvent(&e);
	if (e.type == SDL_QUIT)
		return 1;

	if (e.type != SDL_KEYDOWN)
		return 0;

	switch (e.key.keysym.sym) {
		case SDLK_ESCAPE:
			return 1;
			break;
		case SDLK_r:
			return 2;
			break;
		case SDLK_LEFT:
			snake->dir = LEFT;
			break;
		case SDLK_RIGHT:
			snake->dir = RIGHT;
			break;
		case SDLK_DOWN:
			snake->dir = DOWN;
			break;
		case SDLK_UP:
			snake->dir = UP;
			break;
		default:
			break;
	}

	return 0;
}

void
clear_screen(void)
{
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			screen[i][j] = 0;
		}
	}
}

#define copytobuf(buf, c) \
for (int i = 0; i < 4; i++) { \
	for (int j = 0; j < 3; j++) \
		buf[i][j] = c[i][j]; \
} \

#define switchcopy(num, buf) \
switch (num) { \
	case 0: \
		copytobuf(buf, zero); \
		break; \
	case 1: \
		copytobuf(buf, one); \
		break; \
	case 2: \
		copytobuf(buf, two); \
		break; \
	case 3: \
		copytobuf(buf, three); \
		break; \
	case 4: \
		copytobuf(buf, four); \
		break; \
	case 5: \
		copytobuf(buf, five); \
		break; \
	case 6: \
		copytobuf(buf, six); \
		break; \
	case 7: \
		copytobuf(buf, seven); \
		break; \
	case 8: \
		copytobuf(buf, eight); \
		break; \
	case 9: \
		copytobuf(buf, nine); \
		break; \
}; \

void
map_score(int score, uint8_t screen[Height][Width])
{
	int zero[4][3] = {
		{ 1, 1, 1 },
		{ 1, 0, 1 },
		{ 1, 0, 1 },
		{ 1, 1, 1 },
	};
	int one[4][3] = {
		{ 0, 1, 0 },
		{ 0, 1, 0 },
		{ 0, 1, 0 },
		{ 0, 1, 0 },
	};

	int two[4][3] = {
		{ 0, 1, 1 },
		{ 0, 0, 1 },
		{ 0, 1, 0 },
		{ 0, 1, 1 },
	};

	int three[4][3] = {
		{ 1, 1, 1 },
		{ 0, 0, 1 },
		{ 0, 1, 1 },
		{ 1, 1, 1 },
	};

	int four[4][3] = {
		{ 1, 0, 1 },
		{ 1, 1, 1 },
		{ 0, 0, 1 },
		{ 0, 0, 1 },
	};

	int five[4][3] = {
		{ 1, 1, 1 },
		{ 1, 0, 0 },
		{ 0, 1, 1 },
		{ 1, 1, 1 },
	};

	int six[4][3] = {
		{ 1, 1, 1 },
		{ 1, 0, 0 },
		{ 1, 1, 1 },
		{ 1, 1, 1 },
	};

	int seven[4][3] = {
		{ 1, 1, 1 },
		{ 0, 0, 1 },
		{ 0, 0, 1 },
		{ 0, 0, 1 },
	};

	int eight[4][3] = {
		{ 1, 1, 1 },
		{ 1, 0, 1 },
		{ 1, 1, 1 },
		{ 1, 1, 1 },
	};

	int nine[4][3] = {
		{ 0, 1, 1 },
		{ 0, 1, 1 },
		{ 0, 0, 1 },
		{ 0, 0, 1 },
	};

	int tensbuffer[4][3] = {0};
	int onesbuffer[4][3] = {0};

	int mid = (WIDTH - 1) / 2;
	int left = mid - 2;
	int right = mid + 2;


	int ones = score % 10;
	int tens = score / 10;
	switchcopy(tens, tensbuffer);
	switchcopy(ones, onesbuffer);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			screen[i][left + j] = tensbuffer[i][j];
			screen[i][right + j] = onesbuffer[i][j];
		}
	}
}

void
draw_screen(void)
{
	uint32_t *pixels = (uint32_t *)surface->pixels;
	for (uint32_t i = 0; (int)i < HEIGHT * SCALE; i++) {
		for (uint32_t j = 0; (int)j < WIDTH * SCALE; j++) {
			switch (screen[i / SCALE][j / SCALE]) {
				case 0:
					pixels[i * WIDTH * SCALE + j] = 0x00;
					break;
				case 1:
					pixels[i * WIDTH * SCALE + j] = 0x00ff00;
					break;
				case 2:
				#ifdef WEB
					pixels[i * WIDTH * SCALE + j] = 0x0000ff;
				#else
					pixels[i * WIDTH * SCALE + j] = 0xff0000;
				#endif
					break;
			}
		}
	}
}

void
reset_game(struct Snake *snake, struct Apple *apple)
{
	spawn_apple(apple, screen);
	snake_free_parts(snake);
	snake->dir = RIGHT;
	snake->body = append(snake->body);
}


int
main(void)
{
	struct Snake snake = {0};
	snake.dir = RIGHT;
	snake.body = append(snake.body);

	struct Apple apple = {0};

	if (SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "unable to init SDL: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow("Snake", 0, 0, Width * SCALE, Height * SCALE, SDL_WINDOW_SHOWN);
	surface = SDL_GetWindowSurface(win);

	if (win == NULL) {
		fprintf(stderr, "unable to create sdl win: %s\n", SDL_GetError());
		return 1;
	}


	double timer = getmsec();
	enum STATE state = GAME;

	spawn_apple(&apple, screen);
	while (1) {
		int key = handle_input(&snake);

		if (key == 1)
			break;

		if (key == 2) {
			state = GAME;
			reset_game(&snake, &apple);
			printf("%d %d\n", snake.body->x, snake.body->y);
			continue;
		}

		double dt = getmsec() - timer;
		if (dt < MS_PER_FRAME)
			continue;

		switch (state) {
			case GAME: {
				if(update(&snake))
					state = SCORE;

				if (snake.body->x == apple.x && snake.body->y == apple.y) {
					spawn_apple(&apple, screen);
					append(snake.body);
				}

				clear_screen();
				map_snake(&snake, screen);
				map_apple(&apple, screen);
				break;
			}

			case SCORE: {
				clear_screen();
				map_score(snake_len(&snake), screen);
				break;
			}
		}

		draw_screen();



		timer = getmsec();
		SDL_UpdateWindowSurface(win);
	}

	printf("score: %d\n", snake_len(&snake));

	return 0;
}
