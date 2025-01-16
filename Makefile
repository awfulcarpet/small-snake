WARNING = -Wall -Wextra -Werror
CFLAGS = -std=c99 -O0 $(WARNING) -ggdb
LDFLAGS =
LDLIBS = -lSDL2

NAME = launch-snake
OUTDIR = .build
OBJ = \
	  $(OUTDIR)/main.o \
	  $(OUTDIR)/snake.o \
	  $(OUTDIR)/apple.o \

all: $(NAME)

run: $(NAME)
	$(OUTDIR)/$(NAME)

$(OUTDIR)/%.o: src/%.c
	@mkdir -p $(OUTDIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(NAME): $(OBJ)
	$(CC) -o $(OUTDIR)/$@ $^ $(LDFLAGS) $(LDLIBS)

clean:
	rm -rf $(OUTDIR) core
