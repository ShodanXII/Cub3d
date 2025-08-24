#include "Cub3d.h"

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

void parse_north(char *north, int count)
{
	int fd;
	if (count != 2)
		error("bzzf args\n");
	int len = ft_strlen(north);
	if (len < 4 || strcmp(north + len - 4, ".xpm"))
		error("no_pic\n");
}

void parsing(t_map *map, int fd)
{
	char **work;
	char *line;
	int i =0;
	int count = 0;

	while((line = get_next_line(fd)))
	{
		count = count_words(line, 32, ',');
		work = ft_split(line, count);
		if(strcmp(work[0], "NO") == 0)
			parse_north(work[1], count);
		else if(strcmp(work[0], "SO") == 0)
			printf("so\n");
		else if(strcmp(work[0], "EA") == 0)
			printf("ea\n");
		else if(strcmp(work[0], "WE") == 0)
			printf("we\n");
		else if(strcmp(work[0], "F") == 0)
			printf("f\n");
		else if(strcmp(work[0], "C") == 0)
			printf("c\n");
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

	if (ac != 2)
	{
		printf("Error\n");
		return 1;
	}
	int len = strlen(av[1]);
	int fd = open(av[1], O_RDONLY);
	if (len < 4 || strcmp(av[1] + len - 4, ".cub") || fd == -1)
	{
		printf("Error\n");
		return 1;
	}
	map = inti_data(map);
	parsing(map, fd);
}