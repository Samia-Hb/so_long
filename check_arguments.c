/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:31:38 by shebaz            #+#    #+#             */
/*   Updated: 2024/05/29 20:04:13 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void clear_exit(t_data *data)
{
	clear_data(data, 0);
	exit(1);
}

void check_form(t_data *data, char **av)
{
    int  fd;
    char *str;
    int  i;
    int  width;

    width = 0;
    fd = open(av[1], O_RDWR, 0777);
    if (fd == -1)
        clear_exit(data);
    width = data->map_width;
    i = 0;
    while (1)
    {
        str = get_next_line(fd);
        if (!str)
            break;
        if (width != ft_strlen(str))
            break;
        free(str);
        i++;
    }
    if (str)
        free(str);
    close(fd);
    if (i != (data->map_height - 1) || (i == (data->map_height - 1) && ft_strlen(data->map[data->map_height - 1]) != width - 1 && data->map_height != 1))
    {
        perror("Error : map is not a rectangle");
        clear_exit(data);
    }
}


void	check_parameters_number(t_data *data, int p_nbr, int e_nbr)
{
	if (p_nbr > 1 || e_nbr > 1)
	{
		perror("Error : more than expected");
		clear_data(data, 0);
		exit(1);
	}
	if (data->coins_nbr < 1)
	{
		perror("Error : At Least one coin required");
		clear_data(data, 0);
		exit(1);
	}
}

void check_borders(t_data *data)
{
	int i;
	int j;
	int tmp;

	i = 0;
	j = 0;
	tmp = 1;
	while (j < data->map_width - 1)
	{
		if (data -> map[0][j] != '1' || data ->map[data->map_height - 1][j] != '1')
			tmp = 0;
		j++;
	}
	while (i < data->map_height)
	{
		if(data-> map[i][0] != '1' || data ->map[i][data->map_width - 2] != '1')
			tmp = 0;
		i++;
	}
	if (!tmp)
	{
		perror("Error");
		clear_exit(data);
	}
}

void check_arguments(t_data *data, char **av)
{
    int	i;
    int	j;
	int	p_nbr;
	int	e_nbr;

	i = 0;
	p_nbr = 0;
	e_nbr = 0;
	// (void)av;
	check_form(data, av);
	check_borders(data);
    while (i < data->map_height)
    {
        j = 0;
        while (j < data->map_width)
        {
            if (data->map[i][j] == 'P')
				p_nbr++;
			if (data->map[i][j] == 'E')
				e_nbr++;
			j++;
        }
		i++;
    }
	check_parameters_number(data, p_nbr,e_nbr);
}
// void affiche_map(t_data *data)
// {
// 	// printf("check\n");
// 	printf("map_height = %d\n", data->map_height);
// 	printf("map_width = %d\n", data->map_width);
// 	int i = 0;
// 	int j;
// 	while (i < data->map_height)
// 	{
// 		j = 0;
// 		while(j < data->map_width)
// 		{
// 			printf("%c",data->map[i][j]);
// 			j++;
// 		}
// 		i++;
// 	}
// }