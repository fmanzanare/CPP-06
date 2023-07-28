# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/28 17:02:36 by fmanzana          #+#    #+#              #
#    Updated: 2023/07/28 18:25:10 by fmanzana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = real_type

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS =	Base.cpp\
		main.cpp

OBJS = $(SRCS:.cpp=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Real type compiled!!"

%.o:	%.cpp
	@$(CC) $(CFLAGS) -c $<

clean:
	@rm -f $(OBJS)

fclean:	clean
	@rm -f $(NAME)
	@echo "Everything cleaned!!"

re:		fclean all

.PHONY: all clean fclean re
