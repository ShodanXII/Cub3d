#include "Cub3d.h"

void error(char *st)
{
	ft_putstr_fd(2 ,str);
	exit(1);
}

t_map *parsing(char *filename, t_map *map)
{
	int fd;
	char *line;

	fd = open(filename, O_RDONLY)
	if(fd < 0)
		return (error("Cant open file"));
	

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
	if (len < 4 || strcmp(av[1] + len - 4, ".cub") != 0 || open(av[1], O_RDONLY) == -1)
	{
		printf("Error\n");
		return 1;
	}
	map = parsing(av[1], map);
}