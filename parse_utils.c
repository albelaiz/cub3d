#include "cub3d.h"

void	free_rgb_array(char **rgb)
{
	free(rgb[0]);
	free(rgb[1]);
	free(rgb[2]);
	free(rgb);
}

void	set_color(t_game *game, char type, int r, int g, int b)
{
	if (type == 'F')
		game->color_floor = (r << 16) | (g << 8) | b;
	else
		game->color_ceiling = (r << 16) | (g << 8) | b;
}

void	find_player_in_line(t_game *game, char *line)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (line[x] == 'N' || line[x] == 'S'
			|| line[x] == 'E' || line[x] == 'W')
		{
			game->player_start_x = x;
			game->player_start_y = game->map_height;
			game->player_start_dir = line[x];
		}
		x++;
	}
}

void	copy_old_map(t_game *game, char **new_map)
{
	int	i;

	i = 0;
	while (i < game->map_height)
	{
		new_map[i] = game->map[i];
		i++;
	}
}
