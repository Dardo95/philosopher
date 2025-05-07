NAME := philo

CC = cc
CFLAGS := -Wall -Werror -Wextra -g -pthread -MMD -MP
IFLAGS := -Iincludes

SRC :=	src/args.c \
		src/init.c \
		src/monitor.c \
		src/philo.c \
		src/philo_threads.c \
		src/philo_actions.c \
		src/philo_utils.c \
		#src/time_utils.c \
		#src/actions.c \

BUILD_DIR := build
OBJ := $(SRC:.c=.o)
OBJ := $(addprefix $(BUILD_DIR)/, $(OBJ))
DEP := $(OBJ:.o=.d)

BLUE := \033[34m
GREEN := \033[32m
YELLOW := \033[33m
CYAN := \033[36m
RESET := \033[0m

.DEFAULT_GOAL := all

all: $(NAME)
	@printf "$(GREEN)\n✅ Compilación completa$(RESET)\n"

$(NAME): $(OBJ)
	@printf "$(CYAN)\r🔗 Enlazando: $(NAME)                     $(RESET)\n"
	@$(CC) $(OBJ) -o $(NAME) $(CFLAGS)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "$(BLUE)\r⚙️  Compilando: $<                         $(RESET)"
	@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<

run: $(NAME)
	@./$(NAME) $(ARGS)

debug: CFLAGS += -g3 -fsanitize=address -fsanitize=thread
debug: re
	@printf "$(CYAN)\n🚀 Ejecutando en modo DEBUG...$(RESET)\n"
	@./$(NAME) $(ARGS)

valgrind: $(NAME)
	@valgrind --leak-check=full --track-origins=yes ./$(NAME) $(ARGS)

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

-include $(DEP)

.PHONY: all clean fclean re norm run debug valgrind
