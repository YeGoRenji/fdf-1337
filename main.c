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
#define ABS(x) ((x) >= 0 ? (x) : -(x))
#define TAU 6.2831853071795864
#define AA 0
#define AA_SHADE 150

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	if (!(0 <= x && x < WINDOW_WIDTH))
		return;
	if (!(0 <= y && y < WINDOW_HEIGHT))
		return;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	swap_int(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void	swap_pts(t_point **pt1, t_point **pt2)
{
	t_point *tmp = *pt1;
	*pt1 = *pt2;
	*pt2 = tmp;
}

void	draw_line_2(t_data* img_ptr, t_point pt1, t_point pt2, uint32_t color)
{
	int y_x_flip = 0;

	// This is where a line shall be born !
	if (ABS(pt2.y - pt1.y) > ABS(pt2.x - pt1.x))
	{
		y_x_flip = 1;
		// swap_pts(&pt1, &pt2);
		// swap_int(&x1, &y1);
		// swap_int(&x2, &y2);

		swap_int(&pt1.x, &pt1.y);
		swap_int(&pt2.x, &pt2.y);
	}

	int	dir_y = (pt2.y - pt1.y > 0) ? 1 : -1;
	int	dir_x = (pt2.x - pt1.x > 0) ? 1 : -1;
	int	y_put = pt1.y;

	float percent = 1;
	// pt1.x = clamp(pt1.x, -1, WINDOW_WIDTH);
	// pt2.x = clamp(pt2.x, -1, WINDOW_WIDTH);
	// pt1.y = clamp(pt1.y, -1, WINDOW_HEIGHT);
	// pt2.y = clamp(pt2.y, -1, WINDOW_HEIGHT);
	for (int x = pt1.x; x * dir_x <= pt2.x * dir_x; x += dir_x)
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
		if (ABS(err) >= 0.5 * ABS(pt2.x - pt1.x))
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

// void	draw_line(t_data* img_ptr, int x1, int y1, int x2, int y2, uint32_t color)
// {
// 	int y_x_flip = 0;

// 	// This is where a line shall be born !
// 	if (ABS(y2 - y1) > ABS(x2 - x1))
// 	{
// 		y_x_flip = 1;
// 		swap_int(&x1, &y1);
// 		swap_int(&x2, &y2);
// 	}

// 	int	dir_y = (y2 - y1 > 0) ? 1 : -1;
// 	int	dir_x = (x2 - x1 > 0) ? 1 : -1;
// 	int	y_put = y1;

// 	float percent = 1;
// 	// x1 = clamp(x1, -1, WINDOW_WIDTH);
// 	// x2 = clamp(x2, -1, WINDOW_WIDTH);
// 	// y1 = clamp(y1, -1, WINDOW_HEIGHT);
// 	// y2 = clamp(y2, -1, WINDOW_HEIGHT);
// 	for (int x = x1; x * dir_x <= x2 * dir_x; x += dir_x)
// 	{
// 		int err = (y2 * (x - x1) - y1 * (x - x2)) - y_put * (x2 - x1);
// 		if (AA)
// 		{
// 			// ! You can make this better
// 			if (y_x_flip)
// 			{
// 				my_mlx_pixel_put(img_ptr, y_put - dir_y, x - dir_x, get_shade(color, percent - 0.2));
// 				my_mlx_pixel_put(img_ptr, y_put + dir_y, x - dir_x, get_shade(color, 1 - percent));
// 			}
// 			else
// 			{
// 				my_mlx_pixel_put(img_ptr, x - dir_x, y_put - dir_y, get_shade(color, percent - 0.2));
// 				my_mlx_pixel_put(img_ptr, x - dir_x, y_put + dir_y, get_shade(color, 1 - percent));
// 			}
// 		}
// 		if (ABS(err) >= 0.5 * ABS(x2 - x1))
// 		{
// 			percent = 1;
// 			y_put += dir_y;
// 		}
// 		percent -= 0.05;
// 		if (percent < 0) percent = 0;
// 		if (y_x_flip)
// 			my_mlx_pixel_put(img_ptr, y_put, x, color);
// 		else
// 			my_mlx_pixel_put(img_ptr, x, y_put, color);
// 	}
// }


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
			dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
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
	system("leaks fdf");
	exit(0);
}

void	draw_point(t_vars *vars, t_point p)
{
	my_mlx_pixel_put(vars->img, p.x, p.y, 0xFFFFFF);
	my_mlx_pixel_put(vars->img, p.x + 1, p.y, 0xFFFFFF);
	my_mlx_pixel_put(vars->img, p.x - 1, p.y, 0xFFFFFF);
	my_mlx_pixel_put(vars->img, p.x, p.y + 1, 0xFFFFFF);
	my_mlx_pixel_put(vars->img, p.x, p.y - 1, 0xFFFFFF);
}

float	check_zero(float arith)
{
	if (arith == 0)
		return (1);
	return (arith);
}

double	rad_to_deg(double angle)
{
	return (mod(angle * 360 / TAU, 360));
}


t_point	*f3d_to_2d(t_vars *vars, t_vect3d point3d)
{
	t_point		*p;
	t_vect3d	result_pt;
	double		prespect;

	result_pt = (t_vect3d){point3d.x, point3d.y, point3d.z, point3d.color};
	apply_rot_x(vars->alpha, &result_pt);
	apply_rot_y(vars->beta, &result_pt);
	apply_rot_z(vars->gamma, &result_pt);

	prespect = check_zero(vars->fov * (1 - (result_pt.z - vars->distance)));
	if (prespect < 0)
		return (NULL);

	p = malloc(sizeof(t_point));
	if (!p)
	{
		perror("fdf");
		exit(-1);
	}
	p->x = (WINDOW_WIDTH / 2) + vars->scale * (result_pt.x + vars->x) / prespect;
	p->y = (WINDOW_HEIGHT / 2) + vars->scale * (result_pt.y - vars->y) / prespect;
	if (vars->is_color_gradient)
		p->color = hueToRGB(10 * point3d.z);
	else
		p->color = point3d.color;
	return (p);
}

void	clear_console()
{
	int a = write(1, "\e[1;1H\e[2J", 10);
	(void)a;
}


// ! Debug purposes
void	print_info(t_vars *vars)
{
	printf("Dimensions: (%d, %d)\n", vars->rows, vars->cols);
	printf("Rotation: (%.2f, %.2f, %.2f)\n", rad_to_deg(vars->alpha), rad_to_deg(vars->beta), rad_to_deg(vars->gamma));
	printf("Position: (%.2f, %.2f, %.2f)\n", vars->x, vars->y, vars->distance);
	printf("Scale: %d, Fov: %f\n", vars->scale, vars->fov);
}


void redraw(t_vars *vars)
{
	int	i;
	int	j;

	clear_img(vars->img);
	// clear_console();
	// print_info(vars);
	i = 0;
	while (i < vars->rows)
	{
		j = 0;
		while (j < vars->cols)
		{
			// t_point *p = f3d_to_2d(vars, vars->pts[i][j]);
			// draw_point(vars , *p);

			t_vect3d vec1 = vars->pts[i][j];
			t_vect3d vec2 = vars->pts[(i + 1) % vars->rows][j];
			t_vect3d vec3 = vars->pts[i][(j + 1) % vars->cols];
			t_point *p1 = f3d_to_2d(vars, vec1);
			t_point *p2 = f3d_to_2d(vars, vec2);
			t_point *p3 = f3d_to_2d(vars, vec3);
			if (!p1 || !p2 || !p3)
			{
				free(p1);
				free(p2);
				free(p3);
				++j;
				continue ;
			}

			if (i < vars->rows - 1)
				draw_line_2(vars->img, (t_point){p1->x, p1->y, p1->color}, *p2, hueToRGB(360 * vars->pts[(i + 1) % vars->rows][j].z / 10));
			if (j < vars->cols - 1)
				draw_line_2(vars->img, (t_point){p1->x, p1->y, p1->color}, *p3, hueToRGB(360 * vars->pts[i][(j + 1) % vars->cols].z / 10));
			free(p1);
			free(p2);
			free(p3);
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
		vars->distance += 0.5;
	else if (keycode == KEY_H)
		vars->distance -= 0.5;
	else if (keycode == KEY_T)
		vars->fov += 0.5;
	else if (keycode == KEY_G)
		vars->fov -= 0.5;
	else if (keycode == KEY_UP)
		vars->y += 1;
	else if (keycode == KEY_DOWN)
		vars->y -= 1;
	else if (keycode == KEY_RIGHT)
		vars->x += 1;
	else if (keycode == KEY_LEFT)
		vars->x -= 1;
	else if (keycode == KEY_F)
		vars->is_color_gradient = !vars->is_color_gradient;
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
	vars.fov = 0.5;
	vars.scale = 200;
	vars.distance = (vars.rows > vars.cols ? vars.rows : vars.cols) / (4 * vars.fov);
	vars.is_color_gradient = 0;
	// vars.distance = 200;
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

	// hueToRGB(120);

	// int j = 0;
	// while (j <= 360)
	// {
	// 	printf("(%3d) -> %#.6x\n",j, hueToRGB(j));
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
	// 	hueToRGB((float)i * 360 / cycles));
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
	mlx_hook(vars.win, 2, X_MAX, rotation_handler, &vars);
	mlx_loop(vars.mlx);
	//free(mlx);
}
