/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inti_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:05:04 by ouel-afi          #+#    #+#             */
/*   Updated: 2025/11/10 10:25:26 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

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
	int	player_size;

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
}

void	loop_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	handle_input(data);
	render_frame(data);
}
