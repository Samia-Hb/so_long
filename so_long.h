/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:14:33 by shebaz            #+#    #+#             */
/*   Updated: 2024/06/05 16:16:33 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "get_next_line/get_next_line.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define TILE_SIZE 50 // Size of each tile
# define WINDOWS_HEIGHT 900
# define WINDOWS_WIDTH 300

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*wall;
	void	*player[3];
	void	*enemy[6];
	void	*road;
	void	*coins;
	void	*exit;
	char	**map;
	int		tex_width;
	int		tex_height;
	int		x;
	int		y;
	int		coins_nbr;
	int		map_height;
	int		map_width;
	int		p_nbr;
	int		e_nbr;
}			t_data;

void		clear_data(t_data *data, int i);
void		initial_struct(t_data *data);
void		check_arguments(t_data *data, char **av);
int			handle_key(int keycode, t_data *data);
int			close_window(t_data *data);
void		clear_exit(t_data *data);
void		free_map(char **map, int x, int fd);
void		calcul_width_height(t_data *data, char **av, char *str);
int			ft_strncmp(char *s1, char *s2, int n);
void		check_arg(t_data *data, char **av);
void		map_2d_array(t_data *data, char **av);
void		check_borders(t_data *data);
void		check_form(t_data *data);
void		check_characters(t_data *data);
void		check_parameters_number(t_data *data, int i, int j);
void		check_path(t_data *data);
void		free_2d_array(char **array, int height);
void		insert_pos(t_data *data, int x, int y);
void		picture_loading(t_data *data);
void		windows_stuff(t_data *data);

#endif