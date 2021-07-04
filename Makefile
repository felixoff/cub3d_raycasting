SRC =	parsing.c \
		parsing_2.c \
		map.c \
		copy_map.c \
		get_texture.c \
		utils.c \
		utils2.c \
		keys_opera.c \
		raycasting.c \
		raycasting2.c \
		raycasting_init.c \
		move_player.c \
		sprites.c \
		errors_save.c \
		cub3d.c \
		get_next_line.c \
		get_next_line_utils.c \
		init_sprite_verify_errors.c

NAME = Cub3D

MLX_DIR = minilibx-linux
MLX = libmlx.a 
CC = gcc


CFLAGS = -Wall -Wextra -Werror -g 

OBJ_DIR = obj
SRC_DIR = src
INC_DIR = inc

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
DPD = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.d))

.c.o:
	${CC} ${CFLAGS} -c$< -o ${<:.c=.o}


all:
	@$(MAKE) -j $(NAME)


$(NAME): $(OBJ)
		${CC} $(CFLAGS) -o $(NAME) $(OBJ) -L $(MLX_DIR) -lmlx -lm -lbsd -lX11 -lXext
		@echo $(NAME) : Created !

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | .gitignore
		@mkdir -p $(OBJ_DIR)
		${CC} $(CFLAGS) -I $(INC_DIR) -I $(MLX_DIR) -c $< -o $@

.gitignore:
		@echo $(NAME) > .gitignore

clean:
	@rm -rf $(OBJ_DIR)
	@echo "obj deleted"

fclean:	clean
	@rm -rf $(NAME)
	@echo "[$(NAME)]: deleted"

re: fclean all

.PHONY: all, clean, fclean, re

-include $(DPD)
