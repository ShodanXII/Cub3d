#include "Cub3d.h"

// hadi gha texture
char *validate_texture(char *path, char *texture_name)
{
    int fd;
    
    if (!path)
        error(ft_strjoin("Missing path for ", texture_name));
    int len = ft_strlen(path);
    if (len < 4 || strcmp(path + len - 4, ".xpm"))
        error(ft_strjoin(texture_name, " texture must be a .xpm file"));
    fd = open(path, O_RDONLY);
    if (fd == -1)
        error(ft_strjoin("Cannot open ", texture_name));
    close(fd);
    char *dup = ft_strdup(path);
    if (!dup)
        error("Memory allocation failed");   
    return dup;
}

void parsing_north(char *north, t_map *map)
{
    if (map->no_path)
        error("NO texture defined multiple times");
    map->no_path = validate_texture(north, "NO");
}

void parsing_south(char *south, t_map *map)
{
    if (map->so_path)
        error("SO texture defined multiple times");
    map->so_path = validate_texture(south, "SO");
}

void parsing_east(char *east, t_map *map)
{
    if (map->ea_path)
        error("EA texture defined multiple times");
    map->ea_path = validate_texture(east, "EA");
}

void parsing_west(char *west, t_map *map)
{
    if (map->we_path)
        error("WE texture defined multiple times");
   map->we_path = validate_texture(west, "WE");
}
