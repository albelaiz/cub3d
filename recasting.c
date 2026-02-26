/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recasting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaamaich <yaamaich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 02:50:11 by yaamaich          #+#    #+#             */
/*   Updated: 2026/02/22 03:19:44 by yaamaich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void draw_vline(t_game *g, int x, int y0, int y1, uint32_t color)
{
    if (y0 < 0) y0 = 0;
    if (y1 >= (int)g->img_ptr->height) y1 = (int)g->img_ptr->height - 1;
    for (int y = y0; y <= y1; y++)
        mlx_put_pixel(g->img_ptr, x, y, color);
}

void render_3d(t_game *g)
{
    int w = (int)g->img_ptr->width;
    int h = (int)g->img_ptr->height;

    // background: ceiling/floor
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            mlx_put_pixel(g->img_ptr, x, y, (y < h/2) ? 0x0020ff40 : 0xFF20ff20);

    double dirX = cos(g->player_dir);
    double dirY = sin(g->player_dir);

    const double fov = M_PI / 3.0;
    double planeLen = tan(fov / 2.0);
    double planeX = -dirY * planeLen;
    double planeY =  dirX * planeLen;

    for (int x = 0; x < w; x++)
    {
        double cameraX = 2.0 * x / (double)w - 1.0;
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;

        int mapX = (int)g->player_x;
        int mapY = (int)g->player_y;

        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1.0 / rayDirY);

        int stepX, stepY;
        double sideDistX, sideDistY;

        if (rayDirX < 0) { stepX = -1; sideDistX = (g->player_x - mapX) * deltaDistX; }
        else             { stepX =  1; sideDistX = (mapX + 1.0 - g->player_x) * deltaDistX; }

        if (rayDirY < 0) { stepY = -1; sideDistY = (g->player_y - mapY) * deltaDistY; }
        else             { stepY =  1; sideDistY = (mapY + 1.0 - g->player_y) * deltaDistY; }

        int hit = 0;
        int side = 0; // 0 x-side, 1 y-side

        while (!hit)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (mapX < 0 || mapY < 0 || mapX >= g->map_width || mapY >= g->map_height)
                break;
            if (g->map[mapY][mapX] == '1')
                hit = 1;
        }

        if (!hit)
            continue;

        double perpDist;
        if (side == 0)
            perpDist = (mapX - g->player_x + (1 - stepX) / 2.0) / rayDirX;
        else
            perpDist = (mapY - g->player_y + (1 - stepY) / 2.0) / rayDirY;

        if (perpDist <= 0.0001)
            perpDist = 0.0001;

        int lineH = (int)(h / perpDist);
        int drawStart = -lineH / 2 + h / 2;
        int drawEnd = lineH / 2 + h / 2;

        uint32_t wallColor = (side == 0) ? 0xFFB0B0B0 : 0xFF808080; // simple shading
        draw_vline(g, x, drawStart, drawEnd, wallColor);
    }
}