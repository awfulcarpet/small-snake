#include <stdint.h>

extern const int Height, Width;

struct Apple {
	uint8_t x, y;
};

void spawn_apple(struct Apple *apple);
void map_apple(struct Apple *apple, uint8_t screen[Height][Width]);
