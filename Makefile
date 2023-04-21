NAME = main

OBJ = main.o

CFLAGS = -Wall -Wextra -Werror -O3 #-g

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux  -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

fclean: clean
	rm -rf $(NAME)

clean:
	rm -rf $(OBJ)
