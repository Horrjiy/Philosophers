# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/04 17:14:53 by mpoplow           #+#    #+#              #
#    Updated: 2025/04/04 18:47:56 by mpoplow          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= philo

CFLAGS	:= -Wall -Wextra -Werror -MMD
# -fsanitize=address -g

# *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	#
# 	FILES																		#
# *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	#

CFILES	:= _main_philo.c argument_validity.c linkedlist.c 

OFILES	= $(addprefix O_D_FILES/, $(notdir $(CFILES:.c=.o)))
DFILES	= $(addprefix O_D_FILES/, $(notdir $(CFILES:.c=.d)))

# *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	#
# 	RULES																		#
# *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	#

all: $(NAME)

$(NAME): $(OFILES) $(DFILES)
	@$(CC) $(OFILES) -o $(NAME)
	@echo "\033[1;32mCREATE PROGRAM: philo\033[0m"

O_D_FILES/%.o: %.c | O_D_FILES
	@$(CC) $(CFLAGS) -MMD -MP -g -c $< -o $@

O_D_FILES:
	@mkdir -p $@

clean:
	@echo "\033[1;33mCLEAN philo\033[0m"
	@rm -f $(OFILES) $(DFILES)
	@rm -rf O_D_Files

fclean: clean
	@echo "\033[1;33mREMOVE PROGRAM: philo\033[0m"
	@rm -f $(NAME)

re: clean all

prep: fclean all
	make clean

.SILENT:  $(OFILES) $(DFILES)
.PHONY: all clean fclean re prep