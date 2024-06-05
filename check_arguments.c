/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:31:38 by shebaz            #+#    #+#             */
/*   Updated: 2024/06/05 16:01:16 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_form(t_data *data)
{
	int	width;
	int	i;

	i = 0;
	width = data->map_width;
	while (i < data->map_height)
	{
		if (width != ft_strlen(data->map[i]))
			break ;
		i++;
	}
	if (i != (data->map_height - 1) || (i == (data->map_height - 1)
			&& ft_strlen(data->map[data->map_height - 1]) != data->map_width - 1
			&& data->map_height != 1))
	{
		perror("Error : map is not a rectangle");
		free_2d_array(data->map, data->map_height);
		free(data);
		exit(1);
	}
}

void	check_parameters_number(t_data *data, int i, int j) // work
{
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			if (data->map[i][j] == 'P')
				data->p_nbr++;
			if (data->map[i][j] == 'E')
				data->e_nbr++;
			j++;
		}
		i++;
	}
	if (data->p_nbr > 1 || data->e_nbr > 1)
	{
		perror("Error : more than expected");
		clear_exit(data);
	}
	if (data->coins_nbr < 1)
	{
		perror("Error : At Least one coin required");
		clear_exit(data);
	}
}

void	check_borders(t_data *data)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = 0;
	tmp = 1;
	while (j < data->map_width - 1)
	{
		if (data->map[0][j] != '1' || data->map[data->map_height - 1][j] != '1')
			tmp = 0;
		j++;
	}
	while (i < data->map_height)
	{
		if (data->map[i][0] != '1' || data->map[i][data->map_width - 2] != '1')
			tmp = 0;
		i++;
	}
	if (!tmp)
	{
		perror("Error");
		clear_exit(data);
	}
}

void	check_characters(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_height - 1)
	{
		j = 0;
		while (j < data->map_width - 1)
		{
			if (data->map[i][j] != '1' && data->map[i][j] != '0'
				&& data->map[i][j] != 'P' && data->map[i][j] != 'C'
				&& data->map[i][j] != 'c' && data->map[i][j] != 'E')
			{
				perror("Error\n");
				clear_exit(data);
			}
			j++;
		}
		i++;
	}
}

void	check_arg(t_data *data, char **av)
{
	int		i;
	char	*str;

	i = 0;
	str = av[1];
	while (i <= ft_strlen(av[1]) - 5)
	{
		str++;
		i++;
	}
	if (ft_strncmp(str, ".ber", 4))
		clear_exit(data);
}
