SERVER		= server
CLIENT		= client

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC_S = server.c minitalk.c
SRC_C = client.c minitalk.c

OBJ_S = $(SRC_S:%.c=%.o)
OBJ_C = $(SRC_C:%.c=%.o)

%.o: %.c
	$(CC) $(CFLAGS) -I . -c $< -o $@

all: $(SERVER) $(CLIENT)

$(SERVER): $(OBJ_S)
	$(CC) $(CFLAGS) $^ -o $@

$(CLIENT): $(OBJ_C)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(OBJ_S) $(OBJ_C)

fclean: clean
	$(RM) $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re
