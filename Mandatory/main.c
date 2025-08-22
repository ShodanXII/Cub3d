#include "Cub3d.h"

void error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
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

void parsing(t_map *map, int fd)
{
	char **work;
	char *line;
	int i =0;

	while((line = get_next_line(fd)))
	{
		work = ft_split(line);
		if(strcmp(work[0], "NO") == 0)
		{
			printf("no\n");

			// parsing_north(line, map); // to do this functions 
		}
		else if(strcmp(work[0], "SO") == 0)
		{
			printf("so\n");
			// parsing_SO(line, map); /// to do
		}
		else if(strcmp(work[0], "EA") == 0)
		{
			printf("ea\n");
			// parsing_EA(line, map); // to do
		}
		else if(strcmp(work[0], "WE") == 0)
		{
			printf("we\n");
			// parsing_WE(line , map); // to do
		}
		else if(strcmp(work[0], "F") == 0)
		{
			printf("f\n");
			// parsing_F(line, map);// to do
		}
		else if(strcmp(work[0], "C") == 0)
		{
			printf("c\n");
			// parsing_C(line, map); // to do
		}
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
	if (len < 4 || strcmp(av[1] + len - 4, ".cub") != 0 || fd == -1)
	{
		printf("Error\n");
		return 1;
	}
	parsing(map, fd);
}