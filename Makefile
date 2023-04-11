CC = cc
FLAGS = -Wall -Wextra -Werror -fsanitize=address
NAME = minishell
DIRBUILD = objdir
INC  = -I ./includes
HEADERS = includes/minishell.h
LIBFT = includes/libft/libft.a
Exec = $(addprefix execution/, execution error utils utils2)
Builtins = $(addprefix execution/builtins/, builtin cd echo env exit export pwd unset)
SRC =  $(addprefix parser/, cmd_creation cmd_managment cmd_utils_ cmd_utils creat_cmds enviroment\
error_free execution_built execution_utils execution_utils2 execution finding_ finding\
get_tokens__ get_tokens_ heredoc_utils heredoc_utils2 heredoc in_out_file_managment\
in_out_utils joining list_manupulation pipe_asign pipe_management removing signals\
suite_syntax syntax_analyzer token expantion suite_syntax) $(Exec) $(Builtins) main

OBJ = $(addprefix $(DIRBUILD)/, $(SRC:=.o))

all : $(NAME)
$(NAME) : $(OBJ) $(LIBFT)
	@$(CC) $(FLAGS) $^ -o $(NAME) -lreadline  $(LDFLAGS)  $(LIBFT) -fsanitize=address

$(LIBFT) :
	@make -C includes/libft
	
$(DIRBUILD)/%.o : source/%.c $(HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(INC) $(FLAGS) -c $< -o $@ 
clean :
	@rm -rf $(DIRBUILD)
	@make clean -C includes/libft

fclean : clean
	@rm -rf $(NAME)
	@make fclean -C includes/libft
	@echo "\033[0;95m Everything is fcleaned in minishell!\033[m"

re : fclean all

.PHONY : re fclean clean all
