NAME := cub3D

CC := cc

INCLUDES := includes/
LIBFT_INCLUDES := libft/includes
MLX_INCLUDES := minilibx-linux/

MLX_DIR := minilibx-linux/
MLX := $(MLX_DIR)libmlx.a

CFLAGS := -Wall -Wextra -Werror -I$(INCLUDES) -I$(LIBFT_INCLUDES) -I$(MLX_INCLUDES)

SRCS := main.c

RAYCAST_SRCS := ft_raycasting.c ft_raycasting_utils.c ft_raycasting_loop.c

DRAW_SRCS := ft_draw.c ft_draw_utils.c ft_minimap.c

GAME_SRCS := ft_game.c ft_clean_exit.c ft_textures.c ft_game_utils.c ft_movements.c

ANIMATIONS_SRCS := ft_sword.c ft_door.c ft_door_utils.c

INPUTS_SRCS := ft_input.c ft_camera.c ft_mouse.c 

PARSING_SRCS := utils.c check_map.c init_map.c padding.c parse_ct.c

SRC_DIR := ./srcs/
PARSING_DIR := $(SRC_DIR)parsing/
RAYCAST_DIR := $(SRC_DIR)raycasting/
DRAW_DIR := $(SRC_DIR)draw/
GAME_DIR := $(SRC_DIR)game/
ANIMATIONS_DIR := $(SRC_DIR)animations/
INPUTS_DIR := $(SRC_DIR)inputs/


OBJ_DIR := ./objects/
OBJ = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
OBJ += $(addprefix $(OBJ_DIR), $(PARSING_SRCS:.c=.o))
OBJ += $(addprefix $(OBJ_DIR), $(RAYCAST_SRCS:.c=.o))
OBJ += $(addprefix $(OBJ_DIR), $(DRAW_SRCS:.c=.o))
OBJ += $(addprefix $(OBJ_DIR), $(GAME_SRCS:.c=.o))
OBJ += $(addprefix $(OBJ_DIR), $(ANIMATIONS_SRCS:.c=.o))
OBJ += $(addprefix $(OBJ_DIR), $(INPUTS_SRCS:.c=.o))

HEADER := $(INCLUDES)cub3d.h

LIBFT_DIR := ./libft/
LIBFT := $(LIBFT_DIR)libft.a

BIN_DIR := ./bin/

YELLOW := \e[1;93m

GREEN := \e[1;4;92m

RED := \e[1;4;91m

NORMAL := \e[0m

ITALIC := \e[3m

DEBUG_FLAGS := $(CFLAGS) -fsanitize=address -g3

MAKEFLAGS += --no-print-directory -j

vpath %.c $(SRC_DIR):$(PARSING_DIR):$(RAYCAST_DIR):$(DRAW_DIR):$(GAME_DIR):$(ANIMATIONS_DIR):$(INPUTS_DIR)

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
	@$(CC) $(CFLAGS) $(OBJ) -o $@ -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
	@echo
	@echo "==================================================================================================";
	@echo "                                                                                                  ";
	@echo "                     ▄   ▄▄▄▄   ▄▄▄  ▄▄     ▄▄▄    ▄▄▄▄▄    ▄▄▄▄▄▄                                ";
	@echo "                     ▀██████▀  █▀██  ██    ██▀▀█▄ ██▀▀▀██  █▀██▀▀██                               ";
	@echo "                       ██        ██  ██    ██ ▄█▀ ▀   ▄█▀    ██   ██                              ";
	@echo "                       ██        ██  ██    ██▀▀█▄   ▀▀▀█▄    ██   ██                              ";
	@echo "                       ██        ██  ██  ▄ ██  ▄█ ▄    ██  ▄ ██   ██                              ";
	@echo "                       ▀█████    ▀█████▄ ▀██████▀ ▀█████▀  ▀██▀███▀                               ";
	@echo "                                                                                                  ";
	@echo "                                                                                                  ";
	@echo "                                                                                                  ";
	@echo "           ▄▄         ▄▄     ▄▄▄▄                                                                 ";
	@echo "         ▄█▀▀█▄       ██   ▄██████                                    █▄    █▄                    ";
	@echo "         ██  ██      ▄██   ▀█▄  ██          ▄          ▀▀            ▄██▄   ██                    ";
	@echo "         ██▀▀██    ▄██▀ █      ▄█▀    ████▄ ████▄▄███▄ ██ ▄█▀█▄ ▄███▀ ██    ████▄ ██ ██           ";
	@echo "       ▄ ██  ██    ███████   ▄█▀      ██ ██ ██   ██ ██ ██ ██▄█▀ ██    ██    ██ ██ ██▄██           ";
	@echo "       ▀██▀  ▀█▄█      ██  ██████▄   ▄████▀▄█▀  ▄▀███▀▄██▄▀█▄▄▄▄▀███▄▄██   ▄████▀▄▄▀██▀           ";
	@echo "                                      ██               ██                           ██            ";
	@echo "                                      ▀              ▀▀▀                          ▀▀▀             ";
	@echo "                                                                                                  ";
	@echo "  ▄▄▄▄▄▄                               ▄▄▄▄         ▄▄▄▄▄▄▄                                       ";
	@echo " █▀██▀▀██                    █▄       ██  ██       █▀██▀▀▀  █▄                        █▄       █▄ ";
	@echo "   ██   ██ ▄        ▀▀ ▄     ██       ▀██▄█▀         ██     ██                ▄       ██      ▄██▄";
	@echo "   ██   ██ ███▄███▄ ██ ████▄ ████▄    ▄████▄▄█▀      ████   ████▄ ▄███▄ ██ ██ ████▄▄████ ▄█▀█▄ ██ ";
	@echo " ▄ ██   ██ ██ ██ ██ ██ ██ ██ ██ ██   ██▀  ██▄        ██     ██ ██ ██ ██ ██ ██ ██   ██ ██ ██▄█▀ ██ ";
	@echo " ▀██▀███▀ ▄██ ██ ▀█▄██▄██ ▀█▄██ ██   ▀█▄▄██▀▀█▄      ▀█████▄████▀▄▀███▀▄▀██▀█▄█▀  ▄█▀███▄▀█▄▄▄▄██ ";
	@echo "                                                                                                  ";
	@echo "                                                                                                  ";
	@echo "==================================================================================================";
	@echo

$(MLX):
	@if [ ! -d "minilibx-linux" ]; then \
		echo "The minilibx folder was not found. Cloning the source.\n"; \
		git clone https://github.com/42paris/minilibx-linux.git; \
	fi
	$(MAKE) -C $(MLX_DIR)

debug: $(LIBFT) $(MLX) | $(BIN_DIR)
	@$(CC) $(DEBUG_FLAGS) -o $(BIN_DIR)$(NAME) $(addprefix $(SRC_DIR), $(SRCS)) $(addprefix $(PARSING_DIR), $(PARSING_SRCS)) \
	$(addprefix $(RAYCAST_DIR), $(RAYCAST_SRCS)) $(addprefix $(DRAW_DIR), $(DRAW_SRCS)) \
	$(addprefix $(GAME_DIR), $(GAME_SRCS)) $(addprefix $(ANIMATIONS_DIR), $(ANIMATIONS_SRCS)) \
	$(addprefix $(INPUTS_DIR), $(INPUTS_SRCS)) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

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
