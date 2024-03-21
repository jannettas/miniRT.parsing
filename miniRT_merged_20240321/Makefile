# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zsoltani <zsoltani@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/20 17:58:32 by ebennace          #+#    #+#              #
#    Updated: 2024/03/21 21:32:57 by zsoltani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

# ==== External folders and libraries ==== #

LIBFT_DIR   = ./src/lib/libft/
LIBFT		= $(LIBFT_DIR)/libft.a
MINLBX_DIR = ./src/lib/minilibx/
MINLBX	= = $(MINLBX_DIR)/libmlx.a

# ==== Project's files ==== #
SRCS       = 		src/minirt.c \
					src/scene.c \
					src/render.c \
					src/camera.c \
					src/ray_op.c \
					src/ray_hits.c \
					src/vector_op.c \
					src/matrix_op.c \
					src/shapes.c \
					src/color.c \
					src/light.c \
					src/parser_utils_1.c \
					src/parser_utils_2.c \
					src/parse_scene.c \
					src/parse_shapes.c \
					src/parse_light.c \
					
# ==== Source: object files ==== #
OBJS = $(SRCS:.c=.o)

# ==== Template ==== #
TEMPLATE = src/header/miniRT_header.txt
# TEMPLATE = 	

# ==== Debug && Leak ==== #
SANITIZE       = -fsanitize=address
LEAKS          = -fsanitize=leak
# SANITIZE       = 
# LEAKS       = 


DEBUGGER       = lldb

# ==== Remove ==== #
RM_FILE = /bin/rm -rf

# ==== Compiling ==== #
CC              ?= gcc
FLAGS           = -g3
FLAGS           += -Wall -Werror -Wextra
FLAGS           += $(SANITIZE)


LNK  = -L $(MINLBX_DIR) -lmlx -framework OpenGL -framework AppKit
MAKE            = make -s

# === Convert all .c to .o with flags and header === # 
all: $(NAME)

${OBJS}: %.o: %.c
	@echo "...Compiling $<"
	@$(CC) $(FLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	@echo "==== Compiling libft ===="
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "==== Compiling minilibx ===="
	@$(MAKE) -C $(MINLBX_DIR)
	@echo "==== Compiling $(NAME) ===="
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LNK) 
	@echo "==== $(NAME) is ready! ===="
	@cat "$(TEMPLATE)"

$(MINLBX):
	@make -C $(MINLBX_DIR)

ENTITLEMENTS = entitlements.plist

sign: $(NAME)
	@echo "==== Signing $(NAME) for profiling ===="
	@echo '<?xml version="1.0" encoding="UTF-8"?>' > $(ENTITLEMENTS)
	@echo '<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "https://www.apple.com/DTDs/PropertyList-1.0.dtd">' >> $(ENTITLEMENTS)
	@echo '<plist version="1.0">' >> $(ENTITLEMENTS)
	@echo '    <dict>' >> $(ENTITLEMENTS)
	@echo '        <key>com.apple.security.get-task-allow</key>' >> $(ENTITLEMENTS)
	@echo '        <true/>' >> $(ENTITLEMENTS)
	@echo '    </dict>' >> $(ENTITLEMENTS)
	@echo '</plist>' >> $(ENTITLEMENTS)
	@codesign -s - -v -f --entitlements $(ENTITLEMENTS) $(NAME)
	@rm -f $(ENTITLEMENTS)


clean:
	@echo "==== Cleaning all LIBFT .o files ===="
	@$(MAKE) clean -C $(LIBFT_DIR)
	@echo "==== Cleaning all MINILIBX .o files ===="
	@$(MAKE) clean -C $(MINLBX_DIR)
	@echo "==== Cleaning all MINI-RT .o files ===="
	@$(RM_FILE) $(OBJS)

fclean: clean
	@echo "==== Full cleaning LIBFT ===="
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@echo "==== Full cleaning $(NAME) ===="
	@$(RM_FILE) $(NAME)

debug : $(OBJS)
	@echo "==== Debug mode ===="
	@$(CC) $(OBJS) $(FLAGS) $(READLINE) $(SANITIZE) $(LIBFT) -o $(NAME)
	$(DEBUGGER) $(NAME)
	@cat "$(TEMPLATE)"

sanitize :	$(OBJS)
	@echo "==== Sanitize mode ===="
	@$(CC) $(OBJS) $(FLAGS) $(READLINE) $(SANITIZE) $(LIBFT) -o $(NAME)
	@cat "$(TEMPLATE)"

leak :	$(OBJS)
		@echo "==== Leaks mode ===="
		@$(CC) $(OBJS) $(FLAGS) $(READLINE) $(LEAKS) $(LIBFT) -o $(NAME)
		@cat "$(TEMPLATE)"

re: fclean all

.PHONY: all clean fclean debug sanitize leak re
