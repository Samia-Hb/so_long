/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:45:26 by shebaz            #+#    #+#             */
/*   Updated: 2024/06/03 11:51:07 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_window(t_data *data)
{
	clear_data(data, 0);
	exit(1);
	return (0);
}

void	free_2d_array(char **array, int height)
{
	int	i;

	i = 0;
	if (array)
	{
		while (i < height)
		{
			if (array[i])
				free(array[i]);
			i++;
		}
		free(array);
	}
}

void	clear_data(t_data *data, int i) // work
{
	if (data->map)
		free_2d_array(data->map, data->map_height);
	if (data->mlx_ptr)
	{
		if (data->win_ptr)
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		if (data->wall)
			mlx_destroy_image(data->mlx_ptr, data->wall);
		if (data->road)
			mlx_destroy_image(data->mlx_ptr, data->road);
		if (data->coins)
			mlx_destroy_image(data->mlx_ptr, data->coins);
		if (data->exit)
			mlx_destroy_image(data->mlx_ptr, data->exit);
		while (i < 3)
		{
			if (data->player[i])
				mlx_destroy_image(data->mlx_ptr, data->player[i]);
			i++;
		}
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	free(data);
}

void	clear_exit(t_data *data) // work
{
	clear_data(data, 0);
	exit(1);
}

void	free_map(char **map, int x, int fd)
{
	int	i;

	i = 0;
	perror("Error\n");
	close(fd);
	while (i < x)
	{
		free(map[i]);
		i++;
	}
	free(map);
	exit(EXIT_FAILURE);
}
