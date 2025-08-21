#include "Cub3d.h"



int main(int ac, char **av)
{
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
	parsing(av[1]);
}