NAME = minishell
SRC = main
SRCS = $(addsuffix .c, $(addprefix src/, $(SRC)))
OBJS = $(patsubst src/%.c, build/%.o, $(SRCS))
LIBFT = libft/libft.a

CODAM_FLAGS = -Wall -Wextra -Werror
LIBS = MLX42/build/libmlx42.a libft/libft.a
INCLUDES = -I $(CURDIR)/incl -I $(CURDIR)/libft

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
	@cc $(OBJS) $(LIBS) $(INCLUDES) $(LINKERS) $(CODAM_FLAGS) -o $@
	@sleep 0.25
	@printf "✅\n"

build/%.o: src/%.c incl/minishell.h
	@mkdir -p $(@D)
	@gcc $(INCLUDES) $(CODAM_FLAGS) -c $< -o $@

$(LIBFT):
	@printf "$(COLOR_INFO)$(EMOJI_INFO)  Initializing submodules...$(COLOR_RESET)\t"
	@git submodule update --init --recursive > /dev/null
	@sleep 0.25
	@printf "✅\n"
	@printf "$(COLOR_INFO)$(EMOJI_INFO)  Building Libft...$(COLOR_RESET)\t\t"
	@$(MAKE) -C libft > /dev/null
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
	@norminette $(SRCS) incl/fractol.h libft

re: fclean $(NAME)

bonus: all

module-update:
	@git submodule update --remote --merge

.PHONY: all clean fclean run re module-update
