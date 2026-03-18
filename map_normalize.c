/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_normalize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaamaich <yaamaich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 12:00:58 by yaamaich          #+#    #+#             */
/*   Updated: 2026/03/18 09:34:15 by yaamaich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_partial_map(char **map, int count)
{
	while (count > 0)
		free(map[--count]);
	free(map);
}

static char	*pad_line(const char *src, int width)
{
	char	*dst;
	int		i;

	dst = (char *)malloc(width + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (src[i] && i < width)
	{
		dst[i] = src[i];
		i++;
	}
	while (i < width)
		dst[i++] = ' ';
	dst[width] = '\0';
	return (dst);
}

static int	allocate_new_map(t_game *g, char **new_map)
{
	int	y;

	y = 0;
	while (y < g->map_height)
	{
		new_map[y] = pad_line(g->map[y], g->map_width);
		if (!new_map[y])
		{
			free_partial_map(new_map, y);
			return (printf("Error\nMalloc failed\n"), 0);
		}
		y++;
	}
	new_map[g->map_height] = NULL;
	return (1);
}

int	normalize_map(t_game *g)
{
	char	**new_map;
	int		y;

	if (!g->map || g->map_height <= 0)
		return (printf("Error\nMissing map\n"), 0);
	if (g->map_width <= 0)
		return (printf("Error\nInvalid map width\n"), 0);
	new_map = (char **)malloc(sizeof(char *) * (g->map_height + 1));
	if (!new_map)
		return (printf("Error\nMalloc failed\n"), 0);
	if (!allocate_new_map(g, new_map))
		return (0);
	y = 0;
	while (y < g->map_height)
	{
		free(g->map[y]);
		y++;
	}
	free(g->map);
	g->map = new_map;
	return (1);
}
