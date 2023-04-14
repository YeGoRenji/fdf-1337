#include <stdlib.h>
#include <mlx.h>

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

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

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_line(t_data* img_ptr, int x1, int y1, int x2, int y2)
{
	// This is where a line shall be born !
	(void)y1;
	(void)y2;
	for (int i = x1; i <= x2; i++)
	{
		my_mlx_pixel_put(img_ptr, i, i, 0x00FF5C00);
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

	draw_line(&img_data, 0,0 , WINDOW_HEIGHT, WINDOW_HEIGHT);
	// my_mlx_pixel_put(&img, 100, 100, 0x00FF5C00);

	mlx_put_image_to_window(mlx_ptr, win_ptr, img_data.img, 0, 0);
	mlx_loop(mlx_ptr);
	free(mlx_ptr);
}
