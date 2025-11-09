/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:00:00 by ouel-afi          #+#    #+#             */
/*   Updated: 2025/11/09 22:02:32 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	handle_movement_ws(t_data *data, double move_speed)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		if (data->map->map[(int)(data->player->pos_y)]
			[(int)(data->player->pos_x + data->player->dir_x
				* move_speed)] != '1')
			data->player->pos_x += data->player->dir_x * move_speed;
		if (data->map->map[(int)(data->player->pos_y
				+ data->player->dir_y * move_speed)]
			[(int)(data->player->pos_x)] != '1')
			data->player->pos_y += data->player->dir_y * move_speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		if (data->map->map[(int)(data->player->pos_y)]
			[(int)(data->player->pos_x - data->player->dir_x
				* move_speed)] != '1')
			data->player->pos_x -= data->player->dir_x * move_speed;
		if (data->map->map[(int)(data->player->pos_y
				- data->player->dir_y * move_speed)]
			[(int)(data->player->pos_x)] != '1')
			data->player->pos_y -= data->player->dir_y * move_speed;
	}
}

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
