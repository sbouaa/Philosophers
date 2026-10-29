CC = cc 

NAME = philo

CFLAGS = -Wall -Wextra -Werror

HEADER = philo.h 

SRCS = main.c init.c utils_1.c utils_2.c philo_actions.c monitor.c

RM = rm -rf

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
		$(RM) $(OBJS)

fclean : 
		$(RM) $(OBJS)
		$(RM) $(NAME)

re : fclean all
