SOURCES = server.c client.c
OBJECTS = $(SOURCES:.c=.o)

NAME_C = client
NAME_S = server

SOURCES_B = server_bonus.c client_bonus.c
OBJECTS_B = $(SOURCES_B:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME_S) $(NAME_C)
$(NAME_S): server.o
	rm -rf $(NAME_S)
	make -C libft
	$(CC) -o $@ $< libft/libft.a

$(NAME_C): client.o
	rm -rf $(NAME_C)
	$(CC) -o $@ $< libft/libft.a

bonus: server_bonus client_bonus

server_bonus: server_bonus.o
	rm -rf $(NAME_S)
	make -C libft
	$(CC) -o $(NAME_S) $< libft/libft.a 

client_bonus: client_bonus.o
	rm -rf $(NAME_C)
	$(CC) -o $(NAME_C) $< libft/libft.a

clean:
	rm -f $(OBJECTS) $(OBJECTS_B)
	make -C libft clean
	
fclean: clean
	rm -f server client libft/libft.a


re: fclean all
