/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 17:24:11 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/20 16:59:07 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parser.h"
#include "include/keys.h"
#include "include/maths.h"
#include "include/structs.h"
#include "include/consts.h"
#include "include/drawing.h"

void	init_vars(t_vars *vars, t_data *img_data)
{
	vars->alpha = 0;
	vars->beta = 0;
	vars->gamma = 0;
	vars->img = img_data;
	vars->fov = 0;
	vars->is_pres = 0;
	vars->scale = min(WINDOW_WIDTH / vars->cols, WINDOW_HEIGHT / vars->rows);
	vars->dist = vars->max + 5;
	vars->is_color_gradient = 0;
	vars->is_aa = 0;
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_data	img_data;

	if (argc != 2)
		exit(write(2, "Usage: ./fdf <file_name>\n", 25));
	handle_map(argv[1], &vars);
	if (vars.rows == 0 || vars.cols == 0)
		exit(write(2, "Error: No data found\n", 21));
	init_vars(&vars, &img_data);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF");
	img_data.img = mlx_new_image(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img_data.addr = mlx_get_data_addr(img_data.img, &img_data.bits_per_pixel,
			&img_data.line_length, &img_data.endian);
	redraw(&vars);
	mlx_hook(vars.win, 17, 0, close_win, &vars);
	mlx_mouse_hook(vars.win, zoom_handler, &vars);
	mlx_hook(vars.win, 2, X_MASK, rotation_handler, &vars);
	mlx_loop(vars.mlx);
}
