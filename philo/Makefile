CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo
SRC = main.c utils.c memory.c check_arguments.c death.c
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re