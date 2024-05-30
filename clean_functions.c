/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:45:26 by shebaz            #+#    #+#             */
/*   Updated: 2024/05/30 13:46:58 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int close_window(t_data *data)
{
    clear_data(data, 0);
    exit(1);
    return (0);
}

void free_2d_array(char **array, int rows) //work
{
    int i;
    
    i = 0;
    while (i < rows)
    {
        free(array[i]);
        i++;
    }
    free(array);
}

void clear_data(t_data *data, int i)//work
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