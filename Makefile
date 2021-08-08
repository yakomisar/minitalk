SERVER		= server
CLIENT		= client

cc			= gcc
FLAGS		= -WALL -WEXTRA -WERROR
INCL		= srcs/

all:		$(SERVER) $(CLIENT)

$(SERVER)	: server.o support.o srcs/minitalk.h
			@$(cc) server.o support.o -o $@
			@echo "server has been build"

$(CLIENT)	: client.o support.o srcs/minitalk.h
			@$(cc) client.o support.o -o $@
			@echo "client has been build"

%.o	: %.c
	@$(cc) $(FLAGS) $< -c -I $(INCL)

clean	:
		@rm -rf *.o

fclean	: clean
		@rm $(SERVER) $(CLIENT)

re	: fclean all
