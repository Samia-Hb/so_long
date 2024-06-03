/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:49:10 by shebaz            #+#    #+#             */
/*   Updated: 2024/06/03 22:13:14 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	go_up(t_data *data) // work
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->road, data->y
		* TILE_SIZE, data->x * TILE_SIZE);
	data->map[data->x][data->y] = '0';
	if (data->map[data->x - 1][data->y] == '1' || (data->map[data->x
			- 1][data->y] == 'E' && data->coins_nbr))
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player[0],
			data->y * TILE_SIZE, data->x * TILE_SIZE);
	else if (data->map[data->x - 1][data->y] == '0')
	{
		data->x--;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player[0],
			data->y * TILE_SIZE, data->x * TILE_SIZE);
	}
	else if (data->map[data->x - 1][data->y] == 'c' || data->map[data->x
		- 1][data->y] == 'C')
	{
		data->coins_nbr--;
		data->x--;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player[0],
			data->y * TILE_SIZE, data->x * TILE_SIZE);
	}
	else if (data->map[data->x - 1][data->y] == 'E' && !(data->coins_nbr))
		clear_exit(data);
	data->map[data->x][data->y] = 'P';
}

void	go_down(t_data *data) // work
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->road, data->y
		* TILE_SIZE, data->x * TILE_SIZE);
	data->map[data->x][data->y] = '0';
	if ((data->map[data->x + 1][data->y] == 'E' && data->coins_nbr)
		|| data->map[data->x + 1][data->y] == '1')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player[0],
			data->y * TILE_SIZE, data->x * TILE_SIZE);
	else if (data->map[data->x + 1][data->y] == '0')
	{
		data->x++;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player[0],
			data->y * TILE_SIZE, data->x * TILE_SIZE);
	}
	else if (data->map[data->x + 1][data->y] == 'c' || data->map[data->x
		+ 1][data->y] == 'C')
	{
		data->coins_nbr--;
		data->x++;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player[0],
			data->y * TILE_SIZE, data->x * TILE_SIZE);
	}
	else if (data->map[data->x][data->y] == 'E' && data->coins_nbr == 0)
		clear_exit(data);
	data->map[data->x][data->y] = 'P';
}

void	go_right(t_data *data) // work
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->road, data->y
		* TILE_SIZE, data->x * TILE_SIZE);
	data->map[data->x][data->y] = '0';
	if ((data->map[data->x][data->y + 1] == 'E' && data->coins_nbr)
		|| data->map[data->x][data->y + 1] == '1')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player[0],
			data->y * TILE_SIZE, data->x * TILE_SIZE);
	if (data->map[data->x][data->y + 1] == '0')
	{
		data->y++;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player[1],
			data->y * TILE_SIZE, data->x * TILE_SIZE);
	}
	else if (data->map[data->x][data->y + 1] == 'c'
		|| data->map[data->x][data->y + 1] == 'C')
	{
		data->coins_nbr--;
		data->y++;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player[1],
			data->y * TILE_SIZE, data->x * TILE_SIZE);
	}
	else if (data->map[data->x][data->y + 1] == 'E' && data->coins_nbr == 0)
		clear_exit(data);
	data->map[data->x][data->y] = 'P';
}

void	go_left(t_data *data) // work
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->road, data->y
		* TILE_SIZE, data->x * TILE_SIZE);
	data->map[data->x][data->y] = '0';
	if ((data->map[data->x][data->y - 1] == 'E' && data->coins_nbr)
		|| data->map[data->x][data->y - 1] == '1')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player[0],
			data->y * TILE_SIZE, data->x * TILE_SIZE);
	if (data->map[data->x][data->y - 1] == '0')
	{
		data->y--;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player[2],
			data->y * TILE_SIZE, data->x * TILE_SIZE);
	}
	else if (data->map[data->x][data->y - 1] == 'c'
		|| data->map[data->x][data->y - 1] == 'C')
	{
		data->coins_nbr--;
		data->y--;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player[2],
			data->y * TILE_SIZE, data->x * TILE_SIZE);
	}
	else if (data->map[data->x][data->y - 1] == 'E' && data->coins_nbr == 0)
		clear_exit(data);
	data->map[data->x][data->y] = 'P';
}

int	handle_key(int keycode, t_data *data) // work
{
	int	i;

	i = 0;
	i++;
	if (keycode == 65307)
		clear_exit(data);
	if (keycode == 0x0077)
		go_up(data);
	else if (keycode == 0x0073)
		go_down(data);
	else if (keycode == 0x0061)
		go_left(data);
	else if (keycode == 0x0064)
		go_right(data);
	printf("move : %d", i);
	return (0);
}
