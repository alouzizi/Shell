NAME = minishell
HEADER = minishell.h

SRCS = main.c \
	parsing/quotes.c \
	parsing/heredoc.c \
	parsing/heredoc_utils.c \
	parsing/dollar.c \
	parsing/signal.c \
	parsing/tree.c \
	execution/builtins/export.c \
	execution/builtins/export_utils.c \
	execution/builtins/echo.c \
	execution/builtins/pwd.c \
	execution/builtins/env.c \
	execution/builtins/cd.c \
	execution/builtins/unset.c \
	execution/operators/pipe.c \
	execution/operators/redirection.c \
	execution/exec.c \
	execution/exec_utils.c \
	execution/utils.c  \
	parsing/tree_utils.c \
	parsing/redirection_utils.c \
	parsing/utils.c

OBJS = $(SRCS:.c=.o)

RL_INC	= -I/goinfre/$(USER)/.brew/opt/readline/include
RL_LIB = -L/goinfre/$(USER)/.brew/opt/readline/lib

%.o : %.c
	@$(CC) $(CFLAGS) $(RL_INC) -I $(RL_INC) -o $@  -c $^

LIBFT = ./libft/libft.a

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
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

run : re
	@rm -rf $(OBJS)