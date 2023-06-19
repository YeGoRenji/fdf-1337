/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 17:24:11 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/15 16:41:12 ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "include/parser.h"
#include "include/keys.h"
#include "include/maths.h"
#include "include/structs.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define AA 0
#define AA_SHADE 150

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (!(0 <= x && x < WINDOW_WIDTH))
		return ;
	if (!(0 <= y && y < WINDOW_HEIGHT))
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}


// y = ax + b
// y2 = ax2 + b
// y1 = ax1 + b
// y2-y1 = a (x2 - x1)
// y1 = x1 * (y2 - y1)/(x2 - x1) + b
// y1x2 - x1y2 / (x2 - x1)=  + b


void	draw_line(t_data* img_ptr, t_point pt1, t_point pt2)
{
	int			y_x_flip = 0;
	uint32_t	color;

	// This is where a line shall be born !
	if (ft_abs(pt2.y - pt1.y) > ft_abs(pt2.x - pt1.x))
	{
		y_x_flip = 1;
		ft_swap(&pt1.x, &pt1.y);
		ft_swap(&pt2.x, &pt2.y);
	}
	int	dir_y = (pt2.y - pt1.y > 0) ? 1 : -1;
	int	dir_x = (pt2.x - pt1.x > 0) ? 1 : -1;
	int	y_put = pt1.y;

	float percent = 1;
	int x = pt1.x;
	for (; x * dir_x <= pt2.x * dir_x; x += dir_x)
	{
		int err = (pt2.y * (x - pt1.x) - pt1.y * (x - pt2.x)) - y_put * (pt2.x - pt1.x);
		color = lerp_color(pt1.color, pt2.color, inv_lerp(pt1.x, pt2.x, x));
		if (AA)
		{
			// ! You can make this better
			if (y_x_flip)
			{
				my_mlx_pixel_put(img_ptr, y_put - dir_y, x - dir_x, get_shade(color, percent - 0.2));
				my_mlx_pixel_put(img_ptr, y_put + dir_y, x - dir_x, get_shade(color, 1 - percent));
			}
			else
			{
				my_mlx_pixel_put(img_ptr, x - dir_x, y_put - dir_y, get_shade(color, percent - 0.2));
				my_mlx_pixel_put(img_ptr, x - dir_x, y_put + dir_y, get_shade(color, 1 - percent));
			}
		}
		if (ft_abs(err) >= 0.5 * ft_abs(pt2.x - pt1.x))
		{
			percent = 1;
			y_put += dir_y;
		}
		percent -= 0.05;
		if (percent < 0) percent = 0;
		if (y_x_flip)
			my_mlx_pixel_put(img_ptr, y_put, x, color);
		else
			my_mlx_pixel_put(img_ptr, x, y_put, color);
	}
}


void	clear_img(t_data *img)
{
	void	*dst;
	int		y;
	int		x;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			dst = img->addr + (y * img->line_length
					+ x * (img->bits_per_pixel / 8));
			*(unsigned int*)dst = 0x000000;
			++x;
		}
		++y;
	}
}

int	close_win(t_vars *vars)
{
	puts("Closed Window !");
	mlx_destroy_image(vars->mlx, vars->img->img);
	mlx_destroy_window(vars->mlx, vars->win);
	// ! free stuff ?
	exit(system("leaks fdf"));
}


t_point	*f3d_to_2d(t_vars *vars, t_vect3d point3d)
{
	t_point		*p;
	t_vect3d	result_pt;
	double		pres;

	result_pt = (t_vect3d){point3d.x, point3d.y, point3d.z, point3d.color};
	apply_rot_x(vars->alpha, &result_pt);
	apply_rot_y(vars->beta, &result_pt);
	apply_rot_z(vars->gamma, &result_pt);

	pres = check_zero(vars->is_pres * (vars->dist - vars->fov * result_pt.z));
	if (pres <= 0)
		return (NULL);

	p = malloc(sizeof(t_point));
	if (!p)
	{
		perror("fdf");
		exit(-1);
	}
	p->x = (WINDOW_WIDTH / 2) + vars->scale * (result_pt.x + vars->x) / pres;
	p->y = (WINDOW_HEIGHT / 2) + vars->scale * (result_pt.y - vars->y) / pres;
	p->color = point3d.color;
	if (vars->is_color_gradient)
		p->color = hue_to_rgb(320 * inv_lerp(vars->min, vars->max, point3d.z));
	return (p);
}

void	clear_console(void)
{
	int	a;

	a = write(1, "\e[1;1H\e[2J", 10);
	(void)a;
}


// ! Debug purposes
void	print_info(t_vars *vars)
{
	printf("Dimensions: (%d, %d)\n", vars->rows, vars->cols);
	printf("Rotation: (%.2f, %.2f, %.2f)\n", rad_to_deg(vars->alpha), rad_to_deg(vars->beta), rad_to_deg(vars->gamma));
	printf("Position: (%.2f, %.2f, %.2f)\n", vars->x, vars->y, vars->dist);
	printf("Scale: %d, Fov: %f\n", vars->scale, vars->fov);
	printf("Max : %d, Min: %d\n", vars->max, vars->min);
}


void redraw(t_vars *vars)
{
	int			i;
	int			j;
	t_vect3d	vec[3];
	t_point		*p[3];

	clear_img(vars->img);
	clear_console();
	print_info(vars);
	i = 0;
	while (i < vars->rows)
	{
		j = 0;
		while (j < vars->cols)
		{
			vec[0] = vars->pts[i][j];
			vec[1] = vars->pts[(i + 1) % vars->rows][j];
			vec[2] = vars->pts[i][(j + 1) % vars->cols];
			p[0] = f3d_to_2d(vars, vec[0]);
			p[1] = f3d_to_2d(vars, vec[1]);
			p[2] = f3d_to_2d(vars, vec[2]);
			if (!p[0] || !p[1] || !p[2])
			{
				free(p[0]);
				free(p[1]);
				free(p[2]);
				++j;
				continue ;
			}

			if (i < vars->rows - 1)
				draw_line(vars->img, (t_point){p[0]->x, p[0]->y, p[0]->color}, (t_point){p[1]->x, p[1]->y, p[1]->color});
			if (j < vars->cols - 1)
				draw_line(vars->img, (t_point){p[0]->x, p[0]->y, p[0]->color}, (t_point){p[2]->x, p[2]->y, p[2]->color});
			free(p[0]);
			free(p[1]);
			free(p[2]);
			++j;
		}
		++i;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
}


int	rotation_handler(int keycode, t_vars *vars)
{
	printf("Clicked %d\n", keycode);
	if (keycode == KEY_Q)
		vars->alpha += TAU / 32;
	else if (keycode == KEY_A)
		vars->alpha -= TAU / 32;
	else if (keycode == KEY_W)
		vars->beta += TAU / 32;
	else if (keycode == KEY_S)
		vars->beta -= TAU / 32;
	else if (keycode == KEY_E)
		vars->gamma += TAU / 32;
	else if (keycode == KEY_D)
		vars->gamma -= TAU / 32;
	else if (keycode == KEY_Y)
		vars->dist += 0.5;
	else if (keycode == KEY_H)
		vars->dist -= 0.5;
	else if (keycode == KEY_T)
		vars->fov += 0.5;
	else if (keycode == KEY_G)
		vars->fov -= 0.5;
	else if (keycode == KEY_F)
		vars->is_color_gradient = !vars->is_color_gradient;
	else if (keycode == KEY_O)
		vars->is_pres = !vars->is_pres;
	else if (keycode == KEY_UP)
		vars->y += 1;
	else if (keycode == KEY_DOWN)
		vars->y -= 1;
	else if (keycode == KEY_RIGHT)
		vars->x += 1;
	else if (keycode == KEY_LEFT)
		vars->x -= 1;
	else if (keycode == KEY_ESC)
		return (close_win(vars));
	else if (keycode == KEY_R)
	{
		vars->alpha = 0;
		vars->beta = 0;
		vars->gamma = 0;
	}
	else
		return (0);
	if (vars->fov < 0)
		vars->fov = 0;
	redraw(vars);
	return (0);
}


int	zoom_handler(int keycode, int x, int y, t_vars *vars)
{
	printf("Clicked %d\n", keycode);
	if (keycode == SCROLL_UP)
		vars->scale += 5;
	else if (keycode == SCROLL_DOWN)
		vars->scale -= 5;
	(void)x;
	(void)y;
	if (vars->scale < 1)
		vars->scale = 1;
	redraw(vars);
	return (0);
}


int main(int argc, char** argv)
{
	t_vars	vars;
	t_data	img_data;

	if (argc != 2)
		exit(write(2, "Usage: ./fdf <file_name>\n", 25));
	handle_map(argv[1], &vars);

	vars.alpha = 0;
	vars.beta = 0;
	// vars.gamma = TAU / 8;
	vars.gamma = 0;
	vars.img = &img_data;
	vars.fov = 0;
	vars.is_pres = 0;
	vars.scale = min(WINDOW_WIDTH / vars.cols, WINDOW_HEIGHT / vars.rows);
	vars.dist = vars.max + 5;
	vars.is_color_gradient = 0;
	// vars.line[0] = (t_point){WINDOW_WIDTH/4, WINDOW_HEIGHT/2};
	// vars.line[1] = (t_point){3*WINDOW_WIDTH/4, WINDOW_HEIGHT/2};
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF");
	img_data.img = mlx_new_image(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img_data.addr = mlx_get_data_addr(img_data.img, &img_data.bits_per_pixel, &img_data.line_length, &img_data.endian);

	// draw_line(&img_data,
	// WINDOW_WIDTH/2, WINDOW_HEIGHT/2,
	// WINDOW_WIDTH, WINDOW_HEIGHT/2  + 50,
	// 0xFF5C00);

	// hue_to_rgb(120);

	// int j = 0;
	// while (j <= 360)
	// {
	// 	printf("(%3d) -> %#.6x\n",j, hue_to_rgb(j));
	// 	j++;
	// }


	// -- Rainbow Circle
	// int i = 0;
	// int cycles = 30000;
	// int Amp = 300;
	// while (i < cycles)
	// {
	// 	draw_line(&img_data, WINDOW_WIDTH/2, WINDOW_HEIGHT/2,
	// 	WINDOW_WIDTH/2 + Amp * cos((double)i/(double)cycles * (TAU)),
	// 	WINDOW_HEIGHT/2 + Amp * sin((double)i/(double)cycles * (TAU)),
	// 	hue_to_rgb((float)i * 360 / cycles));
	// 	i++;
	// }

	redraw(&vars);
	// -- Cool Cube
	// vars.points[0] = (t_vect3d){-1, 1,-1};
	// vars.points[1] = (t_vect3d){ 1, 1,-1};
	// vars.points[2] = (t_vect3d){ 1,-1,-1};
	// vars.points[3] = (t_vect3d){-1,-1,-1};

	// vars.points[4] = (t_vect3d){-1, 1, 1};
	// vars.points[5] = (t_vect3d){ 1, 1, 1};
	// vars.points[6] = (t_vect3d){ 1,-1, 1};
	// vars.points[7] = (t_vect3d){-1,-1, 1};
	// for (int i = 0; i < 4; i++)
	// {
	// 	t_point *a = f3d_to_2d(&vars, vars.points[i]);
	// 	t_point *b = f3d_to_2d(&vars, vars.points[(i + 1) % 4]);
	// 	draw_line(vars.img, a->x, a->y, b->x, b->y, 0xFF5C00);

	// 	a = f3d_to_2d(&vars, vars.points[4 + i]);
	// 	b = f3d_to_2d(&vars, vars.points[4 + (i + 1) % 4]);
	// 	draw_line(vars.img, a->x, a->y, b->x, b->y, 0xFF5C00);

	// 	a = f3d_to_2d(&vars, vars.points[i]);
	// 	b = f3d_to_2d(&vars, vars.points[4 + i]);
	// 	draw_line(vars.img, a->x, a->y, b->x, b->y, 0xFF5C00);
	// }


	mlx_hook(vars.win, 17, 0, close_win, &vars);
	mlx_mouse_hook(vars.win, zoom_handler, &vars);
	mlx_hook(vars.win, 2, X_MASK, rotation_handler, &vars);
	mlx_loop(vars.mlx);
	//free(mlx);
}
