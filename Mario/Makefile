NAME = mario
SRC	= Main.cpp Game.cpp Object.cpp Mario.cpp Turtle.cpp ScoreBoard.cpp ObjectNode.cpp
OBJ = $(SRC:.cpp=.o)
RM = rm -rf
CC = g++
FLAGS = -I/opt/homebrew/Cellar/sfml/2.5.1_2/include -lsfml-graphics -lsfml-window -lsfml-system -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib

#colors
GREEN		=	\e[92;5;118m
YELLOW		=	\e[93;5;226m
GRAY		=	\e[33;2;37m
RESET		=	\e[0m
CURSIVE		=	\e[33;3m

all:		$(NAME)

$(NAME):	$(OBJ)
			@$(CC) $(SRC) $(FLAGS) -o $(NAME)
			@printf "$(GREEN) - Executed$(RESET)\n"

clean:
			@$(RM) $(OBJ)
			@printf	"$(YELLOW) - Deleted Object Files $(RESET)\n"

fclean:		clean
			@$(RM) $(NAME)
			@printf	"$(YELLOW) - Deleted Program$(RESET)\n"

re:			fclean all

run:		all
			./$(NAME)