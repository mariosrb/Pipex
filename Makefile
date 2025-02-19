# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/14 10:31:08 by mdodevsk          #+#    #+#              #
#    Updated: 2025/02/19 12:41:22 by mdodevsk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc -g3

CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./libft/libft.a

SRCS = ./src/main.c ./src/path.c ./src/utils.c ./src/check.c ./src/error.c

OBJS = $(SRCS:.c=.o)

NAME = pipex

all : $(NAME)

libft/libft.a:
	make -C ./libft

$(NAME): $(OBJS) $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make clean -C ./libft

fclean: clean
	rm -f $(NAME)

re: flcean all