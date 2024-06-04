/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:37:54 by shebaz            #+#    #+#             */
/*   Updated: 2024/06/04 23:43:39 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// void free_2d_array_update(char **array, int height)
// {
//     for (int i = 0; i < height; i++)
//         free(array[i]);
//     free(array);
// }

// char	**copy_map(t_data *data)
// {
// 	int		x;
// 	int		y;
// 	char	**copied_map;

// 	x = 0;
// 	copied_map = malloc((data->map_height + 1) * sizeof(char *));
// 	if (!copied_map)
// 		return (NULL);
// 	while (x < data->map_height)
// 	{
// 		copied_map[x] = malloc((data->map_width + 1) * sizeof(char));
// 		if (!copied_map[x])
// 			return (free_2d_array_update(copied_map, data->map_height), NULL);
// 		y = 0;
// 		while (y < data->map_width)
// 		{
// 			copied_map[x][y] = data->map[x][y];
// 			y++;
// 		}
// 		copied_map[x][y] = '\0';
// 		x++;
// 	}
// 	copied_map[data->map_height] = NULL;
// 	return (copied_map);
// }

// void	flood_fill(char **map, int x, int y, int *coins_nbr, int height, int width)
// {
// 	if (map[x][y] != '0' && map[x][y] != 'C' && map[x][y] != 'E'
// 		&& map[x][y] != 'P' && x < height || y < width)
// 		return ;
// 	if (map[x][y] == 'C')
// 		(*coins_nbr)++;
// 	map[x][y] = 's';
// 	flood_fill(map, x + 1, y, coins_nbr, height, width);
// 	flood_fill(map, x - 1, y, coins_nbr, height, width);
// 	flood_fill(map, x, y + 1, coins_nbr, height, width);
// 	flood_fill(map, x, y - 1, coins_nbr, height, width);
// }

// void	check_path(t_data *data)
// {
// 	int		coins_nbr;
// 	char	**copied_map;

// 	copied_map = copy_map(data);
// 	if (!copied_map)
// 	{
// 		perror("Error\n");
// 		exit(1);
// 	}
// 	coins_nbr = 0;
// 	flood_fill(copied_map, data->x, data->y, &coins_nbr, data->map_height, data->map_width);
// 	if (data->coins_nbr != coins_nbr)
// 	{
// 		perror("Error : no valid path");
// 		free_2d_array_update(copied_map, data->map_height);
// 		exit(1);
// 	}
// 	free_2d_array_update(copied_map, data->map_height);
// }

#include "so_long.h"

void free_2d_array_update(char **array, int height)
{
    for (int i = 0; i < height; i++)
        free(array[i]);
    free(array);
}

char **copy_map(t_data *data)
{
    int x, y;
    char **copied_map;

    copied_map = malloc((data->map_height + 1) * sizeof(char *));
    if (!copied_map)
        return NULL;

    for (x = 0; x < data->map_height; x++)
    {
        copied_map[x] = malloc((data->map_width + 1) * sizeof(char));
        if (!copied_map[x])
        {
            free_2d_array_update(copied_map, x);
            return NULL;
        }
        for (y = 0; y < data->map_width; y++)
        {
            copied_map[x][y] = data->map[x][y];
        }
        copied_map[x][y] = '\0';
    }
    copied_map[data->map_height] = NULL; // Null-terminate the array of rows
    return copied_map;
}

void flood_fill(char **map, int x, int y, int *coins_nbr, int height, int width)
{
    if (x < 0 || y < 0 || x >= height || y >= width) // Check bounds
        return;
    if (map[x][y] != '0' && map[x][y] != 'C' && map[x][y] != 'E' && map[x][y] != 'P')
        return;
    if (map[x][y] == 'C')
        (*coins_nbr)++;
    map[x][y] = 's';
    flood_fill(map, x + 1, y, coins_nbr, height, width);
    flood_fill(map, x - 1, y, coins_nbr, height, width);
    flood_fill(map, x, y + 1, coins_nbr, height, width);
    flood_fill(map, x, y - 1, coins_nbr, height, width);
}

void check_path(t_data *data)
{
    int coins_nbr;
    char **copied_map;

    copied_map = copy_map(data);
    if (!copied_map)
    {
        perror("Error\n");
        exit(1);
    }
    coins_nbr = 0;
    flood_fill(copied_map, data->x, data->y, &coins_nbr, data->map_height, data->map_width);
    if (data->coins_nbr != coins_nbr)
    {
        perror("Error : no valid path");
        free_2d_array_update(copied_map, data->map_height);
        exit(1);
    }

    free_2d_array_update(copied_map, data->map_height);
}

