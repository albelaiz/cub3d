/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albelaiz <albelaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:16:38 by albelaiz          #+#    #+#             */
/*   Updated: 2025/11/17 16:16:49 by albelaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_extension(char *file)
{
    int len;
    len = ft_strlen(file);

    if (len < 4)
        return(0);
    if (ft_strncmp(file + len - 4,".cub",4))
        return(0);
    return(1);
}