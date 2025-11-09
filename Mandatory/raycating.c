/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:00:00 by ouel-afi          #+#    #+#             */
/*   Updated: 2025/11/09 21:38:27 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	init_ray(t_ray *ray, t_data *data, int x)
{
	ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	ray->dir_x = data->player->dir_x + data->player->plane_x * ray->camera_x;
	ray->dir_y = data->player->dir_y + data->player->plane_y * ray->camera_x;
	ray->map_x = (int)data->player->pos_x;
	ray->map_y = (int)data->player->pos_y;
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
}

void	calculate_step_and_side_dist(t_ray *ray, t_data *data)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player->pos_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->player->pos_x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player->pos_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->player->pos_y)
			* ray->delta_dist_y;
	}
}

void	update_ray_position(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

void	check_map_bounds(t_ray *ray)
{
	if (ray->map_y < 0 || ray->map_x < 0)
	{
		ray->hit = 1;
	}
}

void	check_wall_collision(t_ray *ray, t_data *data)
{
	if (data->map->map[ray->map_y] && data->map->map[ray->map_y][ray->map_x])
	{
		if (data->map->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
	else
	{
		ray->hit = 1;
	}
}

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
