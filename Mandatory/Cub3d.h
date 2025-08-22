# ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"
#include <fcntl.h>
#include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_map t_map;

struct s_map
{
    int player_x;
    int player_y;
    int player_dir;
    char    *NO_path;
    char    *WE_path;
    char    *EA_path;
    char    *SO_path;
    int     f_rgb[3];
    int     c_rgb[3];
    char    **map;
    int     map_width;
    int     map_hight;
};

void error(char *st);
void parsing(t_map *map, int fd);

#endif