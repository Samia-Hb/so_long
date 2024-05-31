#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct s_data {
    void *mlx_ptr;
    void *win_ptr;
    void *frames[6]; // Array to hold the frames of the animation
    int current_frame;
    int frame_count;
    int frame_delay;
    int frame_delay_counter;
    int x;
    int y;
} t_data;

void load_frames(t_data *data)
{
    int width = 50, height = 50;
    const char *filepaths[6] =
    {
        "./assests/bonus_assests/1.xpm",
        "./assests/bonus_assests/2.xpm",
        "./assests/bonus_assests/3.xpm",
        "./assests/bonus_assests/4.xpm",
        "./assests/bonus_assests/5.xpm",
        "./assests/bonus_assests/6.xpm"
    };
    for (int i = 0; i < 6; i++) {
        data->frames[i] = mlx_xpm_file_to_image(data->mlx_ptr, (char *)filepaths[i], &width, &height);
        if (!data->frames[i]) {
            fprintf(stderr, "Failed to load frame %d: %s\n", i, filepaths[i]);
            exit(EXIT_FAILURE);
        }
    }
    data->frame_count = 6;
    data->current_frame = 0;
    data->frame_delay = 80;
    data->frame_delay_counter = 0;
    data->x = 100;
    data->y = 100;
}

void update_frame(t_data *data)
{
    data->frame_delay_counter++;
    if (data->frame_delay_counter >= data->frame_delay) {
        data->frame_delay_counter = 0;
        data->current_frame = (data->current_frame + 1) % data->frame_count;
    }
}

void render(t_data *data)
{
    mlx_clear_window(data->mlx_ptr, data->win_ptr);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->frames[data->current_frame], data->x, data->y);
}

int game_loop(t_data *data)
{
    update_frame(data);
    render(data);
    return 0;
}

int main() {
    t_data data;

    data.mlx_ptr = mlx_init();
    if (!data.mlx_ptr) {
        fprintf(stderr, "Failed to initialize MiniLibX\n");
        return EXIT_FAILURE;
    }

    data.win_ptr = mlx_new_window(data.mlx_ptr, 800, 600, "2D Animation");
    if (!data.win_ptr) {
        fprintf(stderr, "Failed to create window\n");
        return EXIT_FAILURE;
    }

    load_frames(&data);

    mlx_loop_hook(data.mlx_ptr, (int (*)())game_loop, &data);
    mlx_loop(data.mlx_ptr);

    return 0;
}
