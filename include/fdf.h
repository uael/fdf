/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 17:19:37 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/09 16:26:39 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <libft.h>

#define FDF_WGT 600
#define FDF_HGT 600

typedef struct	s_fdf
{
	t_mlx		mlx;
	t_xwin		*win;
	t_ximg		*img;
}				t_fdf;

#endif
