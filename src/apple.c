#include <stdint.h>
#include <stdio.h>
#include <assert.h>

#include "apple.h"

void
spawn_apple(struct Apple *apple, uint8_t screen[Height][Width])
{
	FILE *f = fopen("/dev/random", "r");

	do {
		apple->x = fgetc(f) % Width;
		apple->y = fgetc(f) % Height;
	} while (screen[apple->y][apple->x] == 1);

	fclose(f);
}

void
map_apple(struct Apple *apple, uint8_t screen[Height][Width])
{
	assert(apple->x < Width && apple->y < Height);
	screen[apple->y][apple->x] = 2;
}
