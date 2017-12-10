/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 17:19:00 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/10 21:30:46 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "fdf.h"

#define N_FDF COLOR_RED COLOR_BOLD "fdf: " COLOR_RESET
#define IDX(X, Y, CO) (((Y) * (CO)) + (X))
#define MAT(M, X, Y, CO) ((M)[IDX(X, Y, CO)])
#define SIGN(C) ((C) == '-' || (C) == '+')

static int		fdf_err(t_mlx *mlx, int code)
{
	if (code > 0 && code <= ELAST)
		ft_putf(2, N_FDF"%e\n", code);
	else if (code == MLX_EDRAW)
		ft_puts(2, N_FDF"Unable to draw\n");
	else if (code == MLX_ENIMG)
		ft_puts(2, N_FDF"Unable to create a new image\n");
	else if (code == MLX_EAIMG)
		ft_puts(2, N_FDF"Unable to get image arguments\n");
	else if (code == MLX_ENWIN)
		ft_puts(2, N_FDF"Unable to create a new window\n");
	else if (code == MLX_ECWIN)
		ft_puts(2, N_FDF"Unable to clear window\n");
	else if (code == MLX_ENMLX)
		ft_puts(2, N_FDF"Unable to init mlx\n");
	else if (code)
		ft_putf(2, N_FDF"%d: Unrecognized error\n", code);
	if (mlx)
		ft_mlx_dtor(mlx);
	exit(code);
}

static int		fdf_move(int key, t_fdf *fdf)
{
	if (key == X_KEY_UP)
		(fdf->m4 = ft_m4_mul(fdf->m4, ft_m4_transy(-10)));
	else if (key == X_KEY_DOWN)
		(fdf->m4 = ft_m4_mul(fdf->m4, ft_m4_transy(10)));
	else if (key == X_KEY_LEFT)
		(fdf->m4 = ft_m4_mul(fdf->m4, ft_m4_transx(-10)));
	else if (key == X_KEY_RIGHT)
		(fdf->m4 = ft_m4_mul(fdf->m4, ft_m4_transx(10)));
	else if (key == X_KEY_PLUS)
		(fdf->m4 = ft_m4_mul(fdf->m4, ft_m4_scale(ft_v3(1.1, 1.1, 1.1))));
	else if (key == X_KEY_MINUS)
		(fdf->m4 = ft_m4_mul(fdf->m4, ft_m4_scale(ft_v3(0.9, 0.9, 0.9))));
	else if (key == X_KEY_SEVEN)
		(fdf->m4 = ft_m4_mul(fdf->m4, ft_m4_rotx((float)(-M_PI / 64))));
	else if (key == X_KEY_NINE)
		(fdf->m4 = ft_m4_mul(fdf->m4, ft_m4_rotx((float)(M_PI / 64))));
	else if (key == X_KEY_FOUR)
		(fdf->m4 = ft_m4_mul(fdf->m4, ft_m4_roty((float)(-M_PI / 64))));
	else if (key == X_KEY_SIX)
		(fdf->m4 = ft_m4_mul(fdf->m4, ft_m4_roty((float)(M_PI / 64))));
	else if (key == X_KEY_ONE)
		(fdf->m4 = ft_m4_mul(fdf->m4, ft_m4_rotz((float)(-M_PI / 64))));
	else if (key == X_KEY_THREE)
		(fdf->m4 = ft_m4_mul(fdf->m4, ft_m4_rotz((float)(M_PI / 64))));
	return (0);
}

static void		fdf_key(int key, t_fdf *f)
{
	int		x;
	int		y;
	t_v3	v;

	(key == X_KEY_ESC) ? fdf_err(&f->mlx, 0) : fdf_move(key, f);
	y = -1;
	ft_ximg_clear(f->img);
	while (++y < f->l && (x = -1))
		while (++x < f->co)
		{
			v = ft_m4_apply(f->m4, ft_v3((x - (f->co / 2)) * 10,
				(y - (f->l / 2)) * 10, -MAT(f->map, x, y, f->co)));
			if (x + 1 < f->co)
				ft_ximg_wli(f->img, v, ft_m4_apply(f->m4, ft_v3(
					(x + 1 - (f->co / 2)) * 10, (y - (f->l / 2)) * 10, -MAT(
					f->map, x + 1, y, f->co))), MAT(f->map, x + 1, y, f->co) ||
					MAT(f->map, x, y, f->co) ? 0x0f38ff9 : 0x0FFFFFF);
			if (y + 1 < f->l)
				ft_ximg_wli(f->img, v, ft_m4_apply(f->m4, ft_v3(
					(x - (f->co / 2)) * 10, (y + 1 - (f->l / 2)) * 10, -MAT(
					f->map, x, y + 1, f->co))), MAT(f->map, x, y, f->co) ||
					MAT(f->map, x, y + 1, f->co) ? 0x0f38ff9 : 0x0FFFFFF);
		}
	ft_ximg_draw(f->img, f->win, 0, 0);
}

int				*fdf_parse(t_fdf *f, t_dstr s, t_vi32 *map)
{
	int		x;
	char	*b;

	!(b = s.buf) && fdf_err(NULL, EINVAL);
	(f->co = (int)ft_strword(b, ' ', '\n')) ? 0 : fdf_err(NULL, EINVAL);
	f->l = 0;
	ft_vi32_ctor(map);
	x = 0;
	while (*b)
		if (*b == ' ' || (*b == '\n' && ++f->l))
		{
			(*b == '\n' && x != f->co) ? fdf_err(NULL, EINVAL) : 0;
			(*b++ == '\n') ? x = 0 : 0;
		}
		else if (ft_isdigit(*b) || (SIGN(*b) && (ft_isdigit(*(b + 1)))))
		{
			++x;
			ft_vi32_pushc(map, (int)ft_atoi(b++)) ? 0 : fdf_err(NULL, errno);
			while (ft_isdigit(*b))
				++b;
		}
		else
			fdf_err(NULL, EINVAL);
	ft_dstr_dtor(&s, NULL);
	return (map->buf);
}

int				main(int ac, char **av)
{
	t_fdf		fdf;
	t_sz		sz;
	t_vi32		map;
	t_dstr		s;
	char		b[FT_PAGE_SIZE + 1];

	FT_INIT(&fdf, t_fdf);
	if (ac != 2 || (ac = open(av[1], O_RDONLY)) < 0)
		return (fdf_err(NULL, ac < 0 ? errno : EINVAL));
	ft_dstr_ctor(&s);
	while ((sz = read(ac, b, FT_PAGE_SIZE)))
		(sz < 0 || !ft_dstr_pushnc(&s, b, (size_t)sz)) ? fdf_err(0, errno) : 0;
	(void)((fdf.map = fdf_parse(&fdf, s, &map)) && close(ac));
	fdf.m4 = ft_m4_mul(ft_m4_trans(ft_v3(FDF_WGT / 2, FDF_HGT / 2, 0)),
		ft_m4_scale(ft_v3(3, 3, 3)));
	fdf.m4 = ft_m4_mul(fdf.m4, ft_m4_rotz((float)(M_PI / 5)));
	fdf.m4 = ft_m4_mul(fdf.m4, ft_m4_roty((float)(M_PI / 8)));
	fdf.m4 = ft_m4_mul(fdf.m4, ft_m4_rotx((float)(-M_PI / 5)));
	ft_mlx_ctor(&fdf.mlx, (t_err_hdl)fdf_err);
	fdf.win = ft_xwin(&fdf.mlx, FDF_WGT, FDF_HGT, "Wireframe @42");
	fdf.img = ft_ximg(&fdf.mlx, FDF_WGT, FDF_HGT);
	fdf_key(0, &fdf);
	mlx_hook(fdf.win->ptr, X_KEYPRESS, X_KEYPRESSMASK, (int(*)())fdf_key, &fdf);
	mlx_loop(fdf.mlx.ptr);
	return (0);
}
