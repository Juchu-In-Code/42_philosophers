# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 13:32:47 by jgalizio          #+#    #+#              #
#    Updated: 2025/05/15 15:38:05 by jgalizio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo
CFLAGS			= -Wextra -Wall -Werror
# CFLAGS			+= -fsanitize=thread -g
RM				= rm -rf

BASE_DIR		= ./srcs-base
BUILD_DIR		= ./.build
BUILD_BASE_DIR	= $(BUILD_DIR)/base

BASE_TARGET		= $(BUILD_BASE_DIR)/.base
BASE_HEADERS	= $(BASE_DIR)/philo.h

BASE_INC		= -I $(BASE_DIR)

LIB_FLAGS		= -pthread

BASE_SRCS		= $(addprefix $(BASE_DIR)/,\
					a_main.c \
					b_setup_args.c \
					b_setup_program.c \
					b_setup_threads.c \
					c_monitor_routines.c \
					c_philo_routines.c \
					d_tableflip.c \
					u_error_utils.c \
					u_print_utils.c \
					u_time_utils.c \
					u_verify_args_utils.c \
					)

BASE_OBJS		= $(BASE_SRCS:$(BASE_DIR)/%.c=$(BUILD_BASE_DIR)/%.o)

all: $(NAME)

$(NAME): $(BASE_TARGET)

$(BASE_TARGET): $(BASE_OBJS)
	@echo "Creating Philo..."
	@$(CC) $(CFLAGS) $(BASE_OBJS) $(BASE_INC) $(LIB_FLAGS) -o $(NAME)
	@touch $(BASE_TARGET)
	@echo "Done! :D"

$(BUILD_BASE_DIR)/%.o: $(BASE_DIR)/%.c $(BASE_HEADERS)
	@echo "compiling $@..."
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< $(BASE_INC) -o $@


clean:
	@echo "Cleaning objects..."
	@$(RM) $(BASE_OBJS) $(BASE_TARGET)
	@echo "Done! :D"

fclean: clean
	@echo "Cleaning all..."
	@$(RM) $(BUILD_DIR)
	@$(RM) $(NAME)
	@echo "Done! :D"

re: fclean all

rebonus: fclean

.PHONY: all clean fclean re
