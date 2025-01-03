#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "snake.h"

struct Part *
append(struct Part *snake, uint8_t x, uint8_t y)
{
	struct Part *head = snake;
	struct Part *tail = calloc(1, sizeof(struct Part));

	tail->x = x;
	tail->y = y;
	tail->next = NULL;
	tail->prev = NULL;

	if (snake == NULL) {
		return tail;
	}

	while (snake->next != NULL) snake = snake->next;

	tail->prev = snake;
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
print_parts(struct Part *snake)
{
	while (snake != NULL) {
		printf("%d %d\n", snake->x, snake->y);
		snake = snake->next;
	}
}
