#include "Cub3d.h"

t_map *parsing(char *input)
{
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
	map = parsing(av[1]);
}