# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wjasmine <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/11 15:24:34 by wjasmine          #+#    #+#              #
#   Updated: 2022/06/27 08:52:52 by wjasmine         ###   ########.fr       # #
#                                                                              #
# **************************************************************************** #

NAME		= philo_bonus

INCLUDES	= includes/
HEADER		= includes/philo_bonus.h

DIR			=

FILES		= philo_bonus.c utils_bonus.c init_bonus.c time_management_bonus.c routine_bonus.c clear_bonus.c\


SRCS		= $(addprefix $(DIR), $(FILES))

OBJS		= $(SRCS:%.c=%.o)

DS			= $(SRCS:%.c=%.d)

CC 			= cc
CFLAGS		= -Wall -Wextra -Werror -MMD
#CFLAGS		= -Wall -Wextra -Werror -MMD -fsanitize=thread

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
