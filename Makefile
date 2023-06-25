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

documentation:
	-@git clone https://github.com/jothepro/doxygen-awesome-css.git ./doxygen/theme/doxygen-awesome \
		&& cd ./doxygen/theme/doxygen-awesome && git checkout v2.2.0
	@doxygen ./Doxyfile

zappy_server:
	@printf "\e[48;5;196m                COMPILING SERVER              \e[0m\n"
	@cmake $(SERVER_DIR) -B ./build/server && cmake --build ./build/server -j --target all
	@cp ./build/$(SERVER_DIR)/$(SERVER_NAME) .

zappy_gui:
	@printf "\e[48;5;196m                 COMPILING GUI                \e[0m\n"
	@cmake $(GUI_DIR) -B ./build/$(GUI_DIR) && cmake --build ./build/$(GUI_DIR) -j --target all
	@cp ./build/$(GUI_DIR)/$(GUI_NAME) .
	@cp ./gui/config.cfg .
	@cp -r ./gui/assets/ .

zappy_ai:
	@printf "\e[48;5;196m                 COMPILING AI                 \e[0m\n"
	touch ./$(AI_NAME)
	echo -n "cd ./ai && " > ./$(AI_NAME)
	cat ./$(AI_DIR)/$(AI_NAME) >> ./$(AI_NAME)

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
