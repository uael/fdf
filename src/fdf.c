/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 17:19:00 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/10 10:18:52 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "fdf.h"

# define N_FDF COLOR_RED COLOR_BOLD "fdf: " COLOR_RESET

static int	fdf_err_hdl(t_mlx *mlx, int code)
{
	if (errno)
		ft_putf(2, N_FDF"%e\n", errno);
	else
		ft_puts(2, N_FDF"Unexpected error\n");
	if (mlx)
		ft_mlx_dtor(mlx);
	exit(code);
}

static int	fdf_key(int key, t_fdf *fdf)
{
	int x;
	int y;

	if (key == X_KEY_ESC)
		return (fdf_err_hdl(&fdf->mlx, 0));
	else if (key == X_KEY_UP)
		(fdf->dy -= fdf->f);
	else if (key == X_KEY_DOWN)
		(fdf->dy += fdf->f);
	else if (key == X_KEY_LEFT)
		(fdf->dx -= fdf->f);
	else if (key == X_KEY_RIGHT)
		(fdf->dx += fdf->f);
	else if (key == X_KEY_PLUS)
		(++fdf->f);
	else if (key == X_KEY_MINUS)
		(fdf->f = ft_i32max(1, fdf->f - 1));
	ft_ximg_clear(fdf->img);
	y = -1;
	while (++y < fdf->li && (x = -1))
		while (++x < fdf->co)
		{
			if (x + 1 < fdf->co)
				ft_ximg_wli(fdf->img, ft_xli(
					ft_v3iso(fdf->dx + (x * fdf->f), fdf->dy + (y * fdf->f), fdf->map[(y * fdf->co) + x] * (fdf->f / 3)),
					ft_v3iso(fdf->dx + ((x + 1) * fdf->f), fdf->dy + (y * fdf->f), fdf->map[(y * fdf->co) + (x + 1)] * (fdf->f / 3))
				), fdf->map[(y * fdf->co) + x] != fdf->map[(y * fdf->co) + (x + 1)] ? 0x0f38ff9 : 0x0FFFFFF);
			if (y + 1 < fdf->li)
				ft_ximg_wli(fdf->img, ft_xli(
					ft_v3iso(fdf->dx + (x * fdf->f), fdf->dy + (y * fdf->f), fdf->map[(y * fdf->co) + x] * (fdf->f / 3)),
					ft_v3iso(fdf->dx + (x * fdf->f), fdf->dy + ((y + 1) * fdf->f), fdf->map[((y + 1) * fdf->co) + x] * (fdf->f / 3))
				), fdf->map[(y * fdf->co) + x] != fdf->map[((y + 1) * fdf->co) + x] ? 0x0f38ff9 : 0x0FFFFFF);
		}
	ft_ximg_draw(fdf->img, fdf->win, 0, 0);
	return (0);
}

int			main(int ac, char **av)
{
	t_fdf		fdf;
	t_ifstream	ifs;
	char 		c;
	t_st		st;
	char 		*li;
	char 		*co;
	char 		*el;
	int			x;
	char 		*b;
	t_vi32		map;

	FT_INIT(&fdf, t_fdf);
	if (ac != 2 || (ISE(ft_ifstream_open(&ifs, av[1]))))
		fdf_err_hdl(NULL, ac != 2 ? (errno = EINVAL) : errno);
	x = 0;
	while (ST_OK(st = ft_ifstream_peek(&ifs, &c, (size_t)x++)) && c)
		;
	ISE(st) ? fdf_err_hdl(NULL, 1) : 0;
	b = ifs.buf;
	ifs.buf = NULL;
	if (ISE(ft_ifstream_close(&ifs)))
		fdf_err_hdl(NULL, errno);
	if (!(li = ft_strchr(b, '\n')))
		return (fdf_err_hdl(NULL, errno = EINVAL));
	*li = '\0';
	if (!(fdf.co = (int)ft_strword(b, ' ')))
		return (fdf_err_hdl(NULL, errno = EINVAL));
	*li = '\n';
	fdf.li = -1;
	ft_vi32_ctor(&map);
	while (++fdf.li >= 0 && (li = ft_strchr(b, '\n')) && (x = -1))
	{
		co = b;
		while (++x >= 0 && (el = ft_strchr(co, ' ')) && el < li)
		{
			*el = '\0';
			if (!(ft_vi32_pushc(&map, atoi(co))))
				return (fdf_err_hdl(NULL, errno));
			co = el + 1;
			while (*co == ' ')
				++co;
		}
		if (!(ft_vi32_pushc(&map, atoi(co))))
			return (fdf_err_hdl(NULL, errno));
		ft_putf(2, N_FDF"x='%d', y='%d'\n", x, fdf.co);
		if (x && x + 1 != fdf.co)
			return (fdf_err_hdl(NULL, errno = EINVAL));
		b = li + 1;
	}
	if (li && *++li)
		return (fdf_err_hdl(NULL, errno = EINVAL));
	fdf.map = map.buf;
	fdf.f = 10;
	ft_mlx_ctor(&fdf.mlx, (t_err_hdl)fdf_err_hdl);
	fdf.win = ft_xwin(&fdf.mlx, FDF_WGT, FDF_HGT, "Wireframe @42");
	fdf.img = ft_ximg(&fdf.mlx, FDF_WGT, FDF_HGT);
	mlx_hook(fdf.win->ptr, X_KEYPRESS, X_KEYPRESSMASK, fdf_key, &fdf);
	mlx_loop(fdf.mlx.ptr);
	return (0);
}
