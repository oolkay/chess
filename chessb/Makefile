NAME	:= chess

CC		:= c++ 
FLAGS	= #-Wall -Wextra -Werror

SRCDIR	:= src
SRC		:= $(shell find $(SRCDIR) -name '*.cpp')

OBJDIR	:= ./objectives
OBJ		:= $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(CFLAGS) $(OBJ) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(FLAGS) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)

fclean:
	@rm -rf $(OBJDIR)
	@rm -f $(NAME)

re:	fclean all

PHONY: all clean fclean re