#include <stdlib.h>
#include <mlx.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define ABS(x) ((x) >= 0 ? (x) : -(x))
# define PI 3.141592653

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, uint32_t color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_line(t_data* img_ptr, int x1, int y1, int x2, int y2)
{
	// int	dx = x2 - x1;
	// int	dy = y2 - y1;
	int	y_put = y1;
	int	dir_y = (y2 - y1 > 0) ? 1 : -1;
	int	dir_x = (x2 - x1 > 0) ? 1 : -1;

	// This is where a line shall be born !
	for (int x = x1; x * dir_x <= x2 * dir_x; x += dir_x)
	{
		int err = (y2 * (x - x1) - y1 * (x - x2)) - y_put * (x2 - x1);
		printf("x = %d, err = %d\n", x, err);
		if (ABS(err) >= ABS(x2 - x1))
			y_put += dir_y;
		my_mlx_pixel_put(img_ptr, x, y_put, 0x00FF5C00);
	}

	int x_put = x1;
	for (int y = y1; y * dir_y <= y2 * dir_y; y += dir_y)
	{
		int err = (x2 * (y - y1) - x1 * (y - y2)) - x_put * (y2 - y1);
		if (ABS(err) >= ABS(y2 - y1))
			x_put += dir_x;
		my_mlx_pixel_put(img_ptr, x_put, y, 0x00FF5C00);
	}
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

	draw_line(&img_data, 0, 0, 4, 2);

	// -- Cool Stuff
	int i = 0;
	int cycles = 32;
	int m = 200;
	while (i < cycles)
	{
		draw_line(&img_data, WINDOW_WIDTH/2, WINDOW_HEIGHT/2, WINDOW_WIDTH/2 + m * cos(i * 2 * PI/cycles), WINDOW_HEIGHT/2 + m * sin(i * 2 * PI/cycles));
		i++;
	}

	mlx_put_image_to_window(mlx_ptr, win_ptr, img_data.img, 0, 0);
	mlx_loop(mlx_ptr);
	free(mlx_ptr);
}
