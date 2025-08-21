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
		if(ft_strcmp(line, "NO"))
			parsing_north(input, map); // to do this functions 
		else if(ft_strcmp(line, "WE"))
			parsing_WE(line , map); // to do
		else if(ft_strcmp(input, "EA"))
			parsing_EA(line, map); // to do
		else if(ft_strcmp(line, "SO")) 
			parsing_SO(line, map); /// to do
		else if(ft_strcmp(line,"F"))
			parsing_F(line, map);// to do
		else if(ft_strcmp(line, "C"))
			parsing_C(line, map); // to do
		else if(is_map(line, ))// to do
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