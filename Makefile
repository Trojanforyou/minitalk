
NAME_SERVER = server
NAME_CLIENT = client

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -Llibft -lft

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = $(LIBFT_DIR)

SRCS_SERVER = server.c
SRCS_CLIENT = client.c
SRCS_BSERVER = server_bonus.c
SRCS_BCLIENT = client_bonus.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
OBJS_BSERVER =$(SRCS_BSERVER:.c=.o)
OBJS_BCLIENT =$(SRCS_BCLIENT:.c=.o)

all: $(NAME_SERVER) $(NAME_CLIENT) $(NAME_BSERVER) $(NAME_BCLIENT)

$(NAME_SERVER): $(OBJS_SERVER) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_SERVER) -o $(NAME_SERVER) $(LDFLAGS)

$(NAME_CLIENT): $(OBJS_CLIENT) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) -o $(NAME_CLIENT) $(LDFLAGS)

$(NAME_BSERVER): $(OBJS_BSERVER) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_BSERVER) -o $(NAME_BSERVER) $(LDFLAGS)

$(NAME_BCLIENT): $(OBJS_BCLIENT) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_BCLIENT) -o $(NAME_BCLIENT) $(LDFLAGS)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFT_INC) -c $< -o $@

clean:
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT) $(OBJS_BSERVER) $(OBJS_BCLIENT)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT) $(NAME_BSERVER) $(NAME_BCLIENT)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
