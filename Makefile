NAME := cub3D

CC := cc

INCLUDES := includes/
LIBFT_INCLUDES := libft/includes
MLX_INCLUDES := minilibx-linux/

MLX_DIR := minilibx-linux/
MLX := $(MLX_DIR)libmlx.a

CFLAGS := -Wall -Wextra -Werror -I$(INCLUDES) -I$(LIBFT_INCLUDES) -I$(MLX_INCLUDES)

SRCS := main.c

SRC_DIR := ./srcs/

OBJ_DIR := ./objects/
OBJ := $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

HEADER := $(INCLUDES)cub3d.h

LIBFT_DIR := ./libft/
LIBFT := $(LIBFT_DIR)libft.a

BIN_DIR := ./bin/

YELLOW := \e[1;93m

GREEN := \e[1;4;92m

RED := \e[1;4;91m

NORMAL := \e[0m

ITALIC := \e[3m

DEBUG_FLAGS := $(CFLAGS) -g3

MAKEFLAGS += --no-print-directory -j

vpath %.c $(SRC_DIR)

all: $(BIN_DIR)$(NAME)

$(OBJ_DIR)%.o: %.c $(HEADER) | $(OBJ_DIR)
	@echo -e "[$(YELLOW)COMPILING$(NORMAL)] $@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR):
	@echo -e "[$(ITALIC)CREATING OBJECT DIRECTORY$(NORMAL)]"
	@mkdir $@

$(BIN_DIR):
	@echo -e "[$(ITALIC)CREATING BIN DIRECTORY$(NORMAL)]"
	@mkdir $@

$(BIN_DIR)$(NAME): $(OBJ) $(LIBFT) $(MLX) | $(BIN_DIR)
	@echo "[COMPILING] $@ binary"
	@$(CC) $(CFLAGS) $(OBJ) -o $@ -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11
	@echo -----------------------------------------
	@echo -e "|	Compiled $(GREEN)$(NAME)$(NORMAL) binary 💅	|"
	@echo -----------------------------------------

$(MLX):
	$(MAKE) -C $(MLX_DIR)

debug: | $(BIN_DIR)
	@$(CC) $(DEBUG_FLAGS) -o $(BIN_DIR)$(NAME) $(addprefix $(SRC_DIR), $(SRCS))

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	@echo -------------------------------------------------
	@echo -e "|	Removed $(RED)$(OBJ_DIR)$(NORMAL) directory	🗑️	|"
	@echo -------------------------------------------------

fclean:
	@$(MAKE) clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -rf $(BIN_DIR)
	@echo -------------------------------------------------
	@echo -e "|	Removed $(RED)$(BIN_DIR)$(NORMAL) directory	🗑️	|"
	@echo -------------------------------------------------

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re
