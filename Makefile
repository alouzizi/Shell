NAME = minishell
HEADER = minishell.h

SRCS = qouts.c\
		tree.c\
		main.c

OBJS = $(SRCS:.c=.o)

RL_INC	= -I/goinfre/$(USER)/.brew/opt/readline/include
RL_LIB = -L/goinfre/$(USER)/.brew/opt/readline/lib

%.o : %.c
	@$(CC) $(RL_INC) -I $(RL_INC) -o $@  -c $^

LIBFT = ./libft/libft.a

CFLAGS = 

RM = rm -f
CC = cc

all : $(NAME)
$(NAME) : $(OBJS) $(HEADER) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -l readline $(RL_LIB)

$(LIBFT) :
	make -C./libft

%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -f $(OBJS)
	@make clean -C libft

fclean : clean
	@rm -f $(NAME)
	make fclean -C libft

re : fclean all