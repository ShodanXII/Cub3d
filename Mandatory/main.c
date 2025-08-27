#include "Cub3d.h"

void print_data(t_data *data)
{
	printf("NO path %s\n", data->map->no_path);
	printf("SO path %s\n", data->map->so_path);
	printf("EA path %s\n", data->map->ea_path);
	printf("WE path %s\n", data->map->we_path);
	printf("this is the floor argb %d\n" ,data->map->f_rgb[0]);
	printf("this is the floor argb %d\n" , data->map->f_rgb[1]);
	printf("this is the floor argb %d\n" , data->map->f_rgb[2]);
	printf("this is the cealing argb %d\n" ,data->map->c_rgb[0]);
	printf("this is the cealing argb %d\n" , data->map->c_rgb[1]);
	printf("this is the cealing argb %d\n" , data->map->c_rgb[2]);
}

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

void add_color(t_data *data, char *identifier, int r, int g, int b)
{
    if (!strcmp(identifier, "F"))
    {
        data->map->f_rgb[0] = r;
        data->map->f_rgb[1] = g;
        data->map->f_rgb[2] = b;
    }
    else if (!strcmp(identifier, "C"))
    {
        data->map->c_rgb[0] = r;
        data->map->c_rgb[1] = g;
        data->map->c_rgb[2] = b;
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

void parse_side(t_data *data, char **work, int count, int *a)
{
	*a += 1;
    if (count != 2)
        error("Invalid number of arguments for texture");
    int len = strlen(work[1]);
    if (len < 4 || strcmp(work[1] + len - 4, ".xpm"))
        error("Invalid texture file format");
    add_data(data, work[0], work[1]);
}

void parse_fc(t_data *data, char **values, int count, int *a)
{
	*a += 1;
    if (count != 4)
        error("Invalid number of arguments for color");
    int r = ft_atoi(values[1]);
    int g = ft_atoi(values[2]);
    int b = ft_atoi(values[3]);
    if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
        error("Invalid color values");
    add_color(data, values[0], r, g, b);
}

void parse_map(char **map)
{
	map = malloc(sizeof(char *) )
}

void parsing(t_map *map, int fd, t_data *data)
{
	char **work;
	char *line;
	int i = 0;
	int count = 0;
	int a = 0;

	while((line = get_next_line(fd)))
	{
		if (line[0] == '\n')
			continue;
		count = count_words(line, 32, ',');
		if (a != 6){
			work = ft_split(line, count);
			print_split(work);
		}
        if (strcmp(work[0], "NO") == 0)
            parse_side(data, work, count, &a);
        else if (strcmp(work[0], "SO") == 0)
            parse_side(data, work, count, &a);
        else if (strcmp(work[0], "EA") == 0)
            parse_side(data, work, count, &a);
        else if (strcmp(work[0], "WE") == 0)
            parse_side(data, work, count, &a);
        else if (strcmp(work[0], "F") == 0)
            parse_fc(data, work, count, &a);
        else if (strcmp(work[0], "C") == 0)
            parse_fc(data, work, count, &a);
		// else if(is_map(line))// to do
		// 	parsing_map(line , map);// to do
		parse_map(map->map);
			// parse_map(line , map);
		// else (isspace(line))
		// ;
		// else
		// 	error("Input Mangoli"); // hna ma tnsax aykon leak d line w map freehom mnba3d
		free(line);
	}
	close(fd);
}

int main(int ac, char **av)
{
	t_map	*map;
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (ac != 2)
		error("NOT a vlaid argumment");
	int len = strlen(av[1]);
	int fd = open(av[1], O_RDONLY);
	if (len < 4 || strcmp(av[1] + len - 4, ".cub") || fd == -1)
		error("Error");
	map = inti_data(map);
	data->map = map; // Add this line
	parsing(map, fd, data);
	print_data(data);
    // init_mlx(&data);    
    // mlx_loop_hook(data.mlx, &loop_hook, &data);    
    // mlx_loop(data.mlx);
}