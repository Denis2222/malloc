# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/19 15:18:49 by dmoureu-          #+#    #+#              #
#    Updated: 2017/03/27 17:36:03 by dmoureu-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

EXTENSION	=	.so
SPACE		=	_
NAMESTD		=	libft_malloc
NAME		=	$(addprefix $(addprefix $(addprefix $(NAMESTD), $(SPACE)), $(HOSTTYPE)), $(EXTENSION))
NAMELINK	=	$(addprefix $(NAMESTD), $(EXTENSION))
NAMEBASE    =   $(shell basename $(NAME))
LENGTHNAME	=	`printf "%s" $(NAMEBASE) | wc -c`
MAX_COLS	=	$$(echo "$$(tput cols)-20-$(LENGTHNAME)"|bc)
CC			=	gcc
FLAGS		=	-fPIC -W -Wall -Wextra -Werror -g3
SRCDIR		=	src/
OBJDIR		=	.obj/
INCDIR		=	includes/
SRCBASE		=	\
				malloc.c \
				block.c \
				free.c \
				map.c \
				show_alloc.c \
				size.c \
				realloc.c

LIBFT = ./libft/libft.a
SRCS		=	$(addprefix $(SRCDIR), $(SRCBASE))
OBJS		=	$(addprefix $(OBJDIR), $(SRCBASE:.c=.o))

.SILENT:

all:$(NAME)

$(NAME):	$(OBJDIR) $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) -shared -o $(NAME) $(OBJS) -lft -L./libft/ -I $(INCDIR)
	ln -sf $(NAME) $(NAMELINK)
	echo "MAKE   [$(NAMEBASE)]"

$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(dir $(OBJS))

$(OBJDIR)%.o : $(SRCDIR)%.c | $(OBJDIR)
	$(CC) $(FLAGS) -MMD -c $< -o $@											\
		-I $(INCDIR)

$(LIBFT):
	@make -C libft
	@echo $(SRC_LIB_O)

clean:
	if [[ `rm -R $(OBJDIR) &> /dev/null 2>&1; echo $$?` == "0" ]]; then		\
		echo -en "CLEAN  "									\
		"$(NAMEBASE)";							\
	else																	\
		printf "\r";														\
	fi

fclean:		clean
	if [[ `rm $(NAME) &> /dev/null 2>&1; echo $$?` == "0" ]]; then			\
		echo -en "\rFCLEAN "									\
		"[\033[0m$(NAMEBASE)";							\
	else																	\
		printf "\r";														\
	fi
	rm -rf $(NAMELINK)
	make -C libft/ fclean

re:			fclean all

.PHONY:		fclean clean re

-include $(OBJS:.o=.d)

.PHONY: all clean fclean re
