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
#                                  MAKE CONFIG                                 #
#==============================================================================#

SHELL := bash

#==============================================================================#
#                                     NAMES                                    #
#==============================================================================#

USER			= passunca
NAME_SERVER		= server
NAME_CLIENT		= client
UNAME 			= $(shell uname)

### Message Vars
_SUCCESS 		= [$(GRN)SUCCESS$(D)]
_INFO 			= [$(BLU)INFO$(D)]
_NORM 			= [$(YEL)Norminette$(D)]
_NORM_SUCCESS 	= $(GRN)=== OK:$(D)
_NORM_INFO 		= $(BLU)File no:$(D)

#==============================================================================#
#                                    PATHS                                     #
#==============================================================================#

SRC_PATH	= src
INC_PATH	= inc
BUILD_PATH	= .build

SRC_SERVER	= $(addprefix $(SRC_PATH)/, server.c ft_send.c ft_sigaction.c)
SRC_CLIENT	= $(addprefix $(SRC_PATH)/, client.c ft_send.c ft_sigaction.c)

OBJS_SERVER	= $(SRC_SERVER:$(SRC_PATH)/%.c=$(BUILD_PATH)/%.o)
OBJS_CLIENT	= $(SRC_CLIENT:$(SRC_PATH)/%.c=$(BUILD_PATH)/%.o)
DEPS		= $(OBJS:.o=.d)

LIBFT_PATH	= $(INC_PATH)/libft
LIBFT_ARC	= $(LIBFT_PATH)/libft.a

TXT_TEST1	= $(shell cat ./tests/bit_3000.txt)
TXT_TEST2	= $(shell cat ./tests/bit_7000.txt)
TXT_TEST3	= $(shell cat ./tests/bit_9999.txt)
EMOJI_TEST1	= $(shell cat ./tests/emoji_1000.txt)
EMOJI_TEST2	= $(shell cat ./tests/emoji_2000.txt)
EMOJI_TEST3	= $(shell cat ./tests/emoji_3000.txt)

#==============================================================================#
#                              COMPILER & FLAGS                                #
#==============================================================================#

CC		= cc

CFLAGS		= -Wall -Werror -Wextra
CFLAGS		+= -g

INC			= -I

#==============================================================================#
#                                COMMANDS                                      #
#==============================================================================#

AR			= ar rcs
RM			= rm -rf
MKDIR_P		= mkdir -p

MAKE		= make -C

#==============================================================================#
#                                  RULES                                       #
#==============================================================================#

##@ minitalk Compilation Rules 🏗

all: $(BUILD_PATH) deps $(NAME_SERVER) $(NAME_CLIENT)	## Compile minitalk

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c
	@echo -n "$(MAG)█$(D)"
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_PATH):
	$(MKDIR_P) $(BUILD_PATH)

$(NAME_SERVER): $(LIBFT_ARC) $(OBJS_SERVER)
	@echo "[$(YEL)Compiling minitalk Server$(D)]"
	@echo -n "$(GRN)█$(D)"
	$(CC) $(CFLAGS) $(OBJS_SERVER) $(LIBFT_ARC) -o $(NAME_SERVER)
	@echo "[$(_SUCCESS) compiling $(MAG)server!$(D) $(YEL)🖔$(D)]"

$(NAME_CLIENT): $(LIBFT_ARC) $(OBJS_CLIENT)
	@echo "[$(YEL)Compiling minitalk Client$(D)]"
	@echo -n "$(GRN)█$(D)"
	$(CC) $(CFLAGS) $(OBJS_CLIENT) $(LIBFT_ARC) -o $(NAME_CLIENT)
	@echo "[$(_SUCCESS) compiling $(MAG)client!$(D) $(YEL)🖔$(D)]"

$(LIBFT_ARC):
	$(MAKE) $(LIBFT_PATH) extra

bonus:			## Compile minitalk with bonus features
	@echo "[$(YEL)Compiling minitalk with bonus features$(D)]"
	make all
	@echo "[$(_SUCCESS) compiling $(MAG)minitalk with bonus!$(D) $(YEL)🖔$(D)]"

deps: 			## Download/Update libft
	@if test ! -d "$(LIBFT_PATH)"; then make get_libft; \
		else echo "$(YEL)[libft]$(D) folder found"; fi
	@echo " $(RED)$(D) [$(GRN)Nothing to be done!$(D)]"

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

valgrind: all			## Run Server w/ Valgrind
	tmux split-window -h "valgrind --leak-check=full --show-leak-kinds=all ./server"
	sleep 0.5
	./scripts/get-valgrind-pid.sh > server.pid

norm: 		## Run norminette test
	@printf "${_NORM}\n"
	@printf "${_NORM_INFO} "
	@norminette $(SRC_PATH) | wc -l
	@norminette $(SRC_PATH)
	@printf "${_NORM_SUCCESS} "
	@norminette $(SRC_PATH) | grep -wc "OK"

serve: all			## Run Server in new tmux pane
	tmux split-window -h "./server"
	sleep 0.5
	./scripts/get-server-pid.sh > server.pid

test: all			## Attach Clients to server in new tmux panes
	@echo "$(YEL)running test [1/3]$(D)"
	tmux split-window -v "./client $$(cat server.pid) 'running test 1'"
	sleep 1
	@echo "$(YEL)running test [2/3]$(D)"
	tmux split-window -v "./client $$(cat server.pid) 'running test 2'"
	sleep 1
	@echo "$(YEL)running test [3/3]$(D)"
	tmux split-window -v "./client $$(cat server.pid) 'running test 3'"

stress_test: all	## Attach Clients and stress running test
	tmux split-window -v "./client $$(cat server.pid) '$(TXT_TEST1)'" ; \
	echo "$(YEL)running text test [1/3]$(D)" && \
	sleep 7
	tmux split-window -v "./client $$(cat server.pid) '$(TXT_TEST2)'" ; \
	echo "$(YEL)running text test [2/3]$(D)" && \
	sleep 12
	tmux split-window -v "./client $$(cat server.pid) '$(TXT_TEST3)'" ; \
	echo "$(YEL)running text test [3/3]$(D)" && \
	sleep 15
	tmux split-window -v "./client $$(cat server.pid) '$(EMOJI_TEST1)'" ; \
	echo "$(YEL)running 😎emoji😎 test [1/3]$(D)" && \
	sleep 11
	tmux split-window -v "./client $$(cat server.pid) '$(EMOJI_TEST2)'" ; \
	echo "$(YEL)running 😎emoji😎 test [2/3]$(D)" && \
	sleep 20
	tmux split-window -v "./client $$(cat server.pid) '$(EMOJI_TEST3)'" ; \
	echo "$(YEL)running 😎emoji😎 test [3/3]$(D)"

##@ Clean-up Rules 󰃢

clean: 				## Remove object files
	@echo "[$(RED)Cleaning $(NAME) objects 󰃢$(D)]"
	$(RM) $(OBJS)
	@echo "[$(RED)Cleaning Libft objects 󰃢$(D)]"
	$(MAKE) $(LIBFT_PATH) clean
	@echo "[$(RED)Removing $(BUILD_PATH) 󰃢$(D)]"
	$(RM) $(BUILD_PATH)
	@echo "[$(GRN)Object files successfully removed!$(D)]\n"
	$(RM) server.pid
	@echo "[$(GRN)Server pid file successfully removed!$(D)]\n"

fclean: clean	## Remove archives & executables
	@echo "[$(RED)Cleaning executable 󰃢$(D)]"
	$(RM) $(NAME_SERVER) $(NAME_CLIENT)
	$(MAKE) $(LIBFT_PATH) fclean
	@echo "[$(GRN)$(NAME) Successfully removed!$(D)i]\n"

libclean: fclean	## Remove libft
	@echo "[$(RED)Cleaning libft 󰃢$(D)]"
	$(RM) $(LIBFT_PATH)
	@echo "[$(GRN)libft successfully removed!$(D)]\n"
	$(RM) $(INC_PATH)
	@echo "[$(GRN)inc folder successfully removed!$(D)]\n"

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
