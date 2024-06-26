CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -lmlx -lX11 -lXext -lm
CC = cc #-fsanitize=address -g3
NAME = so_long

SRCS = main.c so_long.c check_arguments.c so_long_utils.c clean_functions.c move_player.c flood_fill.c \
	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS)  -o $(NAME) $(OBJS) $(MLXFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: clean all