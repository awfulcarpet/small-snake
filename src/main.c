#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include "snake.h"

uint8_t screen[4][12] = {0};

int
main(void)
{
	struct Snake snake = {0};
	snake.body = append(snake.body, 0, 0);
	snake.body = append(snake.body, 1, 0);
	snake.body = append(snake.body, 2, 0);
	snake.body = append(snake.body, 3, 0);
	snake.body = append(snake.body, 4, 0);
	print_parts(snake.body);
	printf("\n");
	update(&snake);
	print_parts(snake.body);
	return 0;
}
