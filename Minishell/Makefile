CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -I Include
LDFLAGS = -lreadline

SRCDIR  = Srcs
OBJDIR  = Obj
INCDIR  = Include

NAME    = minishell

SRCS    = \
	Srcs/main.c \
	Srcs/Buildin/cd/cd.c \
	Srcs/Buildin/cd/cd_null2.c \
	Srcs/Buildin/cd/cd_null.c \
	Srcs/Buildin/cd/cd_utils.c \
	Srcs/Buildin/echo/echo.c \
	Srcs/Buildin/env/env.c \
	Srcs/Buildin/export/exp.c \
	Srcs/Buildin/export/exp_print.c \
	Srcs/Buildin/export/exp_utils1.c \
	Srcs/Buildin/export/exp_utils2.c \
	Srcs/Buildin/export/exp_utils3.c \
	Srcs/Buildin/pwd/pwd.c \
	Srcs/Buildin/unset/unset.c \
	Srcs/Execution/execve/check.c \
	Srcs/Execution/execve/execve.c \
	Srcs/Execution/execve/execve_utils.c \
	Srcs/Execution/pipe/pipe.c \
	Srcs/Execution/pipe/pipe_utils2.c \
	Srcs/Execution/pipe/pipe_utils.c \
	Srcs/Operations/here_doc/here_doc.c \
	Srcs/Operations/here_doc/here_doc_utils1.c \
	Srcs/Operations/here_doc/here_doc_utils2.c \
	Srcs/Operations/here_doc/here_doc_utils3.c \
	Srcs/Operations/redirection/operations2.c \
	Srcs/Operations/redirection/operations.c \
	Srcs/Operations/redirection/op_input.c \
	Srcs/Operations/redirection/op_output.c \
	Srcs/Parsing/dollar/dollar.c \
	Srcs/Parsing/dollar/dollar_counter.c \
	Srcs/Parsing/dollar/dollar_utils2.c \
	Srcs/Parsing/dollar/dollar_utils3.c \
	Srcs/Parsing/dollar/dollar_utils.c \
	Srcs/Parsing/parsing/parsing.c \
	Srcs/Parsing/parsing/parsing_utils.c \
	Srcs/Parsing/parsing/validation.c \
	Srcs/Signals/exit.c \
	Srcs/Signals/signals.c \
	Srcs/Utils/files_utils1.c \
	Srcs/Utils/file_utils2.c \
	Srcs/Utils/ft_split.c \
	Srcs/Utils/libft_utils1.c \
	Srcs/Utils/libft_utils2.c \
	Srcs/Utils/libft_utils3.c \
	Srcs/Utils/libft_utils4.c \
	Srcs/Utils/libft_utils5.c \
	Srcs/Utils/libft_utils6.c \
	Srcs/Utils/libft_utils7.c \
	Srcs/Utils/libft_utils8.c \
	Srcs/Utils/libft_utils9.c \
	Srcs/Utils/print.c \
	Srcs/Utils/stuct_array.c

OBJS    = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

GREEN   = \033[0;32m
RED     = \033[0;31m
RESET   = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
	@echo "$(RED)✔ Minishell Compiled!$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(RED)Compiled:$(RESET) $(GREEN)$@ ✔$(RESET)"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@rm -rf $(OBJDIR)
	@echo "$(RED)🗑️  Object files removed!$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)🗑️  Executable removed!$(RESET)"

re: fclean all

v: all
	@echo "$(RED)Compiling with Valgrind...$(RESET)"
	@valgrind --leak-check=full -q ./$(NAME)

.PHONY: all clean fclean re v
