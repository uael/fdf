/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 17:19:00 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/09 08:59:44 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	fdf_err_hdl(t_mlx *mlx, int code)
{
	ft_mlx_dtor(mlx);
	exit(code);
}

static int	fdf_key(int key, t_fdf *fdf)
{
	if (key == X_KEY_ESC)
		return (fdf_err_hdl(&fdf->mlx, 0));
	ft_xwin_clear(fdf->win);
	ft_ximg_wli(fdf->img, ft_xli(ft_xdot(21, 42), ft_xdot(21, 42)), 0x0FFFFFF);
	return (0);
}

int			main(void)
{
	t_fdf fdf;

	FT_INIT(&fdf, t_fdf);
	ft_mlx_ctor(&fdf.mlx, (t_err_hdl)fdf_err_hdl);
	fdf.win = ft_xwin(&fdf.mlx, FDF_WGT, FDF_HGT, "Fil de fer @42");
	fdf.img = ft_ximg(&fdf.mlx, FDF_WGT, FDF_HGT);
	mlx_hook(fdf.win->ptr, X_KEYPRESS, X_KEYPRESSMASK, fdf_key, &fdf);
	mlx_loop(fdf.mlx.ptr);
	return (0);
}
