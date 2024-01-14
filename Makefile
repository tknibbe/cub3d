RED=\033[1;31m
GREEN=\033[1;32m
YELLOW=\033[1;33m
BLUE=\033[1;34m
MAGENTA=\033[1;35m
CYAN=\033[1;36m
END=\033[0m

NAME = cub3D
HEADERS  = includes/cub3d.h
SRC_FILES =	main.c \
			utils/error.c \
			utils/free.c \
			minimap.c \
			player.c \
			raycaster/raycaster.c \
			input_handling/parse_input.c \
			input_handling/get_textures/get_textures.c \
			input_handling/get_textures/text_utils.c \
			input_handling/get_map/get_map.c \
			input_handling/get_map/map_utils.c \
			input_handling/get_map/list_to_2d_array.c \
			input_handling/get_map/validate_map.c \
			key_hook.c \
			fps.c \
			init.c \
			events/movement.c

OBJ_FILES = $(SRC_FILES:%.c=obj/%.o)
OBJ_DIR =	obj obj/input_handling obj/utils obj/input_handling/get_map obj/input_handling/get_textures \
			obj/events obj/raycaster

# MLX variables

MLX42_SOURCE_DIR = MLX42/
MLX42_BUILD_DIR = MLX42/build/
MLX42_LIB = MLX42/build/libmlx42.a

# libft variables
LIBFT = libft/libft.a
LIBFT_DIR = libft

# compilation variables

CC = cc
INCLUDES = -I includes -I libft/includes -I MLX42/include/MLX42
CFLAGS = #-Wall -Werror -Wextra
ifdef DEBUG
CFLAGS += -g -fsanitize=address
endif

# flags for the graphics library

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	MLX_FLAGS = -Iinclude -ldl -lglfw -pthread -lm
else ifeq ($(UNAME_S), Darwin)
	GLFW = $(shell brew --prefix glfw)
	MLX_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit -lglfw -L $(GLFW)/lib
else
	$(error OS: $(OS) is not supported!)
endif

# setting variable if submodules haven't been downloaded yet
# checks for empty directories and then sets variable so commands are run on first time typing make

SUBMODULES := $(shell find MLX42 libft -maxdepth 1 -empty)
ifdef SUBMODULES
	SUBMODULES = foo
endif



all: $(NAME)

$(NAME): $(SUBMODULES) $(MLX42_LIB) $(LIBFT) $(OBJ_FILES)
	@echo "${MAGENTA}Creating $@${END}"
	@$(CC) $(INCLUDES) $(MLX_FLAGS) $(CFLAGS) -o $@ $(OBJ_FILES) $(LIBFT) $(MLX42_LIB)
	@echo "${GREEN}Done!${END}"

$(SUBMODULES):
	@git submodule init
	@git submodule update

$(MLX42_LIB):
	@cmake -S $(MLX42_SOURCE_DIR) -B $(MLX42_BUILD_DIR)
	@cmake --build $(MLX42_BUILD_DIR) -j4

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

obj/%.o: src/%.c $(HEADERS) | $(OBJ_DIR)
	@echo "${BLUE}Compiling $<${END}"
	@$(CC) $(INCLUDES) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

clean:
	@echo "${RED}Removing objs cub3d${END}"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean

fclean: clean
	@echo "${RED}Removing ${NAME} and libft MLX42${END}"
	@rm -rf $(LIBFT) $(NAME) $(MLX42_BUILD_DIR)

d: #fclean
	@$(MAKE) DEBUG=1 all

re: fclean all
