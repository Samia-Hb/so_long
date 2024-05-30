/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:34:15 by shebaz            #+#    #+#             */
/*   Updated: 2024/05/29 18:04:55 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
void map_2d_array(t_data *data, char **av, int width, int height) {
    int fd = open(av[1], O_RDONLY);
    if (fd == -1)
        exit(EXIT_FAILURE);

    data->map = malloc(height * sizeof(char *));
    if (!data->map) {
        perror("malloc failed for map");
        close(fd);
        exit(EXIT_FAILURE);
    }
	int x = 0;
	int y;
    while (x < height && x < WINDOWS_HEIGHT)
	{
        char *str = get_next_line(fd);
        if (!str)
		{
            perror("Error reading file");
            for (int i = 0; i < x; i++) {
                free(data->map[i]);
            }
            free(data->map);
            close(fd);
            exit(EXIT_FAILURE);
        }

        data->map[x] = malloc((width + 1) * sizeof(char));
        if (!data->map[x]) {
            perror("malloc failed for map row");
            free(str);
            for (int i = 0; i < x; i++) {
                free(data->map[i]);
            }
            free(data->map);
            close(fd);
            exit(EXIT_FAILURE);
        }
		y = 0;
        while (y < width && y < WINDOWS_WIDTH)
        {
            data->map[x][y] = str[y];
            if (str[y] == 'C' || str[y] == 'c')
            {
                data->coins_nbr++;
            }
            y++;
        }
		data->map[x][width] = '\0';
        free(str);
    	x++;
	}
    close(fd);
}

void draw_map(t_data *data, int width, int height)
{
    int y;
	int	x;

	x = 0;
	while (x < height)
	{
		y = 0;
        while (y < width)
		{
            if (data->map[x][y] == '1')
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->wall, y * TILE_SIZE, x * TILE_SIZE);
            else if (data->map[x][y] == '0')
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->road, y * TILE_SIZE, x * TILE_SIZE);
            else if (data->map[x][y] == 'c' || data->map[x][y] == 'C')
			{
				data->coins_nbr++;
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->coins, y * TILE_SIZE, x * TILE_SIZE);
			}
			else if (data->map[x][y] == 'P')
			{
				data->x = x;
				data->y = y;
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player[0], y * TILE_SIZE, x * TILE_SIZE);
			}
			else if (data->map[x][y] == 'E')
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->exit, y * TILE_SIZE, x * TILE_SIZE);
			y++;
		}
		x++;
    }
}

void go_up(t_data *data)
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

void go_down(t_data *data)
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

void go_right(t_data *data)
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

void go_left(t_data *data)
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
void initial_struct(t_data *data)//work
{
    int i;

    i = 0;
    data->coins = NULL;
    data->wall = NULL;
    while(i < 3)
    {
       data->player[i] = NULL;
       i++;
    }
    data->exit = NULL;
    data->road = NULL;
    data->win_ptr = NULL;
    data->mlx_ptr = NULL;
    data->map = NULL;
}

int main(int ac, char **av)
{
    t_data *data;
    char *str;
    int width;
    int height;

    if (ac < 2)
        return 1;

    data = malloc(sizeof(t_data));
    if (!data)
        return 1;
    initial_struct(data);
    int fd = open(av[1], O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        free(data);
        return 1;
    }
    str = get_next_line(fd);
    if (!str)
    {
        perror("Error reading file");
        close(fd);
        clear_data(data, 0);
        return 1;
    }
    width = strlen(str);
    data->map_width = width;
    data->coins_nbr = 0;
    height = 1;
    free(str);

    while ((str = get_next_line(fd)) != NULL)
    {
        height++;
        free(str);
    }
    close(fd);
    data->map_height = height;
    map_2d_array(data, av, width, height);
    check_arguments(data,av);
    data->mlx_ptr = mlx_init();
    if (!data->mlx_ptr)
    {
        free(data);
        return 1;
    }
	data->win_ptr = mlx_new_window(data->mlx_ptr, width * TILE_SIZE, height * TILE_SIZE, "So_long");
    if (!data->win_ptr)
    {
        mlx_destroy_display(data->mlx_ptr);
        free(data->map);
        free(data->mlx_ptr);
        free(data);
        return 1;
    }

    data->wall = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/wall.xpm", &data->tex_width, &data->tex_height);
    data->road = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/road.xpm", &data->tex_width, &data->tex_height);
    data->coins = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/coins.xpm", &data->tex_width, &data->tex_height);
    data->player[0] = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/player.xpm", &data->tex_width, &data->tex_height);
    data->player[1] = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/player_right.xpm", &data->tex_width, &data->tex_height);
    data->player[2] = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/player_left.xpm", &data->tex_width, &data->tex_height);
    data->exit = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/exit.xpm", &data->tex_width, &data->tex_height);

    if (!data->wall || !data->road || !data->coins || !data->player[0] || !data->exit)
    {
        perror("Failed to load one or more textures");
        clear_data(data, 0);
        return 1;
    }
    draw_map(data, width, height);
    mlx_key_hook(data->win_ptr, handle_key, data);
    mlx_loop(data->mlx_ptr);
    clear_data(data, 0);
    return 0;
}