NAME =	philo

SRCS =	main.c philo.c utils.c init.c

OBJS =	$(patsubst %.c, %.o, $(SRCS))

CFLAGS =	-Wall -Wextra -Werror

CC =	gcc

HEADER =	philo.h

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re