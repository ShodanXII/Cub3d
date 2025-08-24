#include "../Cub3d.h"


void init_mlx(t_data *data)
{
    data->mlx = mlx_init(WIDTH, HIGHT, "Cub3D", false);
    data->img = mlx_new_image(data->mlx, WIDTH, HIGHT);
    if (!data->img)
        error("Failed to create image");        
    if (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0)
        error("Failed to add image to window");
}

void temp_render(t_data *data)
{
    int i = 0;
    int j;
    while (i < WIDTH)
    {
        j = 0;
        while(j < HIGHT)
        {
            if(j < HIGHT / 2)
                mlx_put_pixel(data->img, i, j, 0x0055AAFF );
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
            mlx_put_pixel(data->img, x, y, 0xFF0000FF); // Red square
        }
    }
}

void loop_hook(void *param)
{
    t_data *data = param;
    temp_render(data);
}
