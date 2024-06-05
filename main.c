/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:34:15 by shebaz            #+#    #+#             */
/*   Updated: 2024/06/05 16:15:15 by shebaz           ###   ########.fr       */
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

void	check_arguments(t_data *data, char **av) // work
{
	check_arg(data, av);
	check_characters(data);
	check_form(data);
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
