CLIENT=client.c

SERVER=server.c

SRCS=utils.c\
     server_utils.c\
     client_utils.c

INC=minitalk.h

CC=cc

CFLAGS=-Werror -Wextra -Wall -g3

OBJS=$(SRCS:.c=.o)

all: client server

client: $(OBJS) $(INC) $(CLIENT) Makefile
	$(CC) $(CFLAGS) $(CLIENT) $(OBJS) -o client

server: $(OBJS) $(INC) $(CLIENT) Makefile
	$(CC) $(CFLAGS) $(SERVER) $(SRCS) -o server

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -rf $(OBJS)

fclean: clean
	$(RM) -rf client server

re : fclean all

.PHONY: all clean fclean re
