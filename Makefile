##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

SERVER_DIR		:=	server
GUI_DIR			:=	gui
AI_DIR			:=	ai

SERVER_NAME		:=	zappy_server
GUI_NAME		:=	zappy_gui
AI_NAME			:=	zappy_ai

all: title zappy_server zappy_gui zappy_ai

zappy_server:
	@printf "\e[48;5;196m                COMPILING SERVER              \e[0m\n"
	@cmake $(SERVER_DIR) -B ./build/server && cmake --build ./build/server -j --target all
	@cp ./build/server/zappy_server .

zappy_gui:
	@printf "\e[48;5;196m                 COMPILING GUI                \e[0m\n"
	#@make -C $(CLIENT_DIR) all && cp -f $(CLIENT_DIR)/$(CLIENT_NAME) .

zappy_ai:
	@printf "\e[48;5;196m                 COMPILING AI                 \e[0m\n"
	#@make -C $(AI_DIR) all && cp -f $(AI_DIR)/$(AI_NAME) .

title:
	@printf "\e[48;5;235m                 -=[ Zappy ]=-                \e[0m\n"

clean:
	@printf "Not implemented\n"

fclean:
	@rm -f $(GUI_NAME)
	@rm -f $(SERVER_NAME)
	@rm -f $(CLIENT_NAME)

tests_run: title zappy_server
	@./build/server/unit_tests
	@gcovr build --exclude server/tests/



re: fclean all

.PHONY: zappy_server zappy_gui zappy_ai fclean title all re clean tests_run
