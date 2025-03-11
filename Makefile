CC 		= cc 
CFLAGS 	= -Wall -Wextra -Werror -lpthread
SRC		= main.c mandatory/parsing 
OBJ		= $(SRC:.c=.o)
NAME	= philo

all:$(NAME)

$(NAME):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o:%.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean:clean
	rm -rf $(NAME)

re:fclean all