#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "so_long.h"
#include "minilibx-linux/mlx.h"
#include "get_next_line/get_next_line.h" // Include your implementation of get_next_line


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

void fill_the_array(t_data *data, int fd, int x, int y)
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
}

void map_2d_array(t_data *data, char **av)
{
    int fd;
    int x;
    int y;

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

void draw_map(t_data *data, int x, int y)
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
            }
            y++;
        }
        x++;
    }
}

void initial_struct(t_data *data)
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
    data->e_x_pos = 0;
    data->e_y_pos = 0;
    data->enemy_direction = 1; // Start by moving right
}

void picture_loading(t_data *data)
{
    data->wall = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/wall.xpm", &data->tex_width, &data->tex_height);
    data->road = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/road.xpm", &data->tex_width, &data->tex_height);
    data->coins = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/coins.xpm", &data->tex_width, &data->tex_height);
    data->player[0] = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/player.xpm", &data->tex_width, &data->tex_height);
    data->player[1] = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/player_right.xpm", &data->tex_width, &data->tex_height);
    data->player[2] = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/player_left.xpm", &data->tex_width, &data->tex_height);
    data->exit = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/exit.xpm", &data->tex_width, &data->tex_height);
    if (!data->wall || !data->road || !data->coins || !data->player[0] || !data->player[1] || !data->player[2] || !data->exit)
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

int animation(t_data *data)
{
    int next_y_pos;

    next_y_pos = data->e_y_pos + data->enemy_direction;

    // Check if the next position is a wall or an obstacle
    if (data->map[data->e_x_pos][next_y_pos] == '1' || 
        data->map[data->e_x_pos][next_y_pos] == 'c' || 
        data->map[data->e_x_pos][next_y_pos] == 'C' || 
        data->map[data->e_x_pos][next_y_pos] == 'E')
    {
        // Change direction
        data->enemy_direction *= -1;
        next_y_pos = data->e_y_pos + data->enemy_direction;
    }

    // Clear the old position
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->road, data->e_y_pos * TILE_SIZE, data->e_x_pos * TILE_SIZE);
    // Update enemy position
    data->e_y_pos = next_y_pos;
    // Draw the new position
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->enemy[0], data->e_y_pos * TILE_SIZE, data->e_x_pos * TILE_SIZE);

    usleep(100000); // Sleep for 100 milliseconds

    return 1;
}

int handle_key(int key, t_data *data)
{
    // Handle key press events here
    return 0;
}

int close_window(t_data *data)
{
    // Free resources and exit the program
    clear_exit(data);
    return 0;
}

void check_arguments(t_data *data, char **av)
{
    // Implement any necessary argument checks here
}

void clear_exit(t_data *data)
{
    // Free all resources and exit the program
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
        if (data->player[0])
            mlx_destroy_image(data->mlx_ptr, data->player[0]);
        if (data->player[1])
            mlx_destroy_image(data->mlx_ptr, data->player[1]);
        if (data->player[2])
            mlx_destroy_image(data->mlx_ptr, data->player[2]);
        if (data->exit)
            mlx_destroy_image(data->mlx_ptr, data->exit);
        if (data->enemy[0])
            mlx_destroy_image(data->mlx_ptr, data->enemy[0]);
        if (data->enemy[1])
            mlx_destroy_image(data->mlx_ptr, data->enemy[1]);
        if (data->enemy[2])
            mlx_destroy_image(data->mlx_ptr, data->enemy[2]);
        if (data->enemy[3])
            mlx_destroy_image(data->mlx_ptr, data->enemy[3]);
        if (data->enemy[4])
            mlx_destroy_image(data->mlx_ptr, data->enemy[4]);
        if (data->enemy[5])
            mlx_destroy_image(data->mlx_ptr, data->enemy[5]);
    }
    if (data->map)
    {
        for (int i = 0; i < data->map_height; i++)
        {
            if (data->map[i])
                free(data->map[i]);
        }
        free(data->map);
    }
    free(data);
    exit(EXIT_SUCCESS);
}

void clear_data(t_data *data, int i)
{
    // Free resources without exiting the program
    if (data->map)
    {
        while (i < data->map_height)
        {
            free(data->map[i]);
            i++;
        }
        free(data->map);
    }
}

int main(int ac, char **av)
{
    t_data *data;

    if (ac < 2)
        return 1;
    data = malloc(sizeof(t_data));
    if (!data)
        return 1;
    initial_struct(data);
    calcul_width_height(data, av);
    map_2d_array(data, av);
    check_arguments(data, av);
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
    draw_map(data, 0, 0);
    mlx_key_hook(data->win_ptr, handle_key, data);
    mlx_hook(data->win_ptr, 17, 0, close_window, data);
    mlx_loop_hook(data->win_ptr, animation, data);
    mlx_loop(data->mlx_ptr);
    clear_data(data, 0);
    return 0;
}
