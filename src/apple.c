#include <stdio.h>
#include <assert.h>

#include "apple.h"

void
spawn_apple(struct Apple *apple)
{
	FILE *f = fopen("/dev/random", "r");

	apple->x = fgetc(f) % Width;
	apple->y = fgetc(f) % Height;

	fclose(f);
}

void
map_apple(struct Apple *apple, uint8_t screen[Height][Width])
{
	assert(apple->x < Width && apple->y < Height);
	screen[apple->y][apple->x] = 2;
}
