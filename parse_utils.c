/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaamaich <yaamaich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 09:47:13 by yaamaich          #+#    #+#             */
/*   Updated: 2026/03/18 10:27:51 by yaamaich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	skip_spaces(const char *s, int i)
{
	while (s[i] == ' ')
		i++;
	return (i);
}

static int	parse_component(const char *s, int *i, int *value)
{
	int	n;
	int	has_digit;

	*i = skip_spaces(s, *i);
	n = 0;
	has_digit = 0;
	while (ft_isdigit(s[*i]))
	{
		has_digit = 1;
		n = (n * 10) + (s[*i] - '0');
		if (n > 255)
			return (0);
		(*i)++;
	}
	if (!has_digit)
		return (0);
	*i = skip_spaces(s, *i);
	*value = n;
	return (1);
}

int	parse_rgb_strict(const char *s, int *color)
{
	int	i;
	int	commas;
	int	r;
	int	g;
	int	b;

	i = 0;
	commas = 0;
	while (s[i])
	{
		if (s[i] == ',')
			commas++;
		else if (s[i] != ' ' && !ft_isdigit(s[i]))
			return (0);
		i++;
	}
	if (commas != 2)
		return (0);
	i = 0;
	if (!parse_component(s, &i, &r) || s[i++] != ',')
		return (0);
	if (!parse_component(s, &i, &g) || s[i++] != ',')
		return (0);
	if (!parse_component(s, &i, &b))
		return (0);
	i = skip_spaces(s, i);
	if (s[i] != '\0')
		return (0);
	*color = (r << 16) | (g << 8) | b;
	return (1);
}

void	free_rgb_array(char **rgb)
{
	free(rgb[0]);
	free(rgb[1]);
	free(rgb[2]);
	free(rgb);
}

void	set_color_type(t_game *game, char type, int col)
{
	if (type == 'F')
		game->color_floor = col;
	else
		game->color_ceiling = col;
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
