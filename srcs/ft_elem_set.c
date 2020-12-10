/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_elem_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 14:36:18 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/10 16:39:58 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		elem_set_value(t_elem *e, int *value, const char **str, va_list *param)
{
	long	v;

	v = 0;
	if (**str == '*')
	{
		v = (int)va_arg(*param, int);
		(*str)++;
	}
	else
	{
		while (ft_isdigit(**str))
		{
			v = v * 10 + (**str - '0');
			(*str)++;
		}
	}
	if (v >= 2147483647)
	{
		e->errorFlag = 1;
		v = 0;
	}
	*value = v;
}

void		elem_set_flag(const char **str, t_elem *e, va_list *param)
{
	if (**str == '-' || *(*str + 1) == '-')
		e->align = LEFT;
	if (**str == '0' || (*(*str + 1) == '0' && **str == '-'))
		if (e->align == RIGHT)
			e->pad = '0';
	while (**str == '0' || **str == '-')
		(*str)++;
	elem_set_value(e, &e->width, str, param);
	if (e->width < 0)
	{
		e->width *= -1;
		e->align = LEFT;
		//e->align = RIGHT;
	}
}

void	elem_set_prec(const char **str, t_elem *e, va_list *param)
{
	if (**str != '.')
		return ;
	e->prec = 1;
	(*str)++;
	elem_set_value(e, &e->size, str, param);
	if (e->size < 0)
	{
		e->prec = 0;
		e->size = 0;
	}
}

void	elem_set_data(t_elem *e, va_list *param)
{
	if (e->type == 'c')
	{
		long x = (int)va_arg(*param, int);
		if (x >= 2147483647)
			x = 255;
		else if (x <= -2147483648)
			x = 0;
		if (x == 0)
		{
			e->zeroFlag = 1;
			x = '.';
		}
		e->data = ft_ctostr(x);
	}
		//e->data = ft_ctostr((int)va_arg(*param, int));
	else if (e->type == 's')
		e->data = arg_to_str(e, ft_strdup((char*)va_arg(*param, char*)));
	else if (e->type == 'p')
		e->data = arg_to_ptr((long)va_arg(*param, long));
	else if (e->type == 'd' || e->type == 'i')
		e->data = ft_itoa((int)va_arg(*param, int));
	else if (e->type == 'u')
		e->data = ft_utoa((unsigned int)va_arg(*param, unsigned int));
	else if (e->type == 'x')
		e->data = ft_itoa_base((long)va_arg(*param, long), "0123456789abcdef");
	else if (e->type == 'X')
		e->data = ft_itoa_base((long)va_arg(*param, long), "0123456789ABCDEF");
	else if (e->type == '%')
		e->data = ft_strdup("%");
}
