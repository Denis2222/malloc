# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/19 15:18:49 by dmoureu-          #+#    #+#              #
#    Updated: 2017/04/17 17:27:11 by dmoureu-         ###   ########.fr        #
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
	make -C libft/ clean
	rm ./test* &> /dev/null 2>&1;echo "clean done"
 
fclean:		clean
	if [[ `rm $(NAME) &> /dev/null 2>&1; echo $$?` == "0" ]]; then			\
		echo -en "\rFCLEAN "									\
		"[\033[0m$(NAMEBASE)";							\
	else																	\
		printf "\r";														\
	fi
	rm -rf ./libft_malloc*
	make -C libft/ fclean

re:			fclean all

RUN = ./run.sh
TIME = /usr/bin/time -l
INCH = -I includes/ -L . -lft_malloc -lft -L./libft/
SEE = 2>&1 | grep "page reclaims"


test0t:
	echo "test0:"
	gcc -o test0 ./tests/test0.c
	echo "real:"
	$(TIME) ./test0 $(SEE)
	echo "inject:"
	$(RUN) $(TIME) ./test0 $(SEE)

test1t:
	echo "test1:"
	gcc -o test1 ./tests/test1.c
	echo "real:"
	$(TIME) ./test1 $(SEE)
	echo "inject:"
	$(RUN) $(TIME) ./test1 $(SEE)
	echo "	test0"
	$(RUN) $(TIME) ./test0 $(SEE)

test2t:
	echo "test2:"
	gcc -o test2 ./tests/test2.c
	$(RUN) $(TIME) ./test2 $(SEE)
	echo "test1:"
	$(RUN) $(TIME) ./test1 $(SEE)
	echo "test0:"
	$(RUN) $(TIME) ./test0 $(SEE)

test3t:
	gcc -o test3 ./tests/test3.c
	@echo "TEST3:"
	@echo "malloc system:"
	./test3
	@echo "inject malloc"
	$(RUN) ./test3
	gcc -o test3bis ./tests/test3bis.c
	@echo "TEST3bis:"
	@echo "malloc system:"
	./test3bis
	@echo "inject malloc"
	$(RUN) ./test3bis

test4t:
	echo "test4:"
	gcc -o test4 ./tests/test4.c
	echo "inject:"
	$(RUN) ./test4
	echo "system failure:"
	./test4

test5t:
	echo "\nsubject exemple:\n"
	gcc -o test5 ./tests/test5.c $(INCH)
	./test5
	echo "\n\nspecial exemple:\n"
	gcc -o test6 ./tests/test6.c $(INCH)
	./test6

-include $(OBJS:.o=.d)

.PHONY: all clean fclean re
