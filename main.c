#include <stdlib.h>
#include <mlx.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define ABS(x) ((x) >= 0 ? (x) : -(x))
#define TAU 6.2831853071795864
#define AA 1
#define AA_SHADE 180

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

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

uint32_t	get_shade(uint32_t color, uint8_t shade)
{
	// 0xFF FF FF
	uint32_t r = (color & 0xFF0000) >> 16;
	uint32_t g = (color & 0x00FF00) >> 8;
	uint32_t b = (color & 0x0000FF) >> 0;
	r *= (float)shade / 255;
	g *= (float)shade / 255;
	b *= (float)shade / 255;
	return (r << 16 | g << 8 | b);
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

	for (int x = x1; x * dir_x <= x2 * dir_x; x += dir_x)
	{
		int err = (y2 * (x - x1) - y1 * (x - x2)) - y_put * (x2 - x1);
		if (ABS(err) >= 0.5 * ABS(x2 - x1))
		{
			if (AA)
			{
				if (y_x_flip)
				{
					my_mlx_pixel_put(img_ptr, y_put, x, get_shade(color, AA_SHADE));
					my_mlx_pixel_put(img_ptr, y_put + dir_y, x - dir_x, get_shade(color, AA_SHADE));
				}
				else
				{
					my_mlx_pixel_put(img_ptr, x, y_put, get_shade(color, AA_SHADE));
					my_mlx_pixel_put(img_ptr, x - dir_x, y_put + dir_y, get_shade(color, AA_SHADE));
				}
			}
			y_put += dir_y;
		}
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
		return (255*(x - a)/60);
	if (a + 60 <= x && x < a + 180)
		return (255);
	if (a + 180 <= x && x < a + 240)
		return (255 - 255*(x - 180 - a)/60);
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

int main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	img_data;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF");
	img_data.img = mlx_new_image(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);

	img_data.addr = mlx_get_data_addr(img_data.img, &img_data.bits_per_pixel, &img_data.line_length, &img_data.endian);

	// draw_line(&img_data, 0, 0, WINDOW_WIDTH/4, WINDOW_HEIGHT, 0xFF5C00);
	// draw_line(&img_data, WINDOW_WIDTH/2, WINDOW_HEIGHT/2, WINDOW_WIDTH/2 - 1, WINDOW_HEIGHT/2 - 100, 0xFF5C00);

	// draw_line(&img_data,
	// WINDOW_WIDTH/2, WINDOW_HEIGHT/2,
	// WINDOW_WIDTH/2 + 5, WINDOW_HEIGHT/2 + 5,
	// 0xFF5C00);

	// hueToRGB(120);

	// int j = 0;
	// while (j <= 360)
	// {
	// 	printf("(%3d) -> %#.6x\n",j, hueToRGB(j));
	// 	j++;
	// }
	

	// -- Cool Stuff
	int i = 0;
	int cycles = 10000;
	int Amp = 300;
	while (i < cycles)
	{
		draw_line(&img_data, WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 
		WINDOW_WIDTH/2 + Amp * cos((double)i/cycles * (TAU)), 
		WINDOW_HEIGHT/2 + Amp * sin((double)i/cycles * (TAU)), 
		hueToRGB((float)i * 360 / cycles));
		// draw_line(&img_data, WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 
		// WINDOW_WIDTH/2 + Amp * cos((i * 2 * PI)/cycles),
		// WINDOW_HEIGHT/2 + Amp * sin((i * 2 * PI)/cycles), 
		// 0xFF5C00);
		i++;
	}

	mlx_put_image_to_window(mlx_ptr, win_ptr, img_data.img, 0, 0);
	mlx_loop(mlx_ptr);
	free(mlx_ptr);
}
