CLIENT=client.c
OBJS_CLIENT=client.o

SERVER=server.c
OBJS_SERVER=server.o

SRCS=utils.c\
     server_utils.c\
     client_utils.c

INC=minitalk.h

CC=cc

CFLAGS=-Werror -Wextra -Wall -g3

OBJS=$(SRCS:.c=.o)

all: client server

client: $(OBJS) $(OBJS_CLIENT) $(INC)
	$(CC) $(CFLAGS) $(CLIENT) $(OBJS) -o client

server: $(OBJS) $(OBJS_SERVER) $(INC)
	$(CC) $(CFLAGS) $(SERVER) $(OBJS) -o server

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_CLIENT) $(OBJS_SERVER)

fclean: clean
	$(RM) -rf client server

re : fclean all

.PHONY: all clean fclean re
