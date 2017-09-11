NAME = minishell

IDIR = includes/

BIN_DIR = bin/

VPATH = src:includes

FLAGS = -Wall -Wextra -Werror -I$(IDIR) -g

LIB = libft/libft.a

SRCS = main.c			\
	   parse_line.c		\
	   run_command.c

BINS = $(addprefix $(BIN_DIR), $(SRCS:.c=.o))

all: $(NAME)

makelib:
	make -j4 -C libft

$(NAME): $(BINS) makelib
	gcc -o $(NAME) $(BINS) $(FLAGS) $(LIB)

$(BIN_DIR)%.o: %.c
	gcc $(FLAGS) -c -o $@ $<

clean:
	make -C libft/ clean
	/bin/rm -f $(BINS)

fclean: clean
	make -C libft fclean
	/bin/rm -f $(NAME)

re: fclean all
