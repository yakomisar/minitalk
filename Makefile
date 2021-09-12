SERVER		= server
CLIENT		= client

SERVER_BONUS		= server_bonus
CLIENT_BONUS		= client_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC_S = server.c minitalk.c
SRC_C = client.c minitalk.c

SRC_S_BONUS = server_bonus.c minitalk_bonus.c
SRC_C_BONUS = client_bonus.c minitalk_bonus.c

OBJ_S = $(SRC_S:%.c=%.o)
OBJ_C = $(SRC_C:%.c=%.o)

OBJ_S_BONUS = $(SRC_S_BONUS:%.c=%.o)
OBJ_C_BONUS = $(SRC_C_BONUS:%.c=%.o)

%.o: %.c
	$(CC) $(CFLAGS) -I . -c $< -o $@

all:	$(SERVER) $(CLIENT)

$(SERVER): $(OBJ_S)
	$(CC) $(CFLAGS) $^ -o $@

$(CLIENT): $(OBJ_C)
	$(CC) $(CFLAGS) $^ -o $@

bonus:	$(SERVER_BONUS) $(CLIENT_BONUS)

$(SERVER_BONUS): $(OBJ_S_BONUS)
	$(CC) $(CFLAGS) $^ -o $@

$(CLIENT_BONUS): $(OBJ_C_BONUS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(OBJ_S) $(OBJ_C) $(OBJ_S_BONUS) $(OBJ_C_BONUS)

fclean: clean
	$(RM) $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)

re: fclean all bonus

.PHONY: all clean fclean re bonus
