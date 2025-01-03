WARNING = -Wall -Wextra -Werror
CFLAGS = -std=c99 -O0 $(WARNING)
LDFLAGS =

NAME = launch-snake
OUTDIR = .build
OBJ = \
	  $(OUTDIR)/main.o

all: $(NAME)

run: $(NAME)
	$(OUTDIR)/$(NAME)

$(OUTDIR)/%.o: src/%.c
	@mkdir -p $(OUTDIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(NAME): $(OBJ)
	$(CC) -o $(OUTDIR)/$@ $^ $(LDFLAGS)

clean:
	rm -rf $(OUTDIR) core
