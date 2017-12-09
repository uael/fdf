/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_geo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 06:59:08 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/09 18:39:32 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft/mlx/geo.h"


int toIsometric2D(double x, double y,double z, double *u, double*v)
{
	*u=(x-z)/sqrt(2);
	*v=(x+2*y+z)/sqrt(6);
	return 0;
}

inline t_v2		ft_v2(int x, int y)
{
	return (t_v2){x, y};
}

inline t_v3		ft_v3(int x, int y, int z)
{
	return (t_v3){x, y, z};
}

inline t_v2		ft_v3iso(int x, int y, int z)
{
	return (t_v2){(int)((x - z) / sqrt(2)), (int)((x + 2 * y + z) / sqrt(6))};
}

inline t_xli	ft_xli(t_v2 origin, t_v2 target)
{
	return (t_xli){origin, target};
}
