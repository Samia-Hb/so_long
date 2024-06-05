/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:37:54 by shebaz            #+#    #+#             */
/*   Updated: 2024/06/05 11:04:20 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_2d_array_update(char **array, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**copy_map(t_data *data)
{
	char	**copied_map;
	int		x;
	int		y;

	x = 0;
	copied_map = malloc((data->map_height + 1) * sizeof(char *));
	if (!copied_map)
		return (NULL);
	while (x < data->map_height)
	{
		copied_map[x] = malloc((data->map_width + 1) * sizeof(char));
		if (!copied_map[x])
			return (free_2d_array_update(copied_map, x), NULL);
		y = 0;
		while (y < data->map_width)
		{
			copied_map[x][y] = data->map[x][y];
			y++;
		}
		copied_map[x][y] = '\0';
		x++;
	}
	copied_map[data->map_height] = NULL;
	return (copied_map);
}

void	flood_fill(char **map, int x, int y, int *coins_nbr)
{
	if (map[x][y] != '0' && map[x][y] != 'C' && map[x][y] != 'E'
		&& map[x][y] != 'P')
		return ;
	if (map[x][y] == 'C')
		(*coins_nbr)++;
	map[x][y] = 's';
	flood_fill(map, x + 1, y, coins_nbr);
	flood_fill(map, x - 1, y, coins_nbr);
	flood_fill(map, x, y + 1, coins_nbr);
	flood_fill(map, x, y - 1, coins_nbr);
}

void	check_path(t_data *data)
{
	int		coins_nbr;
	char	**copied_map;

	coins_nbr = 0;
	copied_map = copy_map(data);
	if (!copied_map)
	{
		perror("Error\n");
		exit(1);
	}
	flood_fill(copied_map, data->x, data->y, &coins_nbr);
	if (data->coins_nbr != coins_nbr)
	{
		perror("Error : no valid path");
		free_2d_array_update(copied_map, data->map_height);
		free_2d_array_update(data->map, data->map_height);
		free(data);
		exit(1);
	}
	free_2d_array_update(copied_map, data->map_height);
}
