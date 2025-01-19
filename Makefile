WARNING = -Wall -Wextra -Werror
CFLAGS = -std=c99 -O0 $(WARNING) -ggdb
LDFLAGS =
LDLIBS = -lSDL2

EMCCFLAGS = -s USE_SDL=2 -s USE_GLFW=3 --shell-file minshell.html -s ASYNCIFY
PLATFORM ?= PLATFORM_DESKTOP
ifeq ($(PLATFORM),WEB)
	CC=emcc
	LDLIBS = $(EMCCFLAGS)
	EXT = .html
endif

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
	$(CC) -c -o $@ $< $(CFLAGS) -D$(PLATFORM)

$(NAME): $(OBJ)
	$(CC) -o $(OUTDIR)/$@$(EXT) $^ $(LDFLAGS) $(LDLIBS)

web-release: clean $(NAME)
	@rm -rf pub index.html
	@mkdir -p pub
	mv -f .build/$(NAME).* pub/
	mv pub/$(NAME).html pub/index.html

clean:
	rm -rf $(OUTDIR) core pub
