#include "mlx.h"
#include "fdf.h"
#include <unistd.h>

void pchar(char c)
{
	write(1, &c, 1);
}

int	deal_key(int key, void *param)
{
	key += 0;
	param += 0;
	pchar('O');
	return (0);
}

int main(void)
{
	void *mlx_ptr;
	void *win_ptr;
	t_point p0;
	t_point p1;

	p0.x = 1;
	p0.y = 1;
	p1.x = 50;
	p1.y = 50;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "Bonjour bonjour !!");
	mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0xFFFFFF);
	mlx_key_hook(win_ptr, deal_key, (void *)0);
//	draw_line(mlx_ptr, win_ptr, p0, p1);
	mlx_loop(mlx_ptr);
	return (0);
}
