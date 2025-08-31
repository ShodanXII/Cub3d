NAME = cub3d

CC = cc
CFLAGS =  -O3

SRC_DIR = .
GNL_DIR = $(SRC_DIR)/get_next_line
LIBFT_DIR = $(SRC_DIR)/libft
MLX_DIR = ../MLX42

# Linux setup - no brew needed
SRCS = $(SRC_DIR)/main.c \
	   $(SRC_DIR)/visualasation/inti_mlx.c \
	   $(GNL_DIR)/get_next_line.c \
	   $(GNL_DIR)/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

LIBFT = $(LIBFT_DIR)/libft.a
MLX42_LIB = $(MLX_DIR)/build/libmlx42.a

INCLUDES = -I$(MLX_DIR)/include -I$(SRC_DIR)

# Linux libraries - no frameworks needed
LIBS = $(MLX42_LIB) -lglfw $(LIBFT) -ldl -lm

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