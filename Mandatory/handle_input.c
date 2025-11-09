/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:35:10 by ouel-afi          #+#    #+#             */
/*   Updated: 2025/11/09 22:05:18 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	handle_strafing_ad(t_data *data, double move_speed)
{
	double	strafe_x;
	double	strafe_y;

	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		strafe_x = -data->player->dir_y;
		strafe_y = data->player->dir_x;
		if (data->map->map[(int)(data->player->pos_y)]
			[(int)(data->player->pos_x + strafe_x * move_speed)] != '1')
			data->player->pos_x += strafe_x * move_speed;
		if (data->map->map[(int)(data->player->pos_y + strafe_y * move_speed)]
			[(int)(data->player->pos_x)] != '1')
			data->player->pos_y += strafe_y * move_speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		strafe_x = data->player->dir_y;
		strafe_y = -data->player->dir_x;
		if (data->map->map[(int)(data->player->pos_y)]
			[(int)(data->player->pos_x + strafe_x * move_speed)] != '1')
			data->player->pos_x += strafe_x * move_speed;
		if (data->map->map[(int)(data->player->pos_y + strafe_y * move_speed)]
			[(int)(data->player->pos_x)] != '1')
			data->player->pos_y += strafe_y * move_speed;
	}
}

void	handle_rotation_arrows(t_data *data, double rot_speed)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->player->rot_angle -= rot_speed;
		init_player_direction(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->player->rot_angle += rot_speed;
		init_player_direction(data);
	}
}

void	handle_rotation_ud(t_data *data, double rot_speed)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
	{
		data->player->rot_angle -= rot_speed;
		init_player_direction(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
	{
		data->player->rot_angle += rot_speed;
		init_player_direction(data);
	}
}

void	handle_escape(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
}

void	handle_input(t_data *data)
{
	double	move_speed;
	double	rot_speed;

	move_speed = 0.05;
	rot_speed = 0.03;
	handle_movement_ws(data, move_speed);
	handle_strafing_ad(data, move_speed);
	handle_rotation_arrows(data, rot_speed);
	handle_rotation_ud(data, rot_speed);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
}
