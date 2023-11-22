NAME = minishell
SRC = main \
    utils/error \
    utils/miscellaneous \
    structs/token \
    structs/env \
    structs/shell \
	structs/group \
    parser/index \
    parser/tokens \
    checker/index \
	checker/helpers \
	checker/heredoc \
    group/group \
    group/heredoc \
	group/hdoc_expand \
    debug/print_vector \
	debug/print_group \
    exec/exec \
	exec/utils \
	exec/exec_builtin \
    exec/create_processes \
    exec/exec_process \
    exec/redirect \
	exec/check_cmd \
	built_in/exit \
	built_in/pwd \
	built_in/export \
	built_in/echo \
	built_in/cd \
	built_in/cd_err \
	built_in/utils \
	built_in/unset \
	built_in/env \
	built_in/sort \
	lexer/index \
	expander/index \
	expander/expand_env \
	expander/expand_quotes \
	signals/index

SRCS = $(addsuffix .c, $(addprefix src/, $(SRC)))
OBJS = $(patsubst src/%.c, build/%.o, $(SRCS))
LIBFT = libft/libft.a

DEBUG ?= 0
DEBUG_FLAGS = -g
CODAM_FLAGS = -Wall -Wextra -Werror
LINKER = -lreadline
INCLUDES = -I $(CURDIR)/includes -I $(CURDIR)/libft/includes

COLOR_INFO = \033[1;36m
COLOR_SUCCESS = \033[1;32m
COLOR_RESET = \033[0m

EMOJI_INFO = 🌈
EMOJI_SUCCESS = 🎉
EMOJI_CLEAN = 🧹
EMOJI_RUN = 🚀

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@printf "$(COLOR_INFO)$(EMOJI_INFO)  Compiling $(NAME)...$(COLOR_RESET)\t"
	@cc $(OBJS) $(CODAM_FLAGS) $(if DEBUG, $(DEBUG_FLAGS)) -DDEBUG=$(DEBUG) $(LINKER) $(INCLUDES) $(LIBFT) -o $@
	@sleep 0.25
	@printf "✅\n"

build/%.o: src/%.c includes/minishell.h includes/structs.h includes/enum.h
	@mkdir -p $(@D)
	@cc $(INCLUDES) $(CODAM_FLAGS) $(if DEBUG, $(DEBUG_FLAGS)) -DDEBUG=$(DEBUG) -c $< -o $@

$(LIBFT):
	@printf "$(COLOR_INFO)$(EMOJI_INFO)  Initializing submodules...$(COLOR_RESET)\t"
	@git submodule update --init --recursive > /dev/null
	@printf "✅\n"
	@printf "$(COLOR_INFO)$(EMOJI_INFO)  Building Libft...$(COLOR_RESET)\t\t"
	@$(MAKE) -C libft DEBUG=$(DEBUG) > /dev/null
	@sleep 0.25
	@printf "✅\n"

clean:
	@printf "$(COLOR_INFO)$(EMOJI_CLEAN)  Cleaning up...$(COLOR_RESET)\t\t"
	@$(MAKE) -C libft clean > /dev/null
	@rm -rf build
	@sleep 0.25
	@printf "✅\n"

fclean: clean
	@printf "$(COLOR_INFO)$(EMOJI_CLEAN)  Removing executable...$(COLOR_RESET)\t"
	@$(MAKE) -C libft fclean > /dev/null
	@rm -f libft/libft.a
	@rm -f $(NAME)
	@sleep 0.25
	@printf "✅\n"

run: $(NAME)
	@printf "$(COLOR_INFO)$(EMOJI_RUN)  Compiled and started $(NAME)...$(COLOR_RESET)"
	@./$(NAME) 1

norm:
	@norminette $(SRCS) includes libft

re:
	@$(MAKE) fclean
	@$(MAKE) $(NAME)

bonus: all

module-update:
	@printf "$(COLOR_INFO)$(EMOJI_INFO)  Updating submodules...$(COLOR_RESET)\t"
	@git submodule update --remote --merge
	@sleep 0.25
	@printf "✅\n"

.PHONY: all clean fclean run re module-update
