/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 17:19:00 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/10 16:33:24 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>

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
		(fdf->m = ft_m4_mul(fdf->m, ft_m4_transy(-1)));
	else if (key == X_KEY_DOWN)
		(fdf->m = ft_m4_mul(fdf->m, ft_m4_transy(1)));
	else if (key == X_KEY_LEFT)
		(fdf->m = ft_m4_mul(fdf->m, ft_m4_transx(-1)));
	else if (key == X_KEY_RIGHT)
		(fdf->m = ft_m4_mul(fdf->m, ft_m4_transx(1)));
	else if (key == X_KEY_PLUS)
		(fdf->m = ft_m4_mul(fdf->m, ft_m4_scale(ft_v3(1.1, 1.1, 1.1))));
	else if (key == X_KEY_MINUS)
		(fdf->m = ft_m4_mul(fdf->m, ft_m4_scale(ft_v3(0.9, 0.9, 0.9))));
	else if (key == X_KEY_SEVEN)
		(fdf->m = ft_m4_mul(fdf->m, ft_m4_rotx((float)(-M_PI / 64))));
	else if (key == X_KEY_NINE)
		(fdf->m = ft_m4_mul(fdf->m, ft_m4_rotx((float)(M_PI / 64))));
	else if (key == X_KEY_FOUR)
		(fdf->m = ft_m4_mul(fdf->m, ft_m4_roty((float)(-M_PI / 64))));
	else if (key == X_KEY_SIX)
		(fdf->m = ft_m4_mul(fdf->m, ft_m4_roty((float)(M_PI / 64))));
	else if (key == X_KEY_ONE)
		(fdf->m = ft_m4_mul(fdf->m, ft_m4_rotz((float)(-M_PI / 64))));
	else if (key == X_KEY_THREE)
		(fdf->m = ft_m4_mul(fdf->m, ft_m4_rotz((float)(M_PI / 64))));
	ft_ximg_clear(fdf->img);
	y = -1;
	while (++y < fdf->li && (x = -1))
		while (++x < fdf->co)
		{
			t_v3 v;

			v = ft_m4_apply(fdf->m,
				ft_v3(x * 20, y * 20, fdf->map[(y * fdf->co) + x])
			);
			if (x + 1 < fdf->co)
				ft_ximg_wli(
					fdf->img, v,
					ft_m4_apply(fdf->m,
						ft_v3((x + 1) * 20, y * 20, fdf->map[(y * fdf->co) + (x + 1)])
					),
					0x0FFFFFF
				);
			if (y + 1 < fdf->li)
				ft_ximg_wli(
					fdf->img, v,
					ft_m4_apply(fdf->m,
						ft_v3(x * 20, (y + 1) * 20, fdf->map[((y + 1) * fdf->co) + x])
					),
					0x0FFFFFF
				);
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
			if (!(ft_vi32_pushc(&map, ft_atoi(co))))
				return (fdf_err_hdl(NULL, errno));
			co = el + 1;
			while (*co == ' ')
				++co;
		}
		if (!*co || !ft_isdigit(*co))
			return (fdf_err_hdl(NULL, errno = EINVAL));
		if (!(ft_vi32_pushc(&map, ft_atoi(co))))
			return (fdf_err_hdl(NULL, errno));
		if (x && x + 1 != fdf.co)
			return (fdf_err_hdl(NULL, errno = EINVAL));
		b = li + 1;
	}
	if (li && *++li)
		return (fdf_err_hdl(NULL, errno = EINVAL));
	fdf.map = map.buf;
	fdf.m = ft_m4_mul(ft_m4_trans(ft_v3(FDF_WGT / 2, FDF_HGT / 2, 0)), ft_m4_scale(ft_v3(1, 1, 1)));
	ft_mlx_ctor(&fdf.mlx, (t_err_hdl)fdf_err_hdl);
	fdf.win = ft_xwin(&fdf.mlx, FDF_WGT, FDF_HGT, "Wireframe @42");
	fdf.img = ft_ximg(&fdf.mlx, FDF_WGT, FDF_HGT);
	mlx_hook(fdf.win->ptr, X_KEYPRESS, X_KEYPRESSMASK, fdf_key, &fdf);
	mlx_loop(fdf.mlx.ptr);
	return (0);
}
