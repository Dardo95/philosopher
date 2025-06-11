NAME := philo

CC = cc
CFLAGS := -Wall -Werror -Wextra -pthread -MMD -MP -g3
IFLAGS := -Iincludes

SRC :=	src/args.c \
		src/init.c \
		src/main.c \
		src/monitor.c \
		src/philo_actions.c \
		src/philo_threads.c \
		src/philo_utils.c \
		src/simulation.c \

BUILD_DIR := build
OBJ := $(SRC:.c=.o)
OBJ := $(addprefix $(BUILD_DIR)/, $(OBJ))
DEP := $(OBJ:.o=.d)

BLUE := \033[34m
GREEN := \033[32m
YELLOW := \033[33m
CYAN := \033[36m
RESET := \033[0m

-include $(DEP)

all: $(NAME)

$(NAME): $(OBJ)
	@printf "$(CYAN)\r🔗 Enlazando: $(NAME)                     $(RESET)\n"
	@$(CC) $(OBJ) -o $(NAME) $(CFLAGS)
	@printf "$(GREEN)\n✅ Compilación completa$(RESET)\n"

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "$(BLUE)\r⚙️  Compilando: $<                         $(RESET)"
	@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<


clean:
	@printf "$(YELLOW)\r🧹 Limpiando objetos...                $(RESET)\n"
	@rm -rf $(BUILD_DIR)

fclean: clean
	@printf "$(YELLOW)\r🗑️  Borrando ejecutable...              $(RESET)\n"
	@rm -f $(NAME)
	@printf "$(GREEN)\r✅  Limpieza completa.                  $(RESET)\n"

re: fclean all

norm:
	@printf "$(YELLOW)\n🔍 Revisando con norminette...$(RESET)\n"
	@norminette includes
	@norminette $(SRC)


.PHONY: all clean fclean re norm
.DEFAULT_GOAL := all
