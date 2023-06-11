NAME = fdf

CFLAGS = -Wall -Wextra -Werror -O3 -Ofast #-g

OBJSFOLDER = objs/

SRCS_GNL = get_next_line.c \
	  get_next_line_utils.c

SRCS_PARSER = ft_split.c \
			  ft_strlen.c \
			  ft_strlcpy.c \
			  ft_memcmp.c \
			  ft_atoi.c \

OBJS_FILES = $(SRCS_GNL:.c=.o) \
			 $(SRCS_PARSER:.c=.o) \
			 main.o

OBJS = $(foreach obj, $(OBJS_FILES), $(OBJSFOLDER)$(obj))

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -Imlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
#$(CC) $(OBJS) $(CFLAGS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

$(OBJSFOLDER)%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@
#$(CC) $(CFLAGS) -I/usr/include -Imlx_linux  -c $< -o $@

$(OBJSFOLDER)%.o: gnl/%.c gnl/get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJSFOLDER)%.o: parser/%.c include/parser.h
	$(CC) $(CFLAGS) -c $< -o $@

fclean: clean
	rm -rf $(NAME)

clean:
	rm -rf $(OBJS)

