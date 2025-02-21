# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/14 10:31:08 by mdodevsk          #+#    #+#              #
#    Updated: 2025/02/21 16:44:11 by mdodevsk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc -g3

CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = ./src/main.c ./src/path.c ./src/utils.c ./src/check.c ./src/error.c

OBJS = $(SRCS:.c=.o)

NAME = pipex

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

libft/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

all :$(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY : all clean fclean re