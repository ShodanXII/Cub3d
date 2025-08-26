#include "Cub3d.h"

void add_data(t_data *data, char *identifier, char *value)
{
    if (!strcmp(identifier, "NO"))
        data->map->no_path = ft_strdup(value);
    else if (!strcmp(identifier, "SO"))
        data->map->so_path = ft_strdup(value);
    else if (!strcmp(identifier, "EA"))
        data->map->ea_path = ft_strdup(value);
    else if (!strcmp(identifier, "WE"))
        data->map->we_path = ft_strdup(value);
}

void add_color(t_data *data, char *values, int r, int g, int b)
{
    if (!strcmp(values, "F"))
	{
        data->map->f_rgb[0] = ft_atoi(values[1]);
        data->map->f_rgb[1] = ft_atoi(values[2]);
        data->map->f_rgb[2] = ft_atoi(values[3]);
    }
	else if (!strcmp(values, "C"))
	{
        data->map->c_rgb[0] = ft_atoi(values[1]);
        data->map->c_rgb[1] = ft_atoi(values[2]);
        data->map->c_rgb[2] = ft_atoi(values[3]);
    }
}

void error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

t_map *inti_data(t_map *map)
{
	map = malloc(sizeof(t_map));
	if(!map)
		error("allocation mangoli");
	ft_memset(map, 0, sizeof(t_map));
	return map;
}
void print_split(char **split)
{
	int i = 0;
	while (split[i])
	{
		printf("split[%d] = %s\n", i, split[i]);
		i++;
	}
}

static int	count_words(char const *str, char c, char a)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c || str[i] == a)
			i++;
		else
		{
			count++;
			while (str[i] && str[i] != c && str[i] != a)
				i++;
		}
	}
	return (count);
}

void parse_side(t_data *data, char *identifier, char *path, int count)
{
    if (count != 2)
        error("Invalid number of arguments for texture");
    int len = strlen(path);
    if (len < 4 || strcmp(path + len - 4, ".xpm"))
        error("Invalid texture file format");
    add_data(data, identifier, path);
}

void parse_fc(t_data *data, char *identifier, char **values, int count)
{
    if (count != 4)
        error("Invalid number of arguments for color");
    int r = ft_atoi(values[1]);
    int g = ft_atoi(values[2]);
    int b = ft_atoi(values[3]);
    if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
        error("Invalid color values");
    add_color(data, identifier, r, g, b);
}

void parsing(t_map *map, int fd)
{
	char **work;
	char *line;
	t_data	*data;
	int i =0;
	int count = 0;

	while((line = get_next_line(fd)))
	{
		if (line[0] == '\n')
			continue;
		count = count_words(line, 32, ',');
		work = ft_split(line, count);
		print_split(work);
        if (strcmp(work[0], "NO") == 0)
            parse_side(&data, work[0], work[1], count);
        else if (strcmp(work[0], "SO") == 0)
            parse_side(&data, work[0], work[1], count);
        else if (strcmp(work[0], "EA") == 0)
            parse_side(&data, work[0], work[1], count);
        else if (strcmp(work[0], "WE") == 0)
            parse_side(&data, work[0], work[1], count);
        else if (strcmp(work[0], "F") == 0)
            parse_fc(&data, work[0], work, count);
        else if (strcmp(work[0], "C") == 0)
            parse_fc(&data, work[0], work, count);
		// else if(is_map(line))// to do
		// 	parsing_map(line , map);// to do
		// else (isspace(line))
		// ;
		else
			error("Input Mangoli"); // hna ma tnsax aykon leak d line w map freehom mnba3d
		free(line);
	}
	close(fd);
}

int main(int ac, char **av)
{
	t_map	*map;
	t_data	data;

	if (ac != 2)
		error("NOT a vlaid argumment");
	int len = strlen(av[1]);
	int fd = open(av[1], O_RDONLY);
	if (len < 4 || strcmp(av[1] + len - 4, ".cub") || fd == -1)
		error("Error");
	map = inti_data(map);
    parsing(map, fd);
    data.map = map;
    init_mlx(&data);    
    mlx_loop_hook(data.mlx, &loop_hook, &data);    
    mlx_loop(data.mlx);
}