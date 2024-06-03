/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:42:37 by shebaz            #+#    #+#             */
/*   Updated: 2024/06/03 22:11:31 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	fill_the_array(t_data *data, int fd, int x, int y)
{
	char	*str;

	str = NULL;
	while (x < data->map_height && x < WINDOWS_HEIGHT)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		data->map[x] = malloc((data->map_width + 1) * sizeof(char));
		if (!data->map[x])
			free_map(data->map, x, fd);
		y = 0;
		while (y < data->map_width && y < WINDOWS_WIDTH)
		{
			data->map[x][y] = str[y];
			if (str[y] == 'C' || str[y] == 'c')
				data->coins_nbr++;
			y++;
		}
		data->map[x][data->map_width] = '\0';
		free(str);
		x++;
	}
}

void	map_2d_array(t_data *data, char **av)
{
	int	fd;
	int	x;
	int	y;

	x = 0;
	y = 0;
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	data->map = malloc(data->map_height * sizeof(char *));
	if (!data->map)
	{
		perror("malloc failed for map");
		close(fd);
		exit(EXIT_FAILURE);
	}
	fill_the_array(data, fd, x, y);
	close(fd);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (!n)
		return (0);
	while (i < n - 1 && s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

void	initial_struct(t_data *data) // work
{
	data->coins_nbr = 0;
	data->map_height = 0;
	data->e_nbr = 0;
	data->p_nbr = 0;
}

void	calcul_width_height(t_data *data, char **av, char *str)
{
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		clear_exit(data);
	}
	str = get_next_line(fd);
	if (!str)
	{
		perror("Error reading file");
		close(fd);
		clear_exit(data);
	}
	data->map_width = ft_strlen(str);
	free(str);
	while (str)
	{
		str = get_next_line(fd);
		(data->map_height)++;
		free(str);
	}
	close(fd);
	free(str);
}
