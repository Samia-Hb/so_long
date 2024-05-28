#include "so_long.h"

void affiche_map(t_data *data)
{
	// printf("check\n");
	printf("map_height = %d\n", data->map_height);
	printf("map_width = %d\n", data->map_width);
	int i = 0;
	int j;
	while (i < data->map_height)
	{
		j = 0;
		while(j < data->map_width)
		{
			printf("%c",data->map[i][j]);
			j++;
		}
		i++;
	}
}
// int calcul_line_length(char *str)
void check_arguments(t_data *data, char **av)
{
    int	i;
    int	j;
    int fd;
	int	width;
	char	*str;
	int		p_nbr;
	int		e_nbr;

	int height = data->map_height;
	p_nbr = 0;
	e_nbr = 0;
	// printf("map_height = %d\n",data->map_height);
	width = ft_strlen(data->map[0]);
    i = 1;
	printf("main_width = %d\n",width);
	affiche_map(data);
	while (data->map[i] && i < height)
	{
		printf("i = %d\n", i);
		printf("main_width = %d\n",ft_strlen(data->map[i]));
		if (width != ft_strlen(data->map[i]))
			break;
		i++;
	}
	printf("i = %d\n", i);
	//printf("limit = %d\n", data->map_height - 1);
	if (i == (data->map_height) - 1)
		return ;
	else
	{
		perror("Error : map is not a rectangle");
		clear_data(data);
		exit(1);
	}
	//printf("hey");
	///calcul if the map's form is rectangle

	// fd = open(av[1], O_RDWR, 0777);
	// if(fd == -1)
	// {
	// 	clear_data(data);
	// 	exit(1);
	// }
	// str = get_next_line(fd);
	// width = ft_strlen(str);
	// printf("width_to_compare = %d\n", width);
	// while (1)
	// {
	// 	str = get_next_line(fd);
	// 	printf("width = %d\n", ft_strlen(str));
	// 	if(!str)
	// 		break;
	// 	if (width != ft_strlen(str))
	// 	{
	// 		perror("Error : map is not a rectangle");
	// 		clear_data(data);
	// 		exit(1);
	// 	}
	// }

	///
    while (i < data->map_height)
    {
        j = 0;
        while (j < data->map_width)
        {
            if (data->map[i][j] == 'P')
				p_nbr++;
			if (data->map[i][j] == 'E')
				e_nbr++;
        }
    }
	if (p_nbr > 1 || e_nbr > 1)
	{
		perror("Error : more than expected");
		clear_data(data);
		exit(1);
	}
	if (data->coins_nbr < 1)
	{
		perror("Error : At Least one coin required");
		clear_data(data);
		exit(1);
	}
}