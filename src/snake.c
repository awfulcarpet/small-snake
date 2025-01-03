#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "snake.h"

struct Part *
append(struct Part *snake)
{
	struct Part *head = snake;
	struct Part *tail = calloc(1, sizeof(struct Part));

	tail->x = -1;
	tail->y = 0;
	tail->next = NULL;
	tail->prev = NULL;

	if (snake == NULL) {
		return tail;
	}

	while (snake->next != NULL) snake = snake->next;

	tail->prev = snake;
	tail->x = snake->x;
	tail->y = snake->y;
	snake->next = tail;

	return head;
}

void
update(struct Snake *snake)
{
	if (snake == NULL)
		return;

	if (snake->body == NULL)
		return;

	struct Part *head = snake->body;
	struct Part *parts = snake->body;

	while (parts->next != NULL) parts = parts->next;

	while (parts->prev != NULL) {
		parts->x = parts->prev->x;
		parts->y = parts->prev->y;

		parts = parts->prev;
	}

	if (snake->dir == UP) {
		head->y--;
	}

	if (snake->dir == DOWN) {
		head->y++;
	}

	if (snake->dir == LEFT) {
		head->x--;
	}
	if (snake->dir == RIGHT) {
		head->x++;
	}
}

void
map_snake(struct Snake *snake, uint8_t screen[Height][Width])
{
	if (snake == NULL)
		return;

	struct Part *parts = snake->body;

	while (parts != NULL) {
		screen[parts->y][parts->x] = 1;
		parts = parts->next;
	}
}

void
print_parts(struct Part *snake)
{
	while (snake != NULL) {
		printf("%d %d\n", snake->x, snake->y);
		snake = snake->next;
	}
}
