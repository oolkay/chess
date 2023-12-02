NAME	:= chess
CC		:= c++ 
FLAGS	= -Wall -Wextra -Werror
SRCDIR	:= src
SRC		:= $(shell find $(SRCDIR) -name '*.cpp')
OBJDIR	:= ./objectives
OBJ		:= $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: student $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(CFLAGS) $(OBJ) -o $@
	@echo "${MAGENTA}Compilation has finished succesfully${DEFAULT}"
	@echo "${GREEN}${NAME} IS READY!!${DEFAULT}"

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(FLAGS) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)
	@echo "${RED}Object files are being deleted${DEFAULT}"

fclean: clean
	@rm -f $(NAME)
	@echo "${RED}Executable file is being deleted${DEFAULT}"

re:	fclean all

PHONY: all clean fclean re

student:
	@echo "${CYAN}Name:   Omer Faruk Olkay${DEFAULT}"
	@echo "${CYAN}Mail:   o.olkay2021@gtu.edu.tr${DEFAULT}"
	@echo "${CYAN}Number: 210104004039${DEFAULT}"
	@echo "${CYAN}Have a nice day${DEFAULT}"
	


#		COLORS
DEFAULT = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m