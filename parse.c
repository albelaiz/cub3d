/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaamaich <yaamaich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:19:21 by albelaiz          #+#    #+#             */
/*   Updated: 2026/03/18 10:38:33 by yaamaich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

enum e_cfg_flags
{
	ID_NO = 1,
	ID_SO = 2,
	ID_WE = 4,
	ID_EA = 8,
	ID_F = 16,
	ID_C = 32,
	ID_ALL = 63
};

static int	set_parse_error(t_game *g, char *msg)
{
	if (!g->parse_error)
		printf("Error\n%s\n", msg);
	g->parse_error = 1;
	return (0);
}

static int	line_is_map(const char *line)
{
	int	i;

	if (!line || !line[0])
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

static char	config_type(const char *trimmed)
{
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
		return ('N');
	if (ft_strncmp(trimmed, "SO ", 3) == 0)
		return ('S');
	if (ft_strncmp(trimmed, "WE ", 3) == 0)
		return ('W');
	if (ft_strncmp(trimmed, "EA ", 3) == 0)
		return ('E');
	if (ft_strncmp(trimmed, "F ", 2) == 0)
		return ('F');
	if (ft_strncmp(trimmed, "C ", 2) == 0)
		return ('C');
	return (0);
}

static int	config_bit(char type)
{
	if (type == 'N')
		return (ID_NO);
	if (type == 'S')
		return (ID_SO);
	if (type == 'W')
		return (ID_WE);
	if (type == 'E')
		return (ID_EA);
	if (type == 'F')
		return (ID_F);
	if (type == 'C')
		return (ID_C);
	return (0);
}

static int	handle_config_line(t_game *g, char *trimmed, char type)
{
	int	bit;
	int	ok;

	if (g->map_started)
		return (set_parse_error(g, "Map must be last in file"));
	bit = config_bit(type);
	if (g->config_mask & bit)
		return (set_parse_error(g, "Duplicate identifier"));
	ok = 0;
	if (type == 'F' || type == 'C')
		ok = parse_color(g, trimmed, type);
	else
		ok = pars_texture(g, trimmed, type);
	if (!ok)
		return (set_parse_error(g, "Invalid configuration line"));
	g->config_mask |= bit;
	return (1);
}

void	parse_line(t_game *game, char *line)
{
	char	*trimmed;
	char	*map_line;
	char	type;

	if (game->parse_error)
		return ;
	map_line = ft_strtrim(line, "\n");
	if (!map_line)
	{
		set_parse_error(game, "Malloc failed");
		return ;
	}
	trimmed = ft_strtrim(map_line, " \t");
	if (!trimmed || trimmed[0] == '\0')
	{
		free(trimmed);
		if (game->map_started)
			game->map_ended = 1;
		free(map_line);
		return ;
	}
	type = config_type(trimmed);
	if (type)
		handle_config_line(game, trimmed, type);
	else if (line_is_map(map_line))
	{
		if (game->config_mask != ID_ALL)
			set_parse_error(game, "Map started before all identifiers");
		else if (game->map_ended)
			set_parse_error(game, "Map must be contiguous and last");
		else
		{
			game->map_started = 1;
			if (!pars_map_line(game, map_line))
				set_parse_error(game, "Malloc failed");
		}
	}
	else
		set_parse_error(game, "Invalid line in file");
	free(trimmed);
	free(map_line);
}

int	pars_texture(t_game *game, char *line, char type)
{
	char	*path;
	char	*dup;

	path = ft_strtrim(line + 3, " \t");
	if (!path || path[0] == '\0')
		return (free(path), 0);
	dup = ft_strdup(path);
	free(path);
	if (!dup)
		return (0);
	if (type == 'N')
		game->path_no = dup;
	else if (type == 'S')
		game->path_so = dup;
	else if (type == 'W')
		game->path_we = dup;
	else if (type == 'E')
		game->path_ea = dup;
	else
		return (free(dup), 0);
	return (1);
}

int	parse_color(t_game *game, char *line, char type)
{
	int	col;

	if (!parse_rgb_strict(line + 2, &col))
		return (0);
	set_color_type(game, type, col);
	return (1);
}

int	pars_map_line(t_game *game, char *line)
{
	char	**new_map;
	int		i;
	int		len;
	char	*dup;

	new_map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!new_map)
		return (0);
	i = 0;
	while (i < game->map_height)
	{
		new_map[i] = game->map[i];
		i++;
	}
	dup = ft_strdup(line);
	if (!dup)
		return (free(new_map), 0);
	new_map[game->map_height] = dup;
	free(game->map);
	game->map = new_map;
	len = (int)ft_strlen(line);
	if (len > game->map_width)
		game->map_width = ft_strlen(line);
	find_player_in_line(game, line);
	game->map_height++;
	return (1);
}
