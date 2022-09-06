NAME		=	philo

SRCS_FOLDER	=	srcs
OBJS_FOLDER	=	objs
INC_FOLDER	=	inc

CC		:=	gcc
CFLAGS		:=	-Werror -Wextra -Wall -I$(INC_FOLDER)
LDFLAGS		:=	-fsanitize=address -g -fsanitize=leak

SRCS_BASE	=	\
			libft				\
			print				\
			free				\
			parser				\
			thread				\
			philos				\

SRCS		=	$(addsuffix .c, $(addprefix $(SRCS_FOLDER)/, $(SRCS_BASE)))
OBJS		=	$(addsuffix .o, $(addprefix $(OBJS_FOLDER)/, $(SRCS_BASE)))

$(OBJS_FOLDER)/%.o:		$(SRCS_FOLDER)/%.c
				mkdir -p $(dir $@) 
				$(CC) $(CFLAGS) -c -o $@ $<

$(NAME):			$(OBJS)
				$(CC)  -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
			rm $(OBJS)

fclean:			clean
			rm $(NAME)
			rmdir $(OBJS_FOLDER)

all:		$(NAME)

re:		fclean
		$(MAKE) all

.PHONY:		re fclean clean all
