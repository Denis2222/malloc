# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/19 15:18:49 by dmoureu-          #+#    #+#              #
#    Updated: 2017/03/20 00:24:00 by dmoureu-         ###   ########.fr        #
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
				realloc.c \
				print_memory.c

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
	rm -rf test
	make -C libft/ fclean

test:
	cp $(NAME) libftmalloc.a
	gcc -o test0 tests/test0.c -I includes/ -L . -lft_malloc
	gcc -o test1 tests/test1.c -I includes/ -L . -lft_malloc
	gcc -o test2 tests/test2.c -I includes/ -L . -lft_malloc
	gcc -g -o test3 tests/test3.c -I includes/ -L . -lft -L./libft/ -lft_malloc
	gcc -g -o test3bis tests/test3bis.c -I includes/ -L . -lft_malloc
	gcc -o test4 tests/test4.c -I includes/ -L . -lft_malloc
	gcc -o test5 tests/test5.c -I includes/ -L . -lft_malloc
	echo "Test generated\n"

testdone:
	make re && make test && /usr/bin/time -l ./test0 && /usr/bin/time -l ./test3

re:			fclean all

.PHONY:		fclean clean re

-include $(OBJS:.o=.d)

.PHONY: all clean fclean re
