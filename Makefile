NAME = minishell

IDIR = includes/

BIN_DIR = bin/

LIB_DIR = libft/

VPATH = src:includes

FLAGS = -Wall -Wextra -Werror -I$(IDIR) -I$(LIB_DIR) -g

LIB = libft/libft.a

SRCS = main.c				\
	   tilde.c				\
	   signal.c				\
	   parse_line.c			\
	   run_command.c		\
	   run_builtin.c		\
	   builtins/cd.c		\
	   builtins/env.c		\
	   builtins/unsetenv.c	\
	   builtins/builtins.c	\

BINS = $(addprefix $(BIN_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(BIN_DIR)/builtins:
	mkdir -p $(BIN_DIR)/builtins

$(LIB):
	make -j4 -C libft

$(NAME): $(BINS) $(LIB)
	gcc -o $(NAME) $(BINS) $(FLAGS) $(LIB)

$(BIN_DIR)%.o: %.c | $(BIN_DIR)/builtins
	gcc $(FLAGS) -c -o $@ $<

clean:
	make -C libft/ clean
	/bin/rm -f $(BINS)

fclean: clean
	make -C libft fclean
	/bin/rm -f $(NAME)

re: fclean all
