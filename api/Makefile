ECHO 	=	printf
CAT 	=	cat
RM      =	rm
FIND 	=	find
CFLAGS	=	-ggdb -Wall -W -Wextra -O2 -D_REENTRANT
LDFLAGS	= -lm -ldxl -lpthread
CC   	= gcc
LD	= gcc

SRCD = src
INCD = -I../include -Iinclude
OBJD = obj
BIND = bin
LIBD = -L../lib
LIBS =

EXEC 	=  DLM
SRCS	=  $(wildcard $(SRCD)/*.c)
OBJ	=  $(SRCS:.c=.o)
OBJS 	:= $(addprefix $(OBJD)/, $(notdir $(OBJ)))

default: $(BIND) $(OBJD) $(BIND)/$(EXEC)

$(BIND)/$(EXEC): $(OBJS)
	@$(ECHO) "Linking ..\n"
	$(LD) -o $@ $^ $(LDFLAGS) $(LIBD) $(LIBS)

$(OBJD)/%.o: $(SRCD)/%.c
	@$(ECHO) "Compiling source file ..\n"
	$(CC) -o $@ -c $< $(CFLAGS) $(INCD)

$(OBJD):
	@mkdir -p $(OBJD)
$(BIND):
	@mkdir -p $(BIND)

clean:
	@$(ECHO) "Cleaning ..\n"
	@$(FIND) $(OBJD) -name *.o -delete

mrproper: clean
	@$(RM) -f $(BIND)/$(EXEC)
	@$(RM) -rf $(OBJD) $(BIND)

dep:
	gccmakedep $(SRCS)

