# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wjasmine <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/11 15:24:34 by wjasmine          #+#    #+#              #
#   Updated: 2022/05/19 21:18:34 by wjasmine         ###   ########.fr       # #
#                                                                              #
# **************************************************************************** #

NAME		= philo

INCLUDES	= includes/
HEADER		= includes/philo.h

DIR			=

FILES		= philo.c utils.c init.c \


SRCS		= $(addprefix $(DIR), $(FILES))

OBJS		= $(SRCS:%.c=%.o)

DS			= $(SRCS:%.c=%.d)

CC 			= cc
CFLAGS		= -Wall -Wextra -Werror -MMD #-pthread

.PHONY: 	all clean fclean re bonus

all:		$(NAME)


$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $@

%.o:		%.c Makefile
			$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

-include	$(DS)
#$(wildcard *.d)

clean:
			$(RM) $(OBJS) $(DS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all
