# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mario <mario@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/12 18:37:01 by mdodevsk          #+#    #+#              #
#    Updated: 2025/02/21 20:59:27 by mario            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc 

CFLAGS = -Wall -Wextra -Werror

SRC =	./ft_atoi.c ./ft_bzero.c ./ft_calloc.c \
		./ft_isalnum.c ./ft_isalpha.c ./ft_isascii.c \
		./ft_isdigit.c ./ft_isprint.c ./ft_memchr.c \
		./ft_memcmp.c ./ft_memcpy.c ./ft_memmove.c \
		./ft_memset.c ./ft_strchr.c ./ft_strdup.c \
		./ft_strlcat.c ./ft_strlcpy.c ./ft_strlen.c \
		./ft_strncmp.c ./ft_strnstr.c ./ft_strrchr.c \
		./ft_tolower.c ./ft_toupper.c ./ft_substr.c \
		./ft_strjoin.c ./ft_split.c  \
	  	./ft_putchar_fd.c ./ft_putendl_fd.c ./ft_putstr_fd.c \
	  	./ft_putnbr_fd.c ./ft_itoa.c ./ft_strmapi.c ./ft_striteri.c \
	  	./ft_lstadd_front_bonus.c \
   	 	./ft_lstdelone_bonus.c \
 		./ft_lstclear_bonus.c ./ft_lstiter_bonus.c

NAME = libft.a

AR = ar -rcs

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean: 
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re
