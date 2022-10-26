# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: enolbas <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 13:30:04 by enolbas           #+#    #+#              #
#    Updated: 2022/10/26 13:43:53 by enolbas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

SRCS_FOLDER	=	srcs
OBJS_FOLDER	=	objs
INC_FOLDER	=	includes
LIB_DIR = ft_printf

CC		:=	gcc
CFLAGS		:=	-Werror -Wextra -Wall -I$(INC_FOLDER) -I$(LIB_DIR)
LDFLAGS		:=	-fsanitize=address -g -fsanitize=leak

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
				make -C $(LIB_DIR) --silent
				$(CC)  -o $(NAME) $(OBJS) -pthread -L $(LIB_DIR) -lftprintf

clean:
			make -C $(LIB_DIR) clean --silent
			rm -rf $(OBJS_FOLDER)

fclean:		clean
			make -C $(LIB_DIR) fclean --silent
			rm $(NAME)

all:		$(NAME)

re:		fclean
		$(MAKE) all

.PHONY:		re fclean clean all
