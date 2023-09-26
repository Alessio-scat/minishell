.PHONY:     			all $(NAME) clear mkbuild lib clean fclean re

NAME					= minishell

BUILD_DIR				= build/

HEADER_DIR				= header/
HEADER_FILE				= minishell.h

DIR						= src/
SRC			 			= main.c \
							builtins/exit/exit_utils.c \
							builtins/exit/exit.c \
							builtins/pwd.c builtins/free_cd.c builtins/cd_utils.c builtins/builtin.c builtins/newecho.c builtins/cd.c builtins/env.c builtins/export/export.c builtins/export/export2.c builtins/export/utils_export.c builtins/export/free_export.c builtins/unset.c\
							utils/lst.c \
							utils/fuction_utils.c \
							utils/list_parsing.c \
							utils/free.c \
							utils/free_all.c \
							exec/exec.c exec/utils/error_message.c exec/utils/malloc_error.c exec/utils/free_env.c exec/utils/free_exec.c exec/init_exec.c exec/exec_pipe.c exec/env.c exec/fill_lst.c exec/lst.c exec/path.c exec/process_bonus.c exec/utils/utils.c exec/open_fd.c\
							parsing/parsing.c \
							parsing/parsepipe.c \
							parsing/redirection/redirs.c \
							parsing/redirection/get_here_doc.c \
							parsing/redirection/get_outfile.c \
							parsing/redirection/get_infile.c \
							parsing/quote.c \
							parsing/verif_builtins.c \
							parsing/init.c \
							parsing/index_redir/indexage_redir.c \
							parsing/index_redir/fill_tab_simple.c \
							parsing/index_redir/fill_tab.c \
							parsing/index_redir/index_utils.c \
							parsing/create_node.c \
							signals/signal.c \
							parsing/err_syntax/err_syntax.c \
							parsing/err_syntax/err_msg.c \
							parsing/err_syntax/check_syntax.c \
							parsing/utils_pars.c \
							parsing/env_var/d_questioning.c \
							parsing/env_var/dollar_special.c \
							parsing/env_var/dollar_var.c \
							parsing/env_var/search_variable.c \
							parsing/env_var/utils_dollar.c \
							parsing/env_var/no_dollar_var.c \
							parsing/parse_cmd/get_cmd.c \
							parsing/parse_cmd/get_flag.c \
							parsing/parse_cmd/get_utils.c \

OBJECTS			    	= $(SRC:%.c=$(BUILD_DIR)%.o)

LIBFT					= libft.a
LIB_DIR					= libft/

	
GCC						= gcc
CFLAGS					= -Wall -Wextra -Werror
SANITIZE				= $(CFLAGS) -g3 -fsanitize=address

RM 						= rm -rf
CLEAR					= clear


$(BUILD_DIR)%.o:		$(DIR)%.c $(HEADER_DIR)/$(HEADER_FILE) $(LIB_DIR)
						@mkdir -p $(@D)
						@$(GCC) $(CFLAGS) -I$(HEADER_DIR) -I$(LIB_DIR) -I/usr/include -O3 -c $< -o $@


all: 					clear mkbuild lib  $(HEADER_DIR) $(NAME)

						 
mkbuild:
						@mkdir -p build


clear:
						$(CLEAR)
						
$(NAME): 				$(OBJECTS) $(LIB_DIR)$(LIBFT)
						@$(GCC) $(OBJECTS) -o $(NAME) $(LIB_DIR)$(LIBFT) -lreadline
						@echo "$(GREEN)[✓] $(NAME) created !$(DEFAULT)"

lib:
						@make -C $(LIB_DIR)
						
clean:					
						@${RM} $(OBJECTS)
						@make clean -C $(LIB_DIR)
						@${RM} $(BUILD_DIR)
						@echo "$(YELLOW)[-] object files deleted !$(DEFAULT)"

fclean:					clean
						@${RM} ${NAME}
						@make fclean -C $(LIB_DIR)
						@echo "$(RED)[x] all deleted !$(DEFAULT)"

re:						fclean all
						$(MAKE) all

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m