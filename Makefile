NAME = minishell
HEADER = minishell.h

SRCS = main.c \
	parsing/quotes.c \
	parsing/signal.c \
	parsing/tree.c \
	execution/builtins/export/ft_export.c \
	execution/builtins/export/export.c \
	execution/builtins/export/export_utils.c \
	execution/builtins/export/export_utils2.c \
	execution/builtins/ft_echo.c \
	execution/builtins/ft_pwd.c \
	execution/builtins/ft_env.c \
	execution/builtins/ft_cd.c \
	execution/builtins/ft_minishell.c \
	execution/builtins/ft_unset.c \
	execution/builtins/ft_exit.c \
	execution/operators/pipe.c \
	execution/exec.c \
	execution/exec_utils.c \
	parsing/tree_utils.c

OBJS = $(SRCS:.c=.o)

RL_INC	= -I/goinfre/$(USER)/.brew/opt/readline/include
RL_LIB = -L/goinfre/$(USER)/.brew/opt/readline/lib

%.o : %.c
	@$(CC) $(CFLAGS) $(RL_INC) -I $(RL_INC) -o $@  -c $^

LIBFT = ./libft/libft.a

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

all : $(NAME)
$(NAME) : $(OBJS) $(HEADER) $(LIBFT) 
		@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -l readline $(RL_LIB)

$(LIBFT) :
	@make -C./libft

%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -f $(OBJS)
	@make clean -C libft

fclean : clean
	@rm -f $(NAME)
	@make fclean -C libft

re : fclean all
