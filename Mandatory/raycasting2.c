/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:51:22 by achat             #+#    #+#             */
/*   Updated: 2025/11/09 21:51:26 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	perform_dda(t_ray *ray, t_data *data)
{
	while (ray->hit == 0)
	{
		update_ray_position(ray);
		check_map_bounds(ray);
		if (ray->hit == 1)
			break ;
		check_wall_collision(ray, data);
	}
}

void	calculate_distance(t_ray *ray, t_data *data)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - data->player->pos_x
				+ (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - data->player->pos_y
				+ (1 - ray->step_y) / 2) / ray->dir_y;
}

void	draw_vertical_line(t_data *data, int x, t_wall *wall)
{
	int	y;

	y = wall->draw_start;
	while (y <= wall->draw_end)
	{
		mlx_put_pixel(data->img, x, y, wall->color);
		y++;
	}
}

void	calculate_wall_rendering(t_ray *ray, t_wall *wall)
{
	wall->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	wall->draw_start = -wall->line_height / 2 + SCREEN_HEIGHT / 2;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	wall->draw_end = wall->line_height / 2 + SCREEN_HEIGHT / 2;
	if (wall->draw_end >= SCREEN_HEIGHT)
		wall->draw_end = SCREEN_HEIGHT - 1;
}

void	cast_rays(t_data *data)
{
	t_ray			ray;
	t_wall			wall;
	mlx_texture_t	*texture;
	double			wall_x;
	int				x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		init_ray(&ray, data, x);
		calculate_step_and_side_dist(&ray, data);
		perform_dda(&ray, data);
		calculate_distance(&ray, data);
		calculate_wall_rendering(&ray, &wall);
		texture = get_wall_texture(data, &ray);
		wall_x = calculate_wall_x(&ray, data);
		calculate_texture_coords(&ray, &wall, texture, wall_x);
		draw_textured_wall(data, x, &wall, texture);
		x++;
	}
}
