/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_du_grow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:33 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/07 09:53:34 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ds/deq.h"

inline t_bool	ft_du8_grow(t_du8 *self, size_t n)
{
	if ((n += self->len + 1) < FT_DEQ_MIN_CAP && FT_DEQ_MIN_CAP > self->cap)
		return (ft_du8_realloc(self, FT_DEQ_MIN_CAP));
	else if (n > self->cap)
		return (ft_du8_realloc(self, ISPOW2(n) ? n : pow2_next(n)));
	return (1);
}

inline t_bool	ft_du16_grow(t_du16 *self, size_t n)
{
	if ((n += self->len + 1) < FT_DEQ_MIN_CAP && FT_DEQ_MIN_CAP > self->cap)
		return (ft_du16_realloc(self, FT_DEQ_MIN_CAP));
	else if (n > self->cap)
		return (ft_du16_realloc(self, ISPOW2(n) ? n : pow2_next(n)));
	return (1);
}

inline t_bool	ft_du32_grow(t_du32 *self, size_t n)
{
	if ((n += self->len + 1) < FT_DEQ_MIN_CAP && FT_DEQ_MIN_CAP > self->cap)
		return (ft_du32_realloc(self, FT_DEQ_MIN_CAP));
	else if (n > self->cap)
		return (ft_du32_realloc(self, ISPOW2(n) ? n : pow2_next(n)));
	return (1);
}

inline t_bool	ft_du64_grow(t_du64 *self, size_t n)
{
	if ((n += self->len + 1) < FT_DEQ_MIN_CAP && FT_DEQ_MIN_CAP > self->cap)
		return (ft_du64_realloc(self, FT_DEQ_MIN_CAP));
	else if (n > self->cap)
		return (ft_du64_realloc(self, ISPOW2(n) ? n : pow2_next(n)));
	return (1);
}

inline t_bool	ft_deq_grow(t_deq *self, size_t n)
{
	if ((n += self->len + 1) < FT_DEQ_MIN_CAP && FT_DEQ_MIN_CAP > self->cap)
		return (ft_deq_realloc(self, FT_DEQ_MIN_CAP));
	else if (n > self->cap)
		return (ft_deq_realloc(self, ISPOW2(n) ? n : pow2_next(n)));
	return (1);
}
