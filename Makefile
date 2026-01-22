NAME		= pipex
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a
SRCS		= main.c \
			  utils1.c \
			  utils2.c \
			  utils3.c
OBJS		= $(SRCS:.c=.o)
HEADERS		= pipex.h

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)


%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re