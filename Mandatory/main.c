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
		error("Cant open file");
	while(line = get_next_line(fd))
	{
		if(is_NO(line)) // to do
			parsing_north(input, map); // to do thid functions 
		else if(is_WE(line)) // to do hadi 
			parsing_WE(line , map); // to do
		else if(is_EA(input))// to do
			parsing_EA(line, map); // to do
		else if(is_SO(line)) // to do
			parsing_SO(line, map); /// to do
		else if(is_F(line)) /// to do
			parsing_F(line, map);// to do
		else if(is_C(line))/// to fdo
			parsing_C(line, map); // to do
		else if(is_map(line))// to do
			parsing_map(line , map);// to do
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
	if (len < 4 || strcmp(av[1] + len - 4, ".cub") != 0 || open(av[1], O_RDONLY) == -1)
	{
		printf("Error\n");
		return 1;
	}
	map = parsing(av[1], map);
}