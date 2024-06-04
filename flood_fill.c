/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:37:54 by shebaz            #+#    #+#             */
/*   Updated: 2024/06/04 13:38:57 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void flood_fill(t_data *data, int x, int y, int *coins_nbr)
{
    printf("data[%d][%d] = %c", x, y, data->map[x][y]);
    if (data->map[x][y] != '0' && data->map[x][y] != 'C' && data->map[x][y] != 'E' && data->map[x][y] != 'P' && data->map[x][y] != 's')
    {
        printf("check\n");
        return ;
    }    
    printf("check\n");
    if (data->map[x][y] == 'C' || data->map[x][y] == 'c')
        (*coins_nbr)++;
    printf("coins = %d\n", *coins_nbr);
    data->map[x][y] = 's';
    while (data->map[x][y] != '1')
    {
        flood_fill(data,x+1, y, coins_nbr);
        flood_fill(data,x-1, y, coins_nbr);
        flood_fill(data,x+1, y - 1, coins_nbr);
        flood_fill(data,x+1, y - 1, coins_nbr);
    }
}

void check_path(t_data *data)
{
    int coins_nbr;
	int	i;
	int	j;

	i = data->x;
	j = data->y;
    coins_nbr = 0;
    flood_fill(data, i , j, &coins_nbr);
    printf("current coins number = %d\n", coins_nbr);
    printf("coins number = %d\n", data->coins_nbr);
    if (data->coins_nbr != coins_nbr || data->map[i][j] != 'E')
    {
        perror("Error\n");
        clear_data(data, 0);
        exit(1);
    }
}