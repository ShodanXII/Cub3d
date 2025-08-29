/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inti_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:05:04 by ouel-afi          #+#    #+#             */
/*   Updated: 2025/08/27 15:08:39 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void init_data(t_data *data)
{
	data->map->player_x = PLAYER_X;
	data->map->player_y = PLAYER_Y;
}

void player(t_data *data)
{
    if (mlx_is_key_down(data->mlx, MLX_KEY_W))
        data->map->player_y -= 1;
    if (mlx_is_key_down(data->mlx, MLX_KEY_S))
        data->map->player_y += 1;
    if (mlx_is_key_down(data->mlx, MLX_KEY_A))
        data->map->player_x -= 1;
    if (mlx_is_key_down(data->mlx, MLX_KEY_D))
        data->map->player_x += 1;
    if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(data->mlx);
}


void	init_mlx(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HIGHT, "Cub3D", false);
	data->img = mlx_new_image(data->mlx, WIDTH, HIGHT);
	if (!data->img)
		error("Failed to create image");
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0)
		error("Failed to add image to window");
}

void	temp_render(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HIGHT)
		{
			if (j < HIGHT / 2)
				mlx_put_pixel(data->img, i, j, 0x0055AAFF);
			else
				mlx_put_pixel(data->img, i, j, 0x333333FF);
			j++;
		}
		i++;
	}
	for (int y = HIGHT/2 - 50; y < HIGHT/2 + 50; y++)
	{
		for (int x = WIDTH/2 - 50; x < WIDTH/2 + 50; x++)
		{
			mlx_put_pixel(data->img, x, y, 0xFF0000FF);
		}
	}
}

void loop_hook(void *param)
{
    t_data *data = param;
	player(data);
    temp_render(data);
}
