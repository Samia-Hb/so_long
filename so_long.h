/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:14:33 by shebaz            #+#    #+#             */
/*   Updated: 2024/05/31 14:28:55 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

# include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line/get_next_line.h"

#define TILE_SIZE 50 // Size of each tile
#define WINDOWS_HEIGHT 600
#define WINDOWS_WIDTH 500

typedef struct s_data
{
    void *mlx_ptr;
    void *win_ptr;
    void *wall;
    void *player[3];
    void *enemy[5];
    void *road;
    void *coins;
    void *exit;
    char **map;
    int tex_width;
    int tex_height;
	int x;
	int y;
	int coins_nbr;
	int map_height;
    int map_width;
} t_data;


void clear_data(t_data *data, int i);
void    initial_struct(t_data *data);
void    check_arguments(t_data *data, char **av);
int handle_key(int keycode, t_data *data);
int close_window(t_data *data);
void clear_exit(t_data *data);

#endif