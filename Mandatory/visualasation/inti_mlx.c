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

void render_map(t_data *data)
{
    int i;
    int j;
	int x;
	int y;
    int tile_size = 50;
    
    char **map = data->map->map;
    i = 0;
    while(map[i])
    {
        j = 0;
        while(map[i][j])
        {
            if(map[i][j] == '1')
            {
				y = 0;
                while(y < tile_size)
                {
					x =0;
                    while(x < tile_size)
                    {
                        int screen_x = j * tile_size + x;
                        int screen_y = i * tile_size + y;
                        if (screen_x >= 0 && screen_x < WIDTH && screen_y >= 0 && screen_y < HIGHT)
                            mlx_put_pixel(data->img, screen_x, screen_y, 0xFFFFFFFF);
						x++;
                    }
					y++;
                }
            }
            j++;
        }
        i++;
    }
}

void init_data(t_data *data)
{
	data->map->player_x = PLAYER_X;
	data->map->player_y = PLAYER_Y;
}

void player(t_data *data)
{
    if (mlx_is_key_down(data->mlx, MLX_KEY_W))
        data->map->player_y -= 5;
    if (mlx_is_key_down(data->mlx, MLX_KEY_S))
        data->map->player_y += 5;
    if (mlx_is_key_down(data->mlx, MLX_KEY_A))
        data->map->player_x -= 5;
    if (mlx_is_key_down(data->mlx, MLX_KEY_D))
        data->map->player_x += 5;
    if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(data->mlx);
	if (data->map->player_x < 15)
        data->map->player_x = 15;
    if (data->map->player_x > WIDTH - 15)
        data->map->player_x = WIDTH - 15;
    if (data->map->player_y < 15)
        data->map->player_y = 15;
    if (data->map->player_y > HIGHT - 15)
        data->map->player_y = HIGHT - 15;
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

void render_player(t_data *data)
{
	int i;
	int j;
	int	player_size = 30;

	data->player = malloc(sizeof(t_player));
	player(data);
	int player_x = data->map->player_x - player_size/2;
	int player_y = data->map->player_y - player_size/2;

	i = 0;
    while (i < player_size)
    {
        j = 0;
        while (j < player_size)
        {
            int x = player_x + i;
            int y = player_y + j;
            if (x >= 0 && x < WIDTH && y >= 0 && y < HIGHT)
                mlx_put_pixel(data->img, x, y, 0xFF0000FF); // Red
            j++;
        }
        i++;
    }
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
	render_map(data);
	render_player(data);
}

void loop_hook(void *param)
{
    t_data *data = param;
	player(data);
    temp_render(data);
}
