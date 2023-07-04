NAME := minishell
OBJ_DIR := obj
CC := cc
CFLAGS := -Wall #-Wextra -Werror #-g -fsanitize=address
LIBFT := libft/
INC := minishell.h check/check.h
SRCS := main.c env.c exec_utils.c execute.c expand.c expand_utils.c fill_command_utils.c fill_commands.c heredoc.c parse.c parse_utils.c redirect_input.c redirect_output.c redirection.c remove_brackets.c signals.c split_args.c tokenize.c utils.c utils_2.c
SRCS += builtins/cd.c builtins/env.c builtins/export_utils.c builtins/pwd.c builtins/utils.c builtins/echo.c builtins/export.c builtins/ft_exit.c builtins/unset.c
SRCS += check/check_line.c check/check_tkns.c check/split_it.c check/tkn_it.c
OBJS := $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))
RED		=	\033[31m
GREEN	=	\033[32m
BLUE	=	\033[34m
PINK	=	\033[35m
WHITE	=	\033[37m
BOLD	=	\033[1m
RESET	=	\033[0m
$(NAME): libft/libft.a $(OBJS)
	@echo "$(GREEN) $(BOLD) making $(NAME) ... $(RESET)"
	@$(CC) $(CFLAGS) -Llibft -lft -lreadline $^ -o $@
	@echo "$(PINK) $(BOLD) $(NAME) is ready $(RESET)"

$(OBJ_DIR)/%.o: %.c $(INC)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

libft/libft.a:
	@echo "$(WHITE) $(BOLD) making libft ... $(RESET)"
	@$(MAKE) -C $(LIBFT)

all: $(NAME)

$(shell mkdir -p $(sort $(dir $(OBJS))))

clean:
	@$(MAKE) -C $(LIBFT) clean
	@rm -rf $(OBJ_DIR)
	@echo "$(RED) $(BOLD) removed object files $(RESET)"

fclean: clean
	@$(MAKE) -C $(LIBFT) fclean
	@rm -f $(NAME)
	@echo "$(RED) $(BOLD) removed binaries $(RESET)"

re: fclean all
.PHONY: all libft clean fclean re
