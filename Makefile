CC = cc
FLAGS = -Wall -Wextra -Werror -fsanitize=address
NAME = minishell
DIRBUILD = objdir
INC  = -I ./includes
HEADERS = includes/minishell.h
LIBFT = includes/libft/libft.a
Exec = $(addprefix execution/, execution error utils utils2 execution_utils execution_utils2 execution_utils3)
Builtins = $(addprefix execution/builtins/, builtin cd echo env exit export export_utils export_utils2 pwd unset unset_utils)
SRC =  $(addprefix parser/, cmd_creation cmd_utils_ cmd_utils creat_cmds enviroment\
error_free execution_utils execution_utils2 finding_ finding\
get_tokens__ get_tokens_ heredoc_utils heredoc_utils2 heredoc in_out_file_managment\
in_out_utils in_out_utils2 joining list_manupulation pipe_management removing signals\
syntax_analyzer token expantion) $(Exec) $(Builtins) main

OBJ = $(addprefix $(DIRBUILD)/, $(SRC:=.o))

all : $(NAME)
$(NAME) : $(OBJ) $(LIBFT) $(HEADERS)
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(READ) -lreadline $(LDFLAGS)  $(LIBFT)

$(LIBFT) :
	@make -C includes/libft
	
$(DIRBUILD)/%.o : source/%.c $(HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(INC) $(CPPFLAGS) $(RL_INCLUDE) -c $< -o $@
clean :
	@rm -rf $(DIRBUILD)
	@make clean -C includes/libft

fclean : clean
	@rm -rf $(NAME)
	@make fclean -C includes/libft
	@echo "\033[0;95m Everything is fcleaned in minishell!\033[m"

re : fclean all

.PHONY : re fclean clean all
