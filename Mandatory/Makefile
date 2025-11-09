NAME = cub3d

CC = cc
CFLAGS = -O3

SRC_DIR = .
GNL_DIR = $(SRC_DIR)/get_next_line
LIBFT_DIR = $(SRC_DIR)/libft
MLX_DIR = ../MLX42

SRCS = $(SRC_DIR)/main.c main_helper2.c main_helper.c \
	   $(GNL_DIR)/get_next_line.c \
	   $(GNL_DIR)/get_next_line_utils.c \
	   visualasation/inti_mlx.c \
	   ./raycating.c raycasting1.c raycasting2.c \
	   ./texture.c texture1.c texture2.c  utils.c utils2.c utils3.c utils1.c \
	   ./handle_input.c 


OBJS = $(SRCS:.c=.o)

LIBFT = $(LIBFT_DIR)/libft.a
MLX42_LIB = $(MLX_DIR)/build/libmlx42.a

INCLUDES = -I$(MLX_DIR)/include -I$(SRC_DIR)

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	GLFW_PATH = /Users/achat/.brew/opt/glfw
	LIBS = $(MLX42_LIB) $(LIBFT) \
	       -L$(GLFW_PATH)/lib -lglfw \
	       -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
else
	LIBS = $(MLX42_LIB) $(LIBFT) \
	       -L/usr/lib/x86_64-linux-gnu -lglfw \
	       -ldl -lm -pthread
endif

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
