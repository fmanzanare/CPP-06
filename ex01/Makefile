# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/28 15:14:43 by fmanzana          #+#    #+#              #
#    Updated: 2023/07/28 16:50:32 by fmanzana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = serialization

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS =	main.cpp

OBJS = $(SRCS:.cpp=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Serialization compiled!!"

%.o:	%.cpp
	@$(CC) $(CFLAGS) -c $<

clean:
	@rm -f $(OBJS)

fclean:	clean
	@rm -f $(NAME)
	@echo "Everything cleaned!!"

re:		fclean all

.PHONY: all clean fclean re
