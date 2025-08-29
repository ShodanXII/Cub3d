/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 11:09:10 by ouel-afi          #+#    #+#             */
/*   Updated: 2025/08/29 12:59:33 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	{
		if (data->map->no_path)
			error("dup_no");
        data->map->no_path = ft_strdup(value);
	}
    else if (!strcmp(identifier, "SO"))
	{
		if (data->map->so_path)
			error("dup_so");
        data->map->so_path = ft_strdup(value);
	}
    else if (!strcmp(identifier, "EA"))
	{
		if (data->map->ea_path)
			error("dup_ea");
        data->map->ea_path = ft_strdup(value);
	}
    else if (!strcmp(identifier, "WE"))
	{
		if (data->map->we_path)
			error("dup_we");
        data->map->we_path = ft_strdup(value);
	}
}

void add_color(t_data *data, char *identifier, int r, int g, int b)
{
    if (!strcmp(identifier, "F"))
    {
		if (data->map->f_rgb[0])
			error("dup_f");
        data->map->f_rgb[0] = r;
        data->map->f_rgb[1] = g;
        data->map->f_rgb[2] = b;
    }
    else if (!strcmp(identifier, "C"))
    {
		if (data->map->c_rgb[0])
			error("dup_c");
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
    if (len < 5 || strcmp(work[1] + len - 5, ".xpm\n"))
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

int store_map(t_map *map, int fd)
{
	char *line;
	int i = 0;
	char **tmp;

	map->map = NULL;
	while((line = get_next_line(fd)))
	{
		if (line[0] == '\n')
			continue;
		while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
			i++;
		if (!line[i])	
			continue;
		tmp = realloc(map->map, sizeof(char *) * (i + 2));
		if (!tmp)
			error("realloc kharya");
		map->map = tmp;
		map->map[i] = ft_strdup(line);
		free(line);
		i++;
		map->map[i] = NULL;
	}
	return i;
}

void valid_map(char **map, int count)
{
	int i = 0;
	int j;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N')
			{
				if (i == 0 || i == count - 1 || map[i][j - 1] == '\0' || map[i][j + 1] == '\0' || map[i - 1][j] == '\0' || map[i + 1][j] == '\0')
					error("map khari.");
				if ((map[i][j - 1] != '0' && map[i][j - 1] != '1' && map[i][j - 1] != 'N') || (map[i][j + 1] != '0' && map[i][j + 1] != '1' && map[i][j + 1] != 'N') || (map[i - 1][j] != '0' && map[i - 1][j] != '1' && map[i - 1][j] != 'N') || (map[i + 1][j] != '0' && map[i + 1][j] != '1' && map[i + 1][j] != 'N'))
					error("map_khari");
			}
			j++;
		}
		i++;
	}	
}

void check_map(char **map)
{
    int i = 0;
	int j;
	int count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N')
				count++;
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'N' && map[i][j] != 32 && map[i][j] != '\t')
				error("map mangoli");
			j++;
		}
		i++;
	}
	if (count != 1)
		error("no_player");
}

void parse_map(t_map *map, int fd)
{
	int count = store_map(map, fd);
	for(int i =0; map->map[i];i++)
		printf("map[%d] = %s\n", i, map->map[i]);
	check_map(map->map);
	valid_map(map->map, count);
}


int parsing(t_map *map, int fd, t_data *data)
{
	char **work;
	char *line;
	int i;
	int count = 0;
	int a = 0;

	while((line = get_next_line(fd)))
	{
		if (line[0] == '\n')
			continue;
		count = count_words(line, 32, ',');
		i = 0;
		while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
			i++;
		if (!line[i])	
			continue;
		if (a != 6){
			work = ft_split(line, count);
			print_split(work);
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
		else
			error("Input Mangoli");
		}
		if (a == 6)
			return 1;
		free(line);
	}
	// close(fd);
	return 0;
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
	data->map = map;
	if (parsing(map, fd, data))
		parse_map(map, fd);
	print_data(data);
    // init_mlx(&data);    
    // mlx_loop_hook(data.mlx, &loop_hook, &data);    
    // mlx_loop(data.mlx);
}