#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line/get_next_line.h"

#define TILE_SIZE 50 // Size of each tile
#define WINDOWS_HEIGHT 600
#define WINDOWS_WIDTH 500

typedef struct {
    int height;
    int width;
    char *name;
} t_map;

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
} t_data;

void map_2d_array(t_data *data, char **av, int len, int height) {
    int fd = open(av[1], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(1);
    }

    data->map = malloc(height * sizeof(char *));
    if (!data->map) {
        perror("malloc failed");
        exit(1);
    }

    for (int y = 0; y < height; y++) {
        char *str = get_next_line(fd);
        if (!str) {
            perror("Error reading file");
            exit(1);
        }
        data->map[y] = malloc(len * sizeof(char));
        if (!data->map[y]) {
            perror("malloc failed");
            exit(1);
        }
        for (int x = 0; x < len; x++) {
            data->map[y][x] = str[x];
        }
        free(str);
    }
    close(fd);
}

void draw_map(t_data *data, int length, int height) {
    int y;
	int	x;

	x = 0;
	while (x < height && x < WINDOWS_WIDTH)
	{
		y = 0;
        while (y < length && y < WINDOWS_HEIGHT)
		{
            if (data->map[x][y] == '1')
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->wall, x * TILE_SIZE, y * TILE_SIZE);
            else if (data->map[x][y] == '0')
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->road, x * TILE_SIZE, y * TILE_SIZE);
            else if (data->map[x][y] == 'c' || data->map[y][x] == 'C')
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->coins, x * TILE_SIZE, y * TILE_SIZE);
            else if (data->map[x][y] == 'P')
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player[0], x * TILE_SIZE, y * TILE_SIZE);
            else if (data->map[x][y] == 'E')
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->exit, x * TILE_SIZE, y * TILE_SIZE);
			y++;
		}
		x++;
    }
}

void go_up(t_data *data)
{
	if (data->map[data->x][(data->y) - 1] == '1' || data->coins_nbr != 0 && data->map[data->x][(data->y) - 1] == 'E')
		return ;
	else if (data->map[data->x][(data->y) - 1] == '0')
	{
		mlx_put_image_to_window(data->mlx_ptr,data->win_ptr,data->player[0],data->x, data->y - 1);
		mlx_put_image_to_window(data->mlx_ptr,data->win_ptr,data->road,data->x, data->y);
	}
	else if (data->map[data->x][(data->y) - 1] == 'c' || data->map[data->x][(data->y) - 1] == 'C')
	{
		(data->coins_nbr)--;
		mlx_put_image_to_window(data->mlx_ptr,data->win_ptr,data->player[0],data->x, data->y - 1);
		mlx_put_image_to_window(data->mlx_ptr,data->win_ptr,data->road,data->x, data->y);
	}
	else if (data->map[data->x][(data->y) - 1] == 'E' && !(data->coins_nbr))
		exit(1);
}
void go_down(t_data *data)
{
	if (data->map[data->x][(data->y) + 1] == '1' || data->coins_nbr != 0 && data->map[data->x][(data->y) + 1] == 'E')
		return ;
	else if (data->map[data->x][(data->y) + 1] == '0')
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player[0], data->x, data->y + 1);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->road, data->x, data->y);
	}
	else if (data->map[data->x][(data->y) + 1] == 'c' || data->map[data->x][(data->y) + 1] == 'C')
	{
		(data->coins_nbr)--;
		mlx_put_image_to_window(data->mlx_ptr,data->win_ptr,data->player[0],data->x, data->y + 1);
		mlx_put_image_to_window(data->mlx_ptr,data->win_ptr,data->road,data->x, data->y);
	}
	else if (data->map[data->x][(data->y) + 1] == 'E' && !(data->coins_nbr))
		exit(1);
}

void go_right(t_data *data)
{
	if (data->map[(data->x) + 1][data->y] == '1' || data->coins_nbr != 0 && data->map[(data->x) + 1][data->y] == 'E')
		return ;
	else if (data->map[(data->x) + 1][data->y] == '0')
	{
		mlx_put_image_to_window(data->mlx_ptr,data->win_ptr,data->player[1],data->x + 1, data->y);
		mlx_put_image_to_window(data->mlx_ptr,data->win_ptr,data->road,data->x, data->y);
	}
	else if (data->map[(data->x) + 1][data->y] == 'c' || data->map[(data->x) + 1][data->y] == 'C')
	{
		(data->coins_nbr)--;
		mlx_put_image_to_window(data->mlx_ptr,data->win_ptr,data->player[1],data->x + 1, data->y);
		mlx_put_image_to_window(data->mlx_ptr,data->win_ptr,data->road,data->x, data->y);
	}
	else if (data->map[(data->x) + 1][data->y] == 'E' && !(data->coins_nbr))
		exit(1);
}

void go_left(t_data *data)
{
	if (data->map[(data->x) - 1][data->y] == '1' || data->coins_nbr != 0 && data->map[(data->x) - 1][data->y] == 'E')
		return ;
	else if (data->map[(data->x) - 1][data->y] == '0')
	{
		mlx_put_image_to_window(data->mlx_ptr,data->win_ptr,data->player[2],data->x - 1, data->y);
		mlx_put_image_to_window(data->mlx_ptr,data->win_ptr,data->road,data->x, data->y);
	}
	else if (data->map[(data->x) - 1][data->y] == 'c' || data->map[(data->x) - 1][data->y] == 'C')
	{
		(data->coins_nbr)--;
		mlx_put_image_to_window(data->mlx_ptr,data->win_ptr,data->player[2],data->x - 1, data->y);
		mlx_put_image_to_window(data->mlx_ptr,data->win_ptr,data->road,data->x, data->y);
	}
	else if (data->map[(data->x) - 1][data->y] == 'E' && !(data->coins_nbr))
		exit(1);
}

int handle_key(int keycode, t_data *data, int x, int y)
{
    if (keycode == 0x0064)//ESC
        exit(0);
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

int main(int ac, char **av) {
    if (ac < 2)
        return 1;

    t_data *data = malloc(sizeof(t_data));
    if (!data)
        return 1;

    data->mlx_ptr = mlx_init();
    if (!data->mlx_ptr)
        return free(data), 1;

    // Open file to get map dimensions
    int fd = open(av[1], O_RDONLY);
    if (fd == -1)
	{
        perror("Error opening file");
        return 1;
    }

    char *str = get_next_line(fd);
    if (!str) {
        perror("Error reading file");
        return 1;
    }
    int width = strlen(str);
    int height = 1;
    while (get_next_line(fd))
        height++;
    close(fd);

    map_2d_array(data, av, width, height);

    data->win_ptr = mlx_new_window(data->mlx_ptr, width * TILE_SIZE, height * TILE_SIZE, "So_long");
    if (!data->win_ptr)
	{
        mlx_destroy_display(data->mlx_ptr);
        free(data->map);
        free(data->mlx_ptr);
        free(data);
        return 1;
    }

    // Load textures
    data->wall = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/wall.xpm", &data->tex_width, &data->tex_height);
    data->road = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/road.xpm", &data->tex_width, &data->tex_height);
    data->coins = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/coins.xpm", &data->tex_width, &data->tex_height);

	data->player[0] = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/player.xpm", &data->tex_width, &data->tex_height);
    data->player[1] = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/player_right.xpm", &data->tex_width, &data->tex_height);
    data->player[2] = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/player_left.xpm", &data->tex_width, &data->tex_height);

    data->exit = mlx_xpm_file_to_image(data->mlx_ptr, "./assests/exit.xpm", &data->tex_width, &data->tex_height);

    if (!data->wall || !data->road || !data->coins || !data->player || !data->exit)
	{
        fprintf(stderr, "Failed to load one or more textures\n");
        return 1;
    }
    draw_map(data, width, height);
    // mlx_key_hook(data->win_ptr, handle_key, data);
    mlx_loop(data->mlx_ptr);

    return 0;
}