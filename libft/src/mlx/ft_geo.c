/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_geo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 06:59:08 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/09 08:12:24 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/mlx/geo.h"

inline t_xdot	ft_xdot(int x, int y)
{
	return (t_xdot){x, y};
}

inline t_xli	ft_xli(t_xdot origin, t_xdot target)
{
	return (t_xli){origin, target};
}
