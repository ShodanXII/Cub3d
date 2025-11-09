/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:00:00 by ouel-afi          #+#    #+#             */
/*   Updated: 2025/11/09 21:47:30 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

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
