# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zsoltani <zsoltani@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/02 18:14:13 by zsoltani          #+#    #+#              #
#    Updated: 2023/10/05 23:00:52 by zsoltani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	get_next_line.c \
	get_next_line_utils.c

BONUSSRC = ft_lstnew_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstsize_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstiter_bonus.c \

OBJ = ${SRC:.c=.o}

BONUSOBJ = ${BONUSSRC:.c=.o}

CC = gcc

RM = rm -f

HEADERS = libft.h

CFLAGS = -Wall -Wextra -Werror

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}


${NAME}:	${OBJ} ${HEADERS}
					@ar rc ${NAME} ${OBJ}
					@ranlib ${NAME}

all: ${NAME}

bonus: $ ${OBJ} ${BONUSOBJ} ${HEADERS}
					@ar rc ${NAME} ${OBJ} ${BONUSOBJ}
clean :
		${RM} ${OBJ} ${BONUSOBJ}

fclean : clean
	${RM} ${NAME}
re: fclean all

.PHONY : all bonus clean fclean re
