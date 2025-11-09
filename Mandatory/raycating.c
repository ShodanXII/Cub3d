/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:00:00 by ouel-afi          #+#    #+#             */
/*   Updated: 2025/11/09 21:51:41 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	init_player_direction(t_data *data)
{
	double	angle;

	angle = data->player->rot_angle;
	data->player->dir_x = cos(angle);
	data->player->dir_y = sin(angle);
	data->player->plane_x = -sin(angle) * 0.66;
	data->player->plane_y = cos(angle) * 0.66;
}

void	render_background(t_data *data)
{
	int	x;
	int	y;
	int	ceiling_color;
	int	floor_color;

	ceiling_color = (data->map->c_rgb[0] << 24) | (data->map->c_rgb[1] << 16) | 
		(data->map->c_rgb[2] << 8) | 0xFF;
	floor_color = (data->map->f_rgb[0] << 24) | (data->map->f_rgb[1] << 16) | 
		(data->map->f_rgb[2] << 8) | 0xFF;
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			if (y < SCREEN_HEIGHT / 2)
				mlx_put_pixel(data->img, x, y, ceiling_color);
			else
				mlx_put_pixel(data->img, x, y, floor_color);
			x++;
		}
		y++;
	}
}

void	render_frame(t_data *data)
{
	render_background(data);
	cast_rays(data);
}
