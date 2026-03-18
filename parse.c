/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaamaich <yaamaich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:19:21 by albelaiz          #+#    #+#             */
/*   Updated: 2026/03/18 04:15:46 by yaamaich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_line(t_game *game, char *line)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t\n");
	if (!trimmed || trimmed[0] == '\0')
	{
		free(trimmed);
		return ;
	}
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
		pars_texture(game, trimmed, 'N');
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
		pars_texture(game, trimmed, 'S');
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
		pars_texture(game, trimmed, 'W');
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
		pars_texture(game, trimmed, 'E');
	else if (ft_strncmp(trimmed, "F ", 2) == 0)
		parse_color(game, trimmed, 'F');
	else if (ft_strncmp(trimmed, "C ", 2) == 0)
		parse_color(game, trimmed, 'C');
	else
		pars_map_line(game, trimmed);
	free(trimmed);
}

void	pars_texture(t_game *game, char *line, char type)
{
	char	*path;

	path = ft_strtrim(line + 3, " \t");
	if (type == 'N' && !game->path_no)
		game->path_no = ft_strdup(path);
	else if (type == 'S' && !game->path_so)
		game->path_so = ft_strdup(path);
	else if (type == 'W' && !game->path_we)
		game->path_we = ft_strdup(path);
	else if (type == 'E' && !game->path_ea)
		game->path_ea = ft_strdup(path);
	free(path);
}

void	parse_color(t_game *game, char *line, char type)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(line + 2, ',');
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		printf("Error\nInvalid RGB color values (must be 0-255)\n");
		free_rgb_array(rgb);
		return ;
	}
	set_color(game, type, r, g, b);
	free_rgb_array(rgb);
}

void	pars_map_line(t_game *game, char *line)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!new_map)
		return ;
	i = 0;
	while (i < game->map_height)
	{
		new_map[i] = game->map[i];
		i++;
	}
	new_map[game->map_height] = ft_strdup(line);
	free(game->map);
	game->map = new_map;
	if (ft_strlen(line) > game->map_width)
		game->map_width = ft_strlen(line);
	find_player_in_line(game, line);
	game->map_height++;
}