/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 17:19:00 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/08 18:30:10 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    fdf_put_pixel(t_fdf *f, int x, int y, int color)
{
	if (y >= FDF_HGT || x >= FDF_WGT || x < 0 || y < 0)
		return ;
	*(int *)&f->li[(y * f->lisz) + (x * (f->bpp / 8))] = color;
}

int		fdf_dtor(t_fdf *fdf, int code)
{
	if (fdf->img && fdf->mlx)
		mlx_destroy_image(fdf->mlx, fdf->img);
	if (fdf->win && fdf->mlx)
		mlx_destroy_window(fdf->mlx, fdf->win);
	exit(code);
}

int		fdf_key(int key, t_fdf *fdf)
{
	if (key == KEY_ESC)
		return (fdf_dtor(fdf, 0));
	return (0);
}

static int g_i = 0;
static int g_j = 0;

int		fdf_loop(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img);
	mlx_new_image(fdf->mlx, FDF_WGT, FDF_HGT);
	fdf_put_pixel(fdf, g_i++, g_j++, 0x0FFFFFF);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	return (0);
}

int		fdf_ctor(t_fdf *fdf)
{
	ft_memset(fdf, 0, sizeof(t_fdf));
	if (!(fdf->mlx = mlx_init()))
		return (fdf_dtor(fdf, 1));
	if (!(fdf->win = mlx_new_window(fdf->mlx, FDF_HGT, FDF_WGT, "Fil de fer")))
		return (fdf_dtor(fdf, 1));
	if (!(fdf->img = mlx_new_image(fdf->mlx, FDF_WGT, FDF_HGT)))
		return (fdf_dtor(fdf, 1));
	mlx_hook(fdf->win, KEYRELEASE, KEYRELEASEMASK, fdf_key, &fdf);
	mlx_new_image(fdf->mlx, FDF_WGT, FDF_HGT);
	fdf->li = mlx_get_data_addr(fdf->img, &fdf->bpp, &fdf->lisz, &fdf->endian);
	return (0);
}

int		main(void)
{
	t_fdf fdf;

	if (fdf_ctor(&fdf))
		return (1);
	mlx_loop_hook(fdf.mlx, fdf_loop, &fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
