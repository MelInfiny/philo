# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: enolbas <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/11 16:00:09 by enolbas           #+#    #+#              #
#    Updated: 2022/02/11 16:00:37 by enolbas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = ft_printf.c		\
	ft_putnbr_base_u.c	\
	ft_nbrlen_base_u.c	\
	print_perc.c		\
	print_char.c		\
	print_hexa.c		\
	print_nbr.c			\
	print_nbr_u.c		\
	print_ptr.c			\
	print_str.c

OBJS := ${SRCS:.c=.o}

CC = gcc

CFLAGS = -c -Wall -Werror -Wextra

INCLUDES = -I.

$(NAME): ${OBJS}
	${CC} ${CFLAGS} ${INCLUDES} $(SRCS)
	ar -rcs $(NAME) ${OBJS}

all: $(NAME)

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
