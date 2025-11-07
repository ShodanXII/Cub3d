/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textture.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:00:00 by ouel-afi          #+#    #+#             */
/*   Updated: 2025/11/07 12:09:40 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	load_textures(t_data *data)
{
	char	*no_path;
	char	*so_path;
	char	*ea_path;
	char	*we_path;

	// Remove newline characters from paths
	no_path = ft_strtrim(data->map->no_path, "\n\r");
	so_path = ft_strtrim(data->map->so_path, "\n\r");
	ea_path = ft_strtrim(data->map->ea_path, "\n\r");
	we_path = ft_strtrim(data->map->we_path, "\n\r");

	printf("Loading textures:\n");
	printf("North: %s\n", no_path);
	printf("South: %s\n", so_path);
	printf("East: %s\n", ea_path);
	printf("West: %s\n", we_path);

	data->textures->north = mlx_load_png(no_path);
	data->textures->south = mlx_load_png(so_path);
	data->textures->east = mlx_load_png(ea_path);
	data->textures->west = mlx_load_png(we_path);

	if (!data->textures->north || !data->textures->south || 
		!data->textures->east || !data->textures->west)
		error("Failed to load one or more textures");

	printf("All textures loaded successfully!\n");

	free(no_path);
	free(so_path);
	free(ea_path);
	free(we_path);
}

mlx_texture_t	*get_wall_texture(t_data *data, t_ray *ray)
{
	if (ray->side == 0) // Vertical walls (hitting from left/right)
	{
		if (ray->dir_x > 0) // Ray going right, hit west face of wall
			return (data->textures->west);
		else // Ray going left, hit east face of wall
			return (data->textures->east);
	}
	else // Horizontal walls (hitting from top/bottom)
	{
		if (ray->dir_y > 0) // Ray going down, hit north face of wall
			return (data->textures->north);
		else // Ray going up, hit south face of wall
			return (data->textures->south);
	}
}

double	calculate_wall_x(t_ray *ray, t_data *data)
{
	double	wall_x;

	// Calculate where exactly the wall was hit
	if (ray->side == 0) // Vertical wall
		wall_x = data->player->pos_y + ray->perp_wall_dist * ray->dir_y;
	else // Horizontal wall
		wall_x = data->player->pos_x + ray->perp_wall_dist * ray->dir_x;
	
	// Get fractional part only
	wall_x -= floor(wall_x);
	
	return (wall_x);
}

void	calculate_texture_coords(t_ray *ray, t_wall *wall, 
								mlx_texture_t *texture, double wall_x)
{
	// Calculate x coordinate on the texture
	wall->tex_x = (int)(wall_x * (double)texture->width);
	
	// Flip texture coordinates based on ray direction to avoid mirroring
	if (ray->side == 0 && ray->dir_x < 0)
		wall->tex_x = texture->width - wall->tex_x - 1;
	if (ray->side == 1 && ray->dir_y > 0)
		wall->tex_x = texture->width - wall->tex_x - 1;
	
	// Calculate how much to increase the texture coordinate per screen pixel
	wall->step = 1.0 * texture->height / wall->line_height;
	
	// Calculate starting texture coordinate
	wall->tex_pos = (wall->draw_start - SCREEN_HEIGHT / 2 + 
					wall->line_height / 2) * wall->step;
}

uint32_t	get_texture_color(mlx_texture_t *texture, int tex_x, int tex_y)
{
	int		index;
	uint8_t	*pixels;
	uint8_t	r, g, b, a;

	// Clamp texture coordinates to valid range
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)texture->width)
		tex_x = texture->width - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= (int)texture->height)
		tex_y = texture->height - 1;

	pixels = texture->pixels;
	index = (tex_y * texture->width + tex_x) * texture->bytes_per_pixel;
	
	// Extract RGBA values
	r = pixels[index];
	g = pixels[index + 1];
	b = pixels[index + 2];
	a = (texture->bytes_per_pixel == 4) ? pixels[index + 3] : 255;
	
	// Return color in RGBA format for MLX42
	return ((r << 24) | (g << 16) | (b << 8) | a);
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
		// Calculate texture y coordinate
		tex_y = (int)wall->tex_pos;
		wall->tex_pos += wall->step;
		
		// Get pixel color from texture
		color = get_texture_color(texture, wall->tex_x, tex_y);
		
		// Draw pixel
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