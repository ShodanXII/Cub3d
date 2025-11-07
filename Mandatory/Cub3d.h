/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:20:43 by ouel-afi          #+#    #+#             */
/*   Updated: 2025/11/07 12:10:37 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <math.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include "../MLX42/include/MLX42/MLX42.h"


typedef struct s_data	t_data;
typedef struct s_player	t_player;
typedef struct s_map	t_map;
# define WIDTH	800
# define HIGHT	800

#define PI 3.14159265358979323846
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800



struct s_map
{
	int		player_x;
	int		player_y;
	int		player_dir;
	char	*no_path;
	char	*we_path;
	char	*ea_path;
	char	*so_path;
	int		f_rgb[3];
	int		c_rgb[3];
	char	**map;	
	int		map_width;
	int		map_hight;
};

// struct s_player
// {
// 	double	pos_x;
// 	double	pos_y;
// 	double	dir_x;
// 	double	dir_y;
// 	double	plane_x;
// 	double	plane_y;
// 	double	move_speed;
// 	double	rot_speed;
// 	double	rot_angle;
// };

typedef struct s_textures
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
}	t_textures;


struct s_data
{
	mlx_image_t	*img;
	t_map		*map;
	mlx_t		*mlx;
	t_textures	*textures;
	t_player	*player;
};


#define FOV (M_PI / 3) // 60 degrees
#define NUM_RAYS WIDTH  // One ray per screen column
#define TILE_SIZE 1.0f
#define MAX_DEPTH 20.0f // Max distance a ray can travel

void	error(char *st);
int	parsing(t_map *map, int fd, t_data *data);
void	init_mlx(t_data *data);
void	init_player(t_data *data);
void	temp_render(t_data *data);
void	loop_hook(void *param);
void	handle_input(t_data *data);

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}	t_ray;

typedef struct s_wall
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;
	int		tex_x;
	double	step;
	double	tex_pos;
}	t_wall;
/* Add these fields to your t_player structure */
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	rot_angle;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

/* Function prototypes */
void	cast_rays(t_data *data);
void	init_player_direction(t_data *data);
void	render_frame(t_data *data);
void	render_background(t_data *data);
void			load_textures(t_data *data);
mlx_texture_t	*get_wall_texture(t_data *data, t_ray *ray);
double			calculate_wall_x(t_ray *ray, t_data *data);
void			calculate_texture_coords(t_ray *ray, t_wall *wall, 
								mlx_texture_t *texture, double wall_x);
uint32_t		get_texture_color(mlx_texture_t *texture, int tex_x, int tex_y);
void			draw_textured_wall(t_data *data, int x, t_wall *wall, 
								mlx_texture_t *texture);
t_textures		*init_textures(void);
char			*ft_strtrim(char const *s1, char const *set);
void	cleanup_textures(t_data *data);

#endif