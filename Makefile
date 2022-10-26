# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: enolbas <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 13:30:04 by enolbas           #+#    #+#              #
#    Updated: 2022/10/26 15:56:12 by enolbas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

SRCS_FOLDER	=	srcs
OBJS_FOLDER	=	objs
INC_FOLDER	=	includes

CC		:=	gcc
CFLAGS		:=	-Werror -Wextra -Wall -I$(INC_FOLDER)
LDFLAGS		:=	-fsanitize=address -g -fsanitize=leak
VFLAGS		:=	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --tool=helgrind

SRCS_BASE	=	\
			libft				\
			print				\
			parser				\
			getters				\
			setters				\
			ending				\
			monitor				\
			philos				\
			actions				\
			main				

SRCS		=	$(addsuffix .c, $(addprefix $(SRCS_FOLDER)/, $(SRCS_BASE)))
OBJS		=	$(addsuffix .o, $(addprefix $(OBJS_FOLDER)/, $(SRCS_BASE)))

$(OBJS_FOLDER)/%.o:		$(SRCS_FOLDER)/%.c
				mkdir -p $(dir $@)
				$(CC) $(CFLAGS) -c -o $@ $<

$(NAME):			$(OBJS)
				$(CC)  -o $(NAME) $(OBJS) -pthread

clean:
			rm -rf $(OBJS_FOLDER)

fclean:		clean
			rm $(NAME)

all:		$(NAME)

re:		fclean
		$(MAKE) all

.PHONY:		re fclean clean all
