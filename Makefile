CC      = cc
CFLAGS  = -Wall -Wextra -Werror
LDFLAGS = -pthread

SRC_MND = philo
SRC_DIR = $(SRC_MND)/philo_util

SRCS    = $(SRC_DIR)/init.c \
          $(SRC_DIR)/parsing.c \
          $(SRC_DIR)/philo_utils_1.c \
          $(SRC_DIR)/routine.c \
          $(SRC_MND)/main.c

OBJS    = $(SRCS:.c=.o)
NAME    = philo/philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c philo/philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
