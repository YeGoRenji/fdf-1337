/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 17:24:11 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/14 20:22:56 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <mlx.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include "gnl/get_next_line.h"
#include "include/parser.h"
#include "include/keys.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define ABS(x) ((x) >= 0 ? (x) : -(x))
#define TAU 6.2831853071795864
#define AA 0
#define AA_SHADE 150

typedef struct	s_point {
	int			x;
	int			y;
	uint32_t	color;
}				t_point;

typedef struct	s_vect3d
{
	double x;
	double y;
	double z;
}				t_vect3d;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_vars {
	void		*mlx;
	void		*win;
	t_data		*img;
	t_point		line[2];
	t_vect3d	points[8];
	t_vect3d	**pts;
	int rows;
	int cols;
	// z distance
	double	distance;
	// rotation angles
	double	alpha;
	double	beta;
	double	gamma;
	// Weak prespective
	double	fov;
	// Scale
	int scale;
}				t_vars;

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

uint32_t	get_shade(uint32_t color, float shade)
{
	// 0xFF FF FF
	uint32_t r = (color & 0xFF0000) >> 16;
	uint32_t g = (color & 0x00FF00) >> 8;
	uint32_t b = (color & 0x0000FF) >> 0;
	if (shade < 0)
		shade = 0;
	if (shade > 1)
		shade = 1;
	r *= shade;
	g *= shade;
	b *= shade;
	return (r << 16 | g << 8 | b);
}

int clamp(int a, int min, int max)
{
	if (a > max)
		return (max);
	if (a < min)
		return (min);
	return (a);
}


void	draw_line(t_data* img_ptr, int x1, int y1, int x2, int y2, uint32_t color)
{
	int y_x_flip = 0;

	// This is where a line shall be born !
	if (ABS(y2 - y1) > ABS(x2 - x1))
	{
		y_x_flip = 1;
		swap_int(&x1, &y1);
		swap_int(&x2, &y2);
	}

	int	dir_y = (y2 - y1 > 0) ? 1 : -1;
	int	dir_x = (x2 - x1 > 0) ? 1 : -1;
	int	y_put = y1;

	float percent = 1;
	// x1 = clamp(x1, -1, WINDOW_WIDTH);
	// x2 = clamp(x2, -1, WINDOW_WIDTH);
	// y1 = clamp(y1, -1, WINDOW_HEIGHT);
	// y2 = clamp(y2, -1, WINDOW_HEIGHT);
	for (int x = x1; x * dir_x <= x2 * dir_x; x += dir_x)
	{
		int err = (y2 * (x - x1) - y1 * (x - x2)) - y_put * (x2 - x1);
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
		if (ABS(err) >= 0.5 * ABS(x2 - x1))
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

int mod(int x, int n)
{
	while (x < 0)
		x += n;
	return (x % n);
}

uint32_t	f(uint16_t x, uint16_t a)
{
	x = a + mod(x - a, 360);
	if (a <= x && x < a + 60)
		return (255 * (x - a) / 60);
	if (a + 60 <= x && x < a + 180)
		return (255);
	if (a + 180 <= x && x < a + 240)
		return (255 - 255 * (x - 180 - a) / 60);
	else
		return (0);
}

uint32_t	hueToRGB(uint16_t hue)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	hue = hue % 360;
	r = f(hue, 240) << 16;
	g = f(hue, 0) << 8;
	b = f(hue, 120) << 0;
	return (r | g | b);
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
	mlx_destroy_window(vars->mlx, vars->win);
	// ! free stuff ?
	exit(0);
}

int	lineHandler(int keycode, t_vars *vars)
{
	// printf("Clicked %d\n", keycode);
	if (keycode == KEY_Q)
		vars->line[0].x -= 1;
	else if (keycode == KEY_A)
		vars->line[0].y -= 1;
	else if (keycode == KEY_W)
		vars->line[0].x += 1;
	else if (keycode == KEY_S)
		vars->line[0].y += 1;
	else if (keycode == KEY_E)
		vars->line[1].x -= 1;
	else if (keycode == KEY_D)
		vars->line[1].y -= 1;
	else if (keycode == KEY_R)
		vars->line[1].x += 1;
	else if (keycode == KEY_F)
		vars->line[1].y += 1;
	clear_img(vars->img);
	draw_line(vars->img,
		vars->line[0].x, vars->line[0].y,
		vars->line[1].x, vars->line[1].y, 0xFFFFFF);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0);
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

float	lerp(uint32_t a, uint32_t b, float t)
{
	return (a * (1 - t) + b * t);
}

t_point	*f3d_to_2d(t_vars *vars, t_vect3d point3d)
{
	t_point *p = malloc(sizeof(t_point));

	double x = point3d.x;
	double y = point3d.y;
	double z = point3d.z;

	// Rotation around X
	// x = x
	double old = y;
	y = y * cos(vars->gamma) - z * sin(vars->gamma);
	z = old * sin(vars->gamma) + z * cos(vars->gamma);

	// Rotation around Y
	old = x;
	x = x * cos(vars->beta) + z * sin(vars->beta);
	// y = y
	z =  - old * sin(vars->beta) + z * cos(vars->beta);

	// Rotation around Z
	old = x;
	x = x * cos(vars->alpha) - y * sin(vars->alpha);
	y = old * sin(vars->alpha) + y * cos(vars->alpha);
	// z = z;

	if (z > vars->distance)
	{
		free(p);
		return (NULL);
	}

	// ! need to understand more why it works ! :)
	// TODO : Add more vars distance not used
	p->x = (WINDOW_WIDTH / 2) + vars->scale * x * vars->fov / check_zero((2 + vars->fov) - (z - vars->distance));
	p->y = (WINDOW_HEIGHT / 2) + vars->scale * y * vars->fov / check_zero((2 + vars->fov) - (z - vars->distance));
	return (p);
}

void	clear_console()
{
	write(1, "\e[1;1H\e[2J", 10);
}


// ! Debug purposes
void	print_info(t_vars *vars)
{
	printf("Dimensions: (%d, %d)\n", vars->rows, vars->cols);
	printf("Rotation: (%.2f, %.2f, %.2f)\n", rad_to_deg(vars->alpha), rad_to_deg(vars->beta), rad_to_deg(vars->gamma));
	printf("Scale: %d, Dist: %f, Fov: %f\n", vars->scale, vars->distance, vars->fov);
}


void redraw(t_vars *vars)
{
	int	i;
	int	j;

	clear_console();
	print_info(vars);
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
				++j;
				continue ;
			}

			if (i != vars->rows - 1)
				draw_line(vars->img, p1->x, p1->y, p2->x, p2->y,  lerp(0xFFFFFF, 0xFF5C00, vars->pts[(i + 1) % vars->rows][j].z / 10));
			if (j != vars->rows - 1)
				draw_line(vars->img, p1->x, p1->y, p3->x, p3->y, lerp(0xFFFFFF, 0xFF5C00, vars->pts[i][(j + 1) % vars->cols].z / 10));
			++j;
		}
		++i;
	}
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
	else if (keycode == KEY_Z)
		vars->scale += 1;
	else if (keycode == KEY_X)
		vars->scale -= 1;
	else if (keycode == KEY_R)
	{
		vars->alpha = 0;
		vars->beta = 0;
		vars->gamma = 0;
	}
	else
		return (0);
	clear_img(vars->img);
	redraw(vars);
	// for (int i = 0; i < 4; i++)
	// {
	// 	t_point *a = f3d_to_2d(vars, vars->points[i]);
	// 	t_point *b = f3d_to_2d(vars, vars->points[(i + 1) % 4]);
	// 	draw_line(vars->img, a->x, a->y, b->x, b->y, 0xFF5C00);

	// 	a = f3d_to_2d(vars, vars->points[4 + i]);
	// 	b = f3d_to_2d(vars, vars->points[4 + (i + 1) % 4]);
	// 	draw_line(vars->img, a->x, a->y, b->x, b->y, 0xFF5C00);

    // 	a = f3d_to_2d(vars, vars->points[i]);
	// 	b = f3d_to_2d(vars, vars->points[4 + i]);
	// 	draw_line(vars->img, a->x, a->y, b->x, b->y, 0xFF5C00);
	// }

	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0);
}

void printSPLIT(char ** s)
{
    int i = 0;

	if (!s)
	{
		puts("(null)");
		return;
	}
    printf("<| ");
    while (s[i])
    {
		printf("%s", s[i]);
        printf(s[i+1]  ? " | " : " |");
        i++;
    }
    printf(">\n");
}

int	split_len(char **split)
{
	int	len;

	len = 0;
	while (*split++)
		len++;
	return (len);
}

void parse_map(char *file_path, t_vars *vars)
{
	int		fd;
	char	*str = "SALAM";
	char	**split;
	t_list	*map;
	// t_list	*next;

	vars->cols = -1;
	vars->rows = 0;
	map = NULL;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		perror("fdf");
		exit(-1);
	}

	// Split things
	while (str)
	{
		str = get_next_line(fd);
		if (str)
		{
			vars->rows++;
			if (ft_strchr(str, '\n'))
				str[ft_strlen(str) - 1] = '\0';
		}
		if (vars->cols == -1)
			vars->cols = count_words(str, ' ');
		split = ft_split(str, ' ');
		if (split)
			ft_lstadd_back(&map, ft_lstnew(split));
		// printSPLIT(ft_split(str, ' '));
	}
	vars->pts = malloc(vars->rows * sizeof(t_vect3d*));

	int i = 0;
	int j;
	// Actual parsing
	while (map)
	{
		j = 0;
		vars->pts[i] = malloc(vars->cols * sizeof(t_vect3d));
		split = (char **)map->content;
		while (j < vars->cols)
		{
			vars->pts[i][j] = (t_vect3d){j - vars->cols / 2, i - vars->rows / 2, ft_atoi(split[j])};
			j++;
		}
		i++;
		map = map->next;
	}

	printf("Got (%d, %d)\n", vars->rows, vars->cols);
}

int main(int argc, char** argv)
{
	t_vars	vars;
	t_data	img_data;


	if (argc > 2)
	{
		exit(write(2, "use: ./fdf [map_path]", 21));
	}
	if (argc == 2)
		parse_map(argv[1], &vars);

	vars.alpha = 0;
	vars.beta = 0;
	vars.gamma = 0;
	vars.img = &img_data;
	vars.distance = 2;
	vars.fov = 2;
	vars.scale = 200;
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


	mlx_put_image_to_window(vars.mlx, vars.win, img_data.img, 0, 0);
	mlx_hook(vars.win, 17, 0, close_win, &vars);
	mlx_hook(vars.win, 2, X_MAX, rotation_handler, &vars);

	mlx_loop(vars.mlx);
	//free(mlx);
}
