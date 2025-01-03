#include <stdint.h>

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

struct Part {
	int8_t x, y;
	struct Part *next;
	struct Part *prev;
};

struct Snake {
	enum Direction dir;
	struct Part *body;
};

struct Part *append(struct Part *head, uint8_t x, uint8_t y);
void update(struct Snake *snake);
void print_parts(struct Part *snake);
