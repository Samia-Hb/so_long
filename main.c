/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:34:15 by shebaz            #+#    #+#             */
/*   Updated: 2024/06/04 21:51:11 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_map(t_data *data, void *texture, int x, int y) // work
{
	while (x < data->map_height)
	{
		y = 0;
		while (y < data->map_width)
		{
			if (data->map[x][y] == '1')
				texture = data->wall;
			else if (data->map[x][y] == '0')
				texture = data->road;
			else if (data->map[x][y] == 'c' || data->map[x][y] == 'C')
				texture = data->coins;
			else if (data->map[x][y] == 'P')
			{
				data->x = x;
				data->y = y;
				texture = data->player[0];
			}
			else if (data->map[x][y] == 'E')
				texture = data->exit;
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, texture, y
				* TILE_SIZE, x * TILE_SIZE);
			y++;
		}
		x++;
	}
}

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

void	check_arguments(t_data *data, char **av) // work
{
	check_arg(data, av);
	check_characters(data);
	check_form(data, av);
	check_borders(data);
	check_parameters_number(data, 0, 0);
	check_path(data);
}

int	main(int ac, char **av)
{
	t_data	*data;
	char	*str;
	void	*texture;

	str = NULL;
	texture = NULL;
	if (ac < 2)
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	initial_struct(data);
	calcul_width_height(data, av, str);
	map_2d_array(data, av);
	check_arguments(data, av);
	windows_stuff(data);
	picture_loading(data);
	draw_map(data, texture, 0, 0);
	mlx_key_hook(data->win_ptr, handle_key, data);
	mlx_hook(data->win_ptr, 17, 0, close_window, data);
	mlx_loop(data->mlx_ptr);
	clear_data(data, 0);
	return (0);
}
