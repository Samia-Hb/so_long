#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line/get_next_line.h"

#define TILE_SIZE 50 // Size of each tile
#define WINDOWS_HEIGHT 600
#define WINDOWS_WIDTH 500



typedef struct s_data
{
    void *mlx_ptr;
    void *win_ptr;
    void *wall;
    void *player[3];
    void *road;
    void *coins;
    void *exit;
    char **map;
    int tex_width;
    int tex_height;
	int x;
	int y;
	int coins_nbr;
	int map_height;
} t_data;

void free_2d_array(char **array, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(array[i]);
    }
    free(array);
}
void clear_data(t_data *data) {
    if (data->map) {
        free_2d_array(data->map, data->map_height);
    }
    if (data->mlx_ptr) {
        if (data->win_ptr) {
            mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        }
        if (data->wall) {
            mlx_destroy_image(data->mlx_ptr, data->wall);
        }
        if (data->road) {
            mlx_destroy_image(data->mlx_ptr, data->road);
        }
        if (data->coins) {
            mlx_destroy_image(data->mlx_ptr, data->coins);
        }
        for (int i = 0; i < 3; ++i) {
            if (data->player[i]) {
                mlx_destroy_image(data->mlx_ptr, data->player[i]);
            }
        }
        if (data->exit) {
            mlx_destroy_image(data->mlx_ptr, data->exit);
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
        while (y < width && y < WINDOWS_WIDTH) {
            data->map[x][y] = str[y];
			y++;
        }
		data->map[x][width] = '\0';
        free(str);
    	x++;
	}
    close(fd);
}

void draw_map(t_data *data, int width, int height) {
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
		clear_data(data);
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
		clear_data(data);
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
		clear_data(data);
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
		clear_data(data);
        exit(0);
	}
}
int handle_key(int keycode, t_data *data)
{
    if (keycode == 65307)//ESC
    {
		clear_data(data);
		exit(0);
	}
    else if(keycode == 0x0077)//W
        go_up(data);
    else if(keycode == 0x0073)//S
        go_down(data);
    else if(keycode == 0x0061)//A
        go_left(data);
    else if(keycode == 0x0064)//D
        go_right(data);
    return 0;
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
        clear_data(data);
        return 1;
    }
    width = strlen(str);
    height = 1;
    free(str);

    while ((str = get_next_line(fd)) != NULL)
    {
        height++;
        free(str);
    }

    data->map_height = height;  // Set map_height after allocating data

    close(fd);

    data->mlx_ptr = mlx_init();
    if (!data->mlx_ptr)
    {
        free(data);
        return 1;
    }

    map_2d_array(data, av, width, height);
    check_arguments(data->map);
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
        clear_data(data);
        return 1;
    }

    draw_map(data, width, height);
    mlx_key_hook(data->win_ptr, handle_key, data);
    mlx_loop(data->mlx_ptr);
    clear_data(data);
    return 0;
}