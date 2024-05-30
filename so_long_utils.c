/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:42:37 by shebaz            #+#    #+#             */
/*   Updated: 2024/05/30 13:43:46 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void go_up(t_data *data)//work
{
    if (data->map[data->x - 1][data->y] == '1' || (data->map[data->x - 1][data->y] == 'E' && data->coins_nbr != 0))
        return ;
    else if (data->map[data->x - 1][data->y] == '0')
    {
        mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->road, data->y * TILE_SIZE, data->x * TILE_SIZE);
        data->map[data->x][data->y] = '0';
        data->x--;
        mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player[0], data->y * TILE_SIZE, data->x * TILE_SIZE);
        data->map[data->x][data->y] = 'P';
    } 
    else if (data->map[data->x - 1][data->y] == 'c' || data->map[data->x - 1][data->y] == 'C')
    {
        data->coins_nbr--;
        mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->road, data->y * TILE_SIZE, data->x * TILE_SIZE);
        data->map[data->x][data->y] = '0';
        data->x--;
        mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player[0], data->y * TILE_SIZE, data->x * TILE_SIZE);
        data->map[data->x][data->y] = 'P';
    }
    else if (data->map[data->x - 1][data->y] == 'E' && !(data->coins_nbr))
	{
		clear_data(data, 0);
        exit(0);
	}
}

void go_down(t_data *data)//work
{
    if (data->map[data->x + 1][data->y] == '1' || (data->map[data->x + 1][data->y] == 'E' && data->coins_nbr != 0))
        return;
    else if (data->map[data->x + 1][data->y] == '0')
    {
        mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->road, data->y * TILE_SIZE, data->x * TILE_SIZE);
        data->map[data->x][data->y] = '0';
        data->x++;
        mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player[0], data->y * TILE_SIZE, data->x * TILE_SIZE);
        data->map[data->x][data->y] = 'P';
    }
    else if (data->map[data->x + 1][data->y] == 'c' || data->map[data->x + 1][data->y] == 'C')
	{
        data->coins_nbr--;
        mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->road, data->y * TILE_SIZE, data->x * TILE_SIZE);
        data->map[data->x][data->y] = '0';
        data->x++;
        mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player[0], data->y * TILE_SIZE, data->x * TILE_SIZE);
        data->map[data->x][data->y] = 'P';
    }
    else if (data->map[data->x][data->y] == 'E' && data->coins_nbr == 0)
	{
		clear_data(data, 0);
        exit(0);
	}
}

void go_right(t_data *data)//work
{
    if (data->map[data->x][data->y + 1] == '1' || (data->map[data->x][data->y + 1] == 'E' && data->coins_nbr != 0))
        return;
    else if (data->map[data->x][data->y + 1] == '0')
    {
        mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->road, data->y * TILE_SIZE, data->x * TILE_SIZE);
        data->map[data->x][data->y] = '0';
        data->y++;
        mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player[1], data->y * TILE_SIZE, data->x * TILE_SIZE);
        data->map[data->x][data->y] = 'P';
    } 
    else if (data->map[data->x][data->y + 1] == 'c' || data->map[data->x][data->y + 1] == 'C')
    {
        data->coins_nbr--;
        mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->road, data->y * TILE_SIZE, data->x * TILE_SIZE);
        data->map[data->x][data->y] = '0';
        data->y++;
        mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player[1], data->y * TILE_SIZE, data->x * TILE_SIZE);
        data->map[data->x][data->y] = 'P';
    }
    else if (data->map[data->x][data->y + 1] == 'E' && data->coins_nbr == 0)
	{
		clear_data(data, 0);
        exit(0);
	}
}

void go_left(t_data *data)//work
{
    if (data->map[data->x][data->y - 1] == '1' || (data->map[data->x][data->y - 1] == 'E' && data->coins_nbr != 0))
        return;
    else if (data->map[data->x][data->y - 1] == '0')
    {
        mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->road, data->y * TILE_SIZE, data->x * TILE_SIZE);
        data->map[data->x][data->y] = '0';
        data->y--;
        mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player[2], data->y * TILE_SIZE, data->x * TILE_SIZE);
        data->map[data->x][data->y] = 'P';
    }
    else if (data->map[data->x][data->y - 1] == 'c' || data->map[data->x][data->y - 1] == 'C')
    {
        data->coins_nbr--;
        mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->road, data->y * TILE_SIZE, data->x * TILE_SIZE);
        data->map[data->x][data->y] = '0';
        data->y--;
        mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player[2], data->y * TILE_SIZE, data->x * TILE_SIZE);
        data->map[data->x][data->y] = 'P';
    }
    else if (data->map[data->x][data->y - 1] == 'E' && data->coins_nbr == 0)
	{
		clear_data(data, 0);
        exit(0);
	}
}

int handle_key(int keycode, t_data *data)//work
{
    if (keycode == 65307)//ESC
    {
		clear_data(data, 0);
		exit(0);
	}
    else if (keycode == 0x0077)//W
        go_up(data);
    else if (keycode == 0x0073)//S
        go_down(data);
    else if (keycode == 0x0061)//A
        go_left(data);
    else if (keycode == 0x0064)//D
        go_right(data);
    return (0);
}