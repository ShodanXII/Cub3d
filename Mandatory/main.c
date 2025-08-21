#include "Cub3d.h"

int main(int ac, char **av)
{
	if (ac != 2 || strcmp(av[1] + strlen(av[1]) - 4, ".cub") != 0)
	{
		printf("Error\n");
		return 1;
	}
	if (open(av[1], O_RDONLY) == -1)
	{
		printf("Error1\n");
		return 1;
	}
}