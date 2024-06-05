/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 22:58:37 by shebaz            #+#    #+#             */
/*   Updated: 2024/06/05 16:15:28 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	picture_loading(t_data *data)
{
	data->wall = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/wall.xpm",
			&data->tex_width, &data->tex_height);
	data->road = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/road.xpm",
			&data->tex_width, &data->tex_height);
	data->coins = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/coins.xpm",
			&data->tex_width, &data->tex_height);
	data->player[0] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./assests/player.xpm", &data->tex_width, &data->tex_height);
	data->player[1] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./assests/player_right.xpm", &data->tex_width, &data->tex_height);
	data->player[2] = mlx_xpm_file_to_image(data->mlx_ptr,
			"./assests/player_left.xpm", &data->tex_width, &data->tex_height);
	data->exit = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/exit.xpm",
			&data->tex_width, &data->tex_height);
	if (!data->wall || !data->road || !data->coins || !data->player[0]
		|| !data->player[1] || !data->player[2] || !data->exit)
	{
		perror("Failed to load one or more textures");
		clear_exit(data);
	}
}

void	windows_stuff(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		clear_exit(data);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->map_width * TILE_SIZE,
			data->map_height * TILE_SIZE, "So_long");
	if (!data->win_ptr)
		clear_exit(data);
}

void	insert_pos(t_data *data, int x, int y)
{
	if (data->map[x][y] == 'C')
		data->coins_nbr++;
	else
	{
		data->x = x;
		data->y = y;
	}
}

void	initial_struct(t_data *data)
{
	data->coins_nbr = 0;
	data->map_height = 0;
	data->e_nbr = 0;
	data->p_nbr = 0;
	data->x = 0;
	data->y = 0;
	data->map_width = 0;
}
