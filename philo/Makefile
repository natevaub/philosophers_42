# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nvaubien <nvaubien@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/21 13:28:18 by nvaubien          #+#    #+#              #
#    Updated: 2023/06/28 10:07:57 by nvaubien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= gcc
CFLAGS			= -g -pthread -fsanitize=thread -Wall -Wextra -Werror
NAME			= philo
NAME_BONUS		= philo_bonus
SRCS_PATH		= ./srcs/
INCLUDES_DIR	= ./includes/
INCLUDES		= -I$(INCLUDES_DIR)

SOURCES			=	checks.c					\
					init.c						\
					main.c						\
					memory.c					\
					philo.c						\
					state.c						\
					utils.c						\

OBJS_DIRECTORY	= objs/
OBJS_LIST		= $(patsubst %.c, %.o, $(SOURCES))
OBJS			= $(addprefix $(OBJS_DIRECTORY), $(OBJS_LIST))
HEADER_LIST		= philo.h
HEADER_FILES	= $(addprefix $(INCLUDES_DIR), $(HEADER_LIST))

all: $(NAME)

$(OBJS_DIRECTORY)%.o: $(SRCS_PATH)%.c $(HEADER_FILES)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) -o $(NAME)

clean:
	rm -rf $(OBJS_DIRECTORY)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
