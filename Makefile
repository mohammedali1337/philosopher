CC 		= cc 
CFLAGS 	= -Wall -Wextra -Werror
LDFLAGS	= -lpthread
SRC		= mandatory/parsing.c mandatory/philo_utils.c mandatory/philo_utils_2.c main.c
OBJ		= $(SRC:%.c=%.o)
NAME	= philo

all:$(NAME)

$(NAME):$(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean:clean
	rm -rf $(NAME)

re:fclean all	