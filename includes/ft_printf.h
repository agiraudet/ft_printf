/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 09:50:08 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/04 12:34:59 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "../libft/includes/libft.h"

# define LEFT 1
# define RIGHT 0

typedef struct	s_elem
{
	char		type;
	char		*data;

	int			align;
	char		pad;
	int			width;

	int			size;
	int			prec;
}				t_elem;


t_elem		elem_init(void);
char		*elem_print(const char **str, va_list *param);
t_elem		*elem_create(const char **str, va_list *param);
int			ft_printf(const char *str, ...);

#endif
