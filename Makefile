#allegro t2 makefile

#
#flags
#
CC = gcc
CFLAGS = -Wall -Wextra 

#
#project files
#
SRCS = main.c ground.c role.c load.c score.c menu.c state.c function.c music.c game.c  object.c
OBJS = $(SRCS:.c=.o)
DBGB = t2dbg
RELB = t2
#
#include files
#
LIB = -lallegro -lallegro_image -lallegro_font -lallegro_color -lallegro_primitives -lallegro_audio -lallegro_acodec -lallegro_ttf

#
#build settings
#
DBGOBJDIR = obj/debug
RELOBJDIR = obj/release
DBGOBJS = $(addprefix $(DBGOBJDIR)/, $(OBJS))
RELOBJS = $(addprefix $(RELOBJDIR)/, $(OBJS))

DBGCFLAGS = -g
RELCFLAGS = -o3  

DBGBINDIR = ./#bin/debug
RELBINDIR = ./#bin/release
DBGBIN =$(DBGBINDIR)/$(DBGB)
RELBIN =$(RELBINDIR)/$(RELB)

.PHONY: all clean debug prep release remake

all:prep release

#
#
#
debug: $(DBGBIN)

$(DBGBIN) : $(DBGOBJS)
	$(CC) $(CFLAGS) $(DBGCFLAGS) $^ -o $(DBGBIN) $(LIB)

$(DEBOBJDIR)/%.o:%.c
	$(CC) -c $(CFLAGS) $(DEGCFLAGS) -o $@ $<

#
#release
#

release: $(RELBIN)

$(RELBIN) : $(RELOBJS)
	$(CC) $(CFLAGS) $(RELCFLAGS) $^ -o $(RELBIN) $(LIB)

$(RELOBJDIR)/%.o:%.c
	$(CC) -c $(CFLAGS) $(RELCFLAGS) -o $@ $<

#
#other
#
prep:
	@mkdir -p $(DBGOBJDIR) $(DBGBINDIR) $(RELOBJDIR) $(RELBINDIR)
remake: clean all

clean:
	rm -f $(DBGOBJS)
	rm -f $(RELOBJS)
