# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vielblin <vielblin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/22 11:32:48 by vielblin          #+#    #+#              #
#    Updated: 2025/10/01 17:33:02 by vielblin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
FLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address
LIBS = -lreadline

INCLUDES = -I includes/

SRCS_DIR = srcs/
OBJS_DIR = objects/

FILES = main parsing

GC_FILES = gc_malloc gc_clear gc_addback gc_init_free
GC_DIR = gc/
GC = $(addsuffix .c, $(GC_FILES))
GC_PREF = $(addprefix $(SRCS_DIR)$(GC_DIR), $(GC))

LIBFT_FILES = ft_free ft_memset get_next_line get_next_line_utils ft_putstr_fd \
			ft_substr ft_split ft_strcmp ft_atoi
LIBFT_DIR = libft/
LIBFT = $(addsuffix .c, $(LIBFT_FILES))
LIBFT_PREF = $(addprefix $(SRCS_DIR)$(LIBFT_DIR), $(LIBFT))

SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES))) $(GC_PREF) $(LIBFT_PREF)

OBJS = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(INCLUDES) -g -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJS) $(LIBS) -g -o $(NAME)
	@echo "Program compiled"

all: $(NAME)

clean:
	@rm -rf $(OBJS_DIR)
	@echo "Removing objects"

fclean: clean
	@rm -f $(NAME)
	@echo "Cleaning all"

re: fclean all

.PHONY: all clean fclean re