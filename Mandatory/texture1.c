/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:46:20 by achat             #+#    #+#             */
/*   Updated: 2025/11/09 21:46:48 by achat            ###   ########.fr       */
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
