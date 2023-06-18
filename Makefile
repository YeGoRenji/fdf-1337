NAME = fdf

CFLAGS = -Wall -Wextra -Werror -O3 -g#-Ofast #-fsanitize=address #-g

OBJSFOLDER = objs/

SRCS_GNL = get_next_line.c \
	  get_next_line_utils.c

OS := $(shell uname -s)

SRCS_PARSER = ft_split.c \
			  ft_strlen.c \
			  ft_tolower.c \
			  ft_strlcpy.c \
			  ft_memcmp.c \
			  ft_atoi.c \
			  ft_atoi_base.c \
			  ft_lstadd_back.c  \
			  ft_lstadd_front.c \
			  ft_lstclear.c \
			  ft_lstdelone.c \
			  ft_lstiter.c \
			  ft_lstlast.c \
			  ft_lstmap.c \
			  ft_lstnew.c \
			  ft_lstsize.c \
			  parser.c

SRCS_MATHS = maths.c \
			 colors.c \
			 matrix.c \
			 utils.c

OBJS_FILES = $(SRCS_GNL:.c=.o) \
			 $(SRCS_PARSER:.c=.o) \
			 $(SRCS_MATHS:.c=.o) \
			 main.o

OBJS = $(foreach obj, $(OBJS_FILES), $(OBJSFOLDER)$(obj))

GLOBAL_HEADERS = include/structs.h include/keys.h

all: objs $(NAME)


objs:
	@mkdir objs

ifeq ($(OS), Darwin)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(OBJSFOLDER)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

else

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

$(OBJSFOLDER)%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux  -c $< -o $@

endif

$(OBJSFOLDER)%.o: src/gnl/%.c src/gnl/get_next_line.h $(GLOBAL_HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiling $<..."

$(OBJSFOLDER)%.o: src/maths/%.c include/maths.h $(GLOBAL_HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiling $<..."

$(OBJSFOLDER)%.o: src/parser/libft/%.c include/parser.h $(GLOBAL_HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiling $<..."

$(OBJSFOLDER)%.o: src/parser/%.c include/parser.h $(GLOBAL_HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiling $<..."

re: fclean all

fclean: clean
	rm -rf $(NAME)

clean:
	rm -rf $(OBJS)

.PHONY: all clean fclean re
