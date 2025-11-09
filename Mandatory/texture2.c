/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:47:31 by achat             #+#    #+#             */
/*   Updated: 2025/11/09 21:47:51 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

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

int	clamp_coord(int v, int max)
{
	if (v < 0)
		return (0);
	if (v >= max)
		return (max - 1);
	return (v);
}

unsigned char	get_alpha(mlx_texture_t *tex, unsigned char *p, int i)
{
	if (tex->bytes_per_pixel == 4)
		return (p[i + 3]);
	return (255);
}

void	get_rgb(unsigned char *p, int i, unsigned char *rgb)
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
