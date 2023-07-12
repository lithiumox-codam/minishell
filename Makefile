NAME = minishell
SRC = main
SRCS = $(addsuffix .c, $(addprefix src/, $(SRC)))
OBJS = $(patsubst src/%.c, build/%.o, $(SRCS))
LIBFT = libft/libft.a
READLINE = readline/libreadline.a

G_FLAGS = -DREADLINE_LIBRARY
CODAM_FLAGS = -Wall -Wextra -Werror
LIBS = libft/libft.a readline/libreadline.a readline/libhistory.a
LINKER = -lncurses
INCLUDES = -I $(CURDIR)/includes -I $(CURDIR)/libft -I $(CURDER)/readline

COLOR_INFO = \033[1;36m
COLOR_SUCCESS = \033[1;32m
COLOR_RESET = \033[0m

EMOJI_INFO = 🌈
EMOJI_SUCCESS = 🎉
EMOJI_CLEAN = 🧹
EMOJI_RUN = 🚀

all: $(NAME)

$(NAME): $(LIBFT) $(READLINE) $(OBJS)
	@printf "$(COLOR_INFO)$(EMOJI_INFO)  Compiling $(NAME)...$(COLOR_RESET)\t"
	@cc $(OBJS) $(CODAM_FLAGS) $(LINKER) $(INCLUDES) $(LIBS) -o $@
	@sleep 0.25
	@printf "✅\n"

build/%.o: src/%.c includes/minishell.h
	@mkdir -p $(@D)
	@cc $(INCLUDES) $(CODAM_FLAGS) -c $< -o $@

$(LIBFT):
	@printf "$(COLOR_INFO)$(EMOJI_INFO)  Initializing submodules...$(COLOR_RESET)\t"
	@git submodule update --init --recursive > /dev/null
	@sleep 0.25
	@printf "✅\n"
	@printf "$(COLOR_INFO)$(EMOJI_INFO)  Building Libft...$(COLOR_RESET)\t\t"
	@$(MAKE) -C libft > /dev/null
	@sleep 0.25
	@printf "✅\n"

$(READLINE):
	@printf "$(COLOR_INFO)$(EMOJI_INFO)  Building Readline...$(COLOR_RESET)\t\t"

	@$(MAKE) static -C readline
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
	@rm -f $(NAME)
	@sleep 0.25
	@printf "✅\n"

run: $(NAME)
	@printf "$(COLOR_INFO)$(EMOJI_RUN)  Compiled and started $(NAME)...$(COLOR_RESET)"
	@./$(NAME) 1

norm:
	@norminette $(SRCS) includes libft

re: fclean $(NAME)

bonus: all

module-update:
	@printf "$(COLOR_INFO)$(EMOJI_INFO)  Updating submodules...$(COLOR_RESET)\t"
	@git submodule update --remote --merge
	@sleep 0.25
	@printf "✅\n"

.PHONY: all clean fclean run re module-update
