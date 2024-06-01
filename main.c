/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:34:15 by shebaz            #+#    #+#             */
/*   Updated: 2024/06/01 15:15:39 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void free_map(char **map, int x, int fd)
{
    int i;

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
void fill_the_array(t_data *data, int fd,int x, int y)
{
	char *str;

	while (x < data->map_height && x < WINDOWS_HEIGHT)
	{
        str = get_next_line(fd);
        if (!str)
            free_map(data->map, x, fd);
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
	// if (str)
		// free(str);
}
void map_2d_array(t_data *data, char **av)
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


void draw_map(t_data *data, int x, int y)//work
{
	while (x < data->map_height)
	{
		y = 0;
        while (y < data->map_width)
		{
            if (data->map[x][y] == '1')
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->wall, y * TILE_SIZE, x * TILE_SIZE);
            else if (data->map[x][y] == '0')
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->road, y * TILE_SIZE, x * TILE_SIZE);
            else if (data->map[x][y] == 'c' || data->map[x][y] == 'C')
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->coins, y * TILE_SIZE, x * TILE_SIZE);
			else if (data->map[x][y] == 'P')
			{
				data->x = x;
				data->y = y;
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player[0], y * TILE_SIZE, x * TILE_SIZE);
			}
			else if (data->map[x][y] == 'E')
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->exit, y * TILE_SIZE, x * TILE_SIZE);
            else if (data->map[x][y] == 'e')
            {
                data->e_x_pos = x;
                data->e_y_pos = y;
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->enemy[0], y * TILE_SIZE, x * TILE_SIZE);
                // printf("enemy_position(%d,%d)",data->e_x_pos, data->e_y_pos);
            }
            y++;
		}
		x++;
    }
}

void initial_struct(t_data *data)//work
{
    int i;

    i = 0;
    data->coins = NULL;
	data->coins_nbr = 0;
	data->map_height = 1;
    data->wall = NULL;
    while (i < 3)
    {
       data->player[i] = NULL;
       i++;
    }
    data->exit = NULL;
    data->road = NULL;
    data->win_ptr = NULL;
    data->mlx_ptr = NULL;
    data->map = NULL;

    data->frame_count = 6;
    data->current_frame = 0;
    data->frame_delay = 80;
    data->frame_delay_counter = 0;
}

void picture_loading(t_data *data)
{
    data->wall =  mlx_xpm_file_to_image(data->mlx_ptr, "./assests/wall.xpm", &data->tex_width, &data->tex_height);
    data->road =  mlx_xpm_file_to_image(data->mlx_ptr, "./assests/road.xpm", &data->tex_width, &data->tex_height);
    data->coins = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/coins.xpm", &data->tex_width, &data->tex_height);
    data->player[0] = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/player.xpm", &data->tex_width, &data->tex_height);
    data->player[1] = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/player_right.xpm", &data->tex_width, &data->tex_height);
    data->player[2] = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/player_left.xpm", &data->tex_width, &data->tex_height);
    data->exit = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/exit.xpm", &data->tex_width, &data->tex_height);
    if (!data->wall || !data->road || !data->coins || !data->player[0] || !data->player[1] || !data->player[2] || 
    !data->exit)
    {
        perror("Failed to load one or more textures");
        clear_exit(data);
    }
    data->enemy[0] = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/bonus_assests/1.xpm", &data->tex_width, &data->tex_height);
    data->enemy[1] = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/bonus_assests/2.xpm", &data->tex_width, &data->tex_height);
    data->enemy[2] = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/bonus_assests/3.xpm", &data->tex_width, &data->tex_height);
    data->enemy[3] = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/bonus_assests/4.xpm", &data->tex_width, &data->tex_height);
    data->enemy[4] = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/bonus_assests/5.xpm", &data->tex_width, &data->tex_height);
    data->enemy[5] = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/bonus_assests/6.xpm", &data->tex_width, &data->tex_height);

    data->frame_count = 6;
    data->current_frame = 0;
    data->frame_delay = 80;
    data->frame_delay_counter = 0;
}
void calcul_width_height(t_data *data, char **av)
{
    char *str;
    int fd;

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
    while ((str = get_next_line(fd)))
    {
        free(str);
        (data->map_height)++;
    }
    close(fd);
    free(str);
}
////////////////

void update_frame(t_data *data)
{
    data->frame_delay_counter++;
    if (data->frame_delay_counter >= data->frame_delay)
    {
        data->frame_delay_counter = 0;
        data->current_frame = (data->current_frame + 1) % data->frame_count;
    }
}

int animation(t_data *data)
{
    update_frame(data);
    data->e_y_pos++;
    if (data->e_y_pos >= data->map_width)
        data->e_y_pos = 0;
    mlx_clear_window(data->mlx_ptr, data->win_ptr);
    draw_map(data, 0, 0);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->enemy[data->current_frame], data->e_y_pos * TILE_SIZE, data->e_x_pos * TILE_SIZE);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player[0], data->y * TILE_SIZE, data->x * TILE_SIZE);
    return (0);
}

// void update_frame(t_data *data)
// {
//     data->current_frame++;
//     if (data->frame_delay_counter <= data->frame_delay)
//     {
//         mlx_put_image_to_window(data->mlx_ptr,data->win_ptr, data->enemy[data->current_frame], data->e_x_pos * TILE_SIZE, data->e_x_pos * TILE_SIZE);
//     }  
// }
// int animation(t_data *data)
// {
//     update_frame(data);
//     return (0);
// }

int main(int ac, char **av)
{
    t_data *data;

    if (ac < 2)
        return 1;
    data = malloc(sizeof(t_data));
    if (!data)
        return (1);
    initial_struct(data);
	calcul_width_height(data,av);
    map_2d_array(data, av);
    check_arguments(data,av);
    data->mlx_ptr = mlx_init();
    if (!data->mlx_ptr)
	{ 
        clear_exit(data);
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->map_width * TILE_SIZE, data->map_height * TILE_SIZE, "So_long");
    if (!data->win_ptr)
	{
        clear_exit(data);
	}
	picture_loading(data);
    draw_map(data,0 , 0);
    mlx_key_hook(data->win_ptr, handle_key, data);
    mlx_hook(data->win_ptr,17 ,0 ,close_window, data);
    mlx_loop_hook(data->mlx_ptr, animation, data);
    mlx_loop(data->mlx_ptr);
    clear_data(data, 0);
    return 0;
}

// int animation(t_data *data)
// {
//     int x = data->e_x_pos;
//     int y = data->e_y_pos;
//     while (data->map[data->e_x_pos][data->e_y_pos] != '1' && data->map[data->e_x_pos][data->e_y_pos] != 'c' && data->map[data->e_x_pos][data->e_y_pos] != 'C' && data->map[data->e_x_pos][data->e_y_pos] != 'E')
//     {
//         mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->enemy[0], (y + 1) * TILE_SIZE, x * TILE_SIZE);
//         mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->road, y * TILE_SIZE, x * TILE_SIZE);
//         data->e_x_pos = x;
//         data->e_y_pos = y + 1;
//     }
//     while (data->map[data->e_x_pos][data->e_y_pos] != '1' && data->map[data->e_x_pos][data->e_y_pos] != 'c' && data->map[data->e_x_pos][data->e_y_pos] != 'C' && data->map[data->e_x_pos][data->e_y_pos] != 'E')
//     {
//         mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->enemy[0], (y + 1) * TILE_SIZE, x * TILE_SIZE);
//         mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->road, y * TILE_SIZE, x * TILE_SIZE);
//         data->e_x_pos = x;
//         data->e_y_pos = y - 1;
//     }
//     return (1);
// }


//////////////