/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:00:00 by ouel-afi          #+#    #+#             */
/*   Updated: 2025/11/09 21:06:52 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	load_textures(t_data *data)
{
	char	*no_path;
	char	*so_path;
	char	*ea_path;
	char	*we_path;

	no_path = ft_strtrim(data->map->so_path, "\n\r");
	so_path = ft_strtrim(data->map->no_path, "\n\r");
	ea_path = ft_strtrim(data->map->ea_path, "\n\r");
	we_path = ft_strtrim(data->map->we_path, "\n\r");
	data->textures->north = mlx_load_png(no_path);
	data->textures->south = mlx_load_png(so_path);
	data->textures->east = mlx_load_png(ea_path);
	data->textures->west = mlx_load_png(we_path);
	if (!data->textures->north || !data->textures->south || 
		!data->textures->east || !data->textures->west)
		error("Failed to load one or more textures");
	free(no_path);
	free(so_path);
	free(ea_path);
	free(we_path);
}

mlx_texture_t	*get_wall_texture(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (data->textures->west);
		else
			return (data->textures->east);
	}
	else 
	{
		if (ray->dir_y > 0)
			return (data->textures->north);
		else 
			return (data->textures->south);
	}
}

double	calculate_wall_x(t_ray *ray, t_data *data)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = data->player->pos_y + ray->perp_wall_dist * ray->dir_y;
	else 
		wall_x = data->player->pos_x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

void	calculate_texture_coords(t_ray *ray, t_wall *wall, 
								mlx_texture_t *texture, double wall_x)
{
	wall->tex_x = (int)(wall_x * (double)texture->width);
	if (ray->side == 0 && ray->dir_x < 0)
		wall->tex_x = texture->width - wall->tex_x - 1;
	if (ray->side == 1 && ray->dir_y > 0)
		wall->tex_x = texture->width - wall->tex_x - 1;
	wall->step = 1.0 * texture->height / wall->line_height;
	wall->tex_pos = (wall->draw_start - SCREEN_HEIGHT / 2 + 
			wall->line_height / 2) * wall->step;
}

static int	clamp_coord(int v, int max)
{
	if (v < 0)
		return (0);
	if (v >= max)
		return (max - 1);
	return (v);
}

static unsigned char	get_alpha(mlx_texture_t *tex, unsigned char *p, int i)
{
	if (tex->bytes_per_pixel == 4)
		return (p[i + 3]);
	return (255);
}

static void	get_rgb(unsigned char *p, int i, unsigned char *rgb)
{
	rgb[0] = p[i];
	rgb[1] = p[i + 1];
	rgb[2] = p[i + 2];
}

unsigned int	get_texture_color(mlx_texture_t *tex, int x, int y)
{
	int				i;
	unsigned char	*p;
	unsigned char	rgb[3];
	unsigned char	a;

	x = clamp_coord(x, tex->width);
	y = clamp_coord(y, tex->height);
	p = tex->pixels;
	i = (y * tex->width + x) * tex->bytes_per_pixel;
	get_rgb(p, i, rgb);
	a = get_alpha(tex, p, i);
	return ((rgb[0] << 24) | (rgb[1] << 16) | (rgb[2] << 8) | a);
}

void	draw_textured_wall(t_data *data, int x, t_wall *wall, 
						mlx_texture_t *texture)
{
	int			y;
	int			tex_y;
	uint32_t	color;

	y = wall->draw_start;
	while (y <= wall->draw_end)
	{
		tex_y = (int)wall->tex_pos;
		wall->tex_pos += wall->step;
		color = get_texture_color(texture, wall->tex_x, tex_y);
		mlx_put_pixel(data->img, x, y, color);
		y++;
	}
}

t_textures	*init_textures(void)
{
	t_textures	*textures;

	textures = malloc(sizeof(t_textures));
	if (!textures)
		error("Texture allocation failed");
	ft_memset(textures, 0, sizeof(t_textures));
	return (textures);
}

void	cleanup_textures(t_data *data)
{
	if (data->textures)
	{
		if (data->textures->north)
			mlx_delete_texture(data->textures->north);
		if (data->textures->south)
			mlx_delete_texture(data->textures->south);
		if (data->textures->east)
			mlx_delete_texture(data->textures->east);
		if (data->textures->west)
			mlx_delete_texture(data->textures->west);
		free(data->textures);
	}
}
