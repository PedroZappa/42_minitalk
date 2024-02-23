# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/18 11:49:03 by passunca          #+#    #+#              #
#    Updated: 2024/02/22 19:51:25 by passunca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                                NAMES & PATHS                                 #
#==============================================================================#

NAME_SERVER		= server
NAME_CLIENT		= client
UNAME 			= $(shell uname)
# Get current tmux esssion name
TMUX_SESSION	= $(shell tmux display-message -p '#S')

SRC_PATH	= src
INC_PATH	= inc
BUILD_PATH	= .build

LIBFT_PATH	= $(INC_PATH)/libft
LIBFT_ARC	= $(LIBFT_PATH)/libft.a

SRC_SERVER	= $(addprefix $(SRC_PATH)/, server.c ft_send.c ft_sigaction.c)
SRC_CLIENT	= $(addprefix $(SRC_PATH)/, client.c ft_send.c ft_sigaction.c)

OBJS_SERVER	= $(SRC_SERVER:$(SRC_PATH)/%.c=$(BUILD_PATH)/%.o)
OBJS_CLIENT	= $(SRC_CLIENT:$(SRC_PATH)/%.c=$(BUILD_PATH)/%.o)
DEPS		= $(OBJS:.o=.d)

TXT_TEST	= $(shell cat ./tests/500_w.txt)
EMOJI_TEST1	= $(shell cat ./tests/1000_emoji.txt)
EMOJI_TEST2	= $(shell cat ./tests/2000_emoji.txt)

SHELL := bash

#==============================================================================#
#                            FLAGS & CMDS                                      #
#==============================================================================#

CC		= cc

CFLAGS		= -Wall -Werror -Wextra
CFLAGS		+= -g

INC			= -I

AR			= ar rcs
RM			= rm -rf
MKDIR_P		= mkdir -p

MAKE		= make -C

#==============================================================================#
#                                  RULES                                       #
#==============================================================================#

##@ Minitalk Compilation Rules 🏗

all: $(BUILD_PATH) $(NAME_SERVER) $(NAME_CLIENT)	## Compile Minitalk

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c
	@echo -n "$(MAG)█$(D)"
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_PATH):
	$(MKDIR_P) $(BUILD_PATH)

$(NAME_SERVER): $(LIBFT_ARC) $(OBJS_SERVER)
	@echo "[$(YEL)Compiling Minitalk Server$(D)]"
	@echo -n "$(GRN)█$(D)"
	$(CC) $(CFLAGS) $(OBJS_SERVER) $(LIBFT_ARC) -o $(NAME_SERVER)

$(NAME_CLIENT): $(LIBFT_ARC) $(OBJS_CLIENT)
	@echo "[$(YEL)Compiling Minitalk Client$(D)]"
	@echo -n "$(GRN)█$(D)"
	$(CC) $(CFLAGS) $(OBJS_CLIENT) $(LIBFT_ARC) -o $(NAME_CLIENT)

$(LIBFT_ARC):
	$(MAKE) $(LIBFT_PATH) extra

bonus:			## Compile Minitalk with bonus features
	@echo "[$(YEL)Compiling Minitalk with bonus features$(D)]"
	make all
	@echo "[$(GRN)SUCCESS$(D) compiling $(MAG)minitalk with bonus!$(D) $(YEL)🖔$(D)]"

deps:			## Download/Update libft
	@if running test ! -d "$(LIBFT_PATH)"; then make get_libft; \
		else echo "$(YEL)[libft]$(D) folder found"; fi
	@make update_modules

-include $(DEPS)

get_libft:		## Get Libft module
	@echo "[$(CYA)Getting Libft submodule$(D)]"
	git clone git@github.com:PedroZappa/libft.git $(LIBFT_PATH)
	@echo "[$(GRN)Libft submodule successfully downloaded$(D)]"

update_modules:	## Update modules
	@echo "[$(CYA)Updating submodules$(D)]"
	git submodule init
	git submodule update --recursive --remote
	@echo "[$(GRN)Submodules successfully updated$(D)]"

##@ Test, Debug & Leak Check Rules 

leak: all			## Check for leaks w/ valgrind
	@valgrind -q --leak-check=full --show-leak-kinds=all \
		--suppressions=readline_supression ./$(NAME)

serve: all			## Run Server in new tmux pane
	tmux split-window -h "./server"
	sleep 1

running test: all			## Attach Clients to server in new tmux panes
	@echo "running test [1/3]"
	tmux split-window -v "./client 1788338 'running test 1'"
	sleep 1
	@echo "running test [2/3]"
	tmux split-window -v "./client 1788338 'running test 2'"
	sleep 1
	@echo "running test [3/3]"
	tmux split-window -v "./client 1788338 'running test 3'"

stress_test: all	## Attach Clients and stress running test
	@echo "running test [1/3]"
	tmux split-window -v "./client 1788338 '$(TXT_TEST)'" && \
	sleep 7
	@echo "running test [2/3]"
	tmux split-window -v "./client 1788338 '$(EMOJI_TEST1)'" && \
	sleep 7
	@echo "running test [3/3]"
	tmux split-window -v "./client 1788338 '$(EMOJI_TEST2)'"

##@ Clean-up Rules 󰃢

clean: 				## Remove object files
	@echo "[$(RED)Cleaning $(NAME) objects 󰃢$(D)]"
	$(RM) $(OBJS)
	@echo "[$(RED)Cleaning Libft objects 󰃢$(D)]"
	$(MAKE) $(LIBFT_PATH) clean
	@echo "[$(RED)Removing $(BUILD_PATH) 󰃢$(D)]"
	$(RM) $(BUILD_PATH)
	@echo "==> $(GRN)Object files successfully removed!$(D)\n"

fclean: clean	## Remove archives & executables
	@echo "[$(RED)Cleaning executable 󰃢$(D)]"
	$(RM) $(NAME_SERVER) $(NAME_CLIENT)
	$(MAKE) $(LIBFT_PATH) fclean
	@echo "==> $(GRN)$(NAME) Successfully removed!$(D)\n"

libclean: fclean	## Remove libft
	@echo "[$(RED)Cleaning libft 󰃢$(D)]"
	$(RM) $(LIBFT_PATH)
	@echo "==> $(GRN)libft successfully removed!$(D)\n"
	$(RM) $(INC_PATH)
	@echo "==> $(GRN)inc folder successfully removed!$(D)\n"

re: fclean all	## Purge and Recompile

##@ Help 󰛵

.PHONY: help
help: 			## Display this help page
	@awk 'BEGIN {FS = ":.*##"; \
			printf "\n=> Usage:\n\tmake $(GRN)<target>$(D)\n"} \
		/^[a-zA-Z_0-9-]+:.*?##/ { \
			printf "\t$(GRN)%-15s$(D) %s\n", $$1, $$2 } \
		/^##@/ { \
			printf "\n=> %s\n", substr($$0, 5) } ' Makefile

.PHONY: bonus deps get_libft update_modules leak serve test stress_test clean \
	fclean libclean re

#==============================================================================#
#                                  UTILS                                       #
#==============================================================================#

# Colors
#
# Run the following command to get list of available colors
# bash -c 'for c in {0..255}; do tput setaf $c; tput setaf $c | cat -v; echo =$c; done'
#
B  		= $(shell tput bold)
BLA		= $(shell tput setaf 0)
RED		= $(shell tput setaf 1)
GRN		= $(shell tput setaf 2)
YEL		= $(shell tput setaf 3)
BLU		= $(shell tput setaf 4)
MAG		= $(shell tput setaf 5)
CYA		= $(shell tput setaf 6)
WHI		= $(shell tput setaf 7)
GRE		= $(shell tput setaf 8)
BRED 	= $(shell tput setaf 9)
BGRN	= $(shell tput setaf 10)
BYEL	= $(shell tput setaf 11)
BBLU	= $(shell tput setaf 12)
BMAG	= $(shell tput setaf 13)
BCYA	= $(shell tput setaf 14)
BWHI	= $(shell tput setaf 15)
D 		= $(shell tput sgr0)
BEL 	= $(shell tput bel)
CLR 	= $(shell tput el 1)
