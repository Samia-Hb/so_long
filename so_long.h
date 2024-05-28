/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:14:33 by shebaz            #+#    #+#             */
/*   Updated: 2024/05/27 13:54:11 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line/get_next_line.h"
#include "minilibx-linux/mlx.h"

#define TILE_SIZE 50 // Size of each tile
#define WINDOWS_HEIGHT 600
#define WINDOWS_WIDTH 500



typedef struct s_data
{
    void *mlx_ptr;
    void *win_ptr;
    void *wall;
    void *player[3];
    void *road;
    void *coins;
    void *exit;
    char **map;
    int tex_width;
    int tex_height;
	int x;
	int y;
	int coins_nbr;
} t_data;

#endif