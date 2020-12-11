/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 14:36:18 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/10 19:52:11 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		ft_set_value(t_elem *e, int *val, const char **str, va_list *param)
{
	long	value;

	value = 0;
	if (**str == '*')
	{
		value = (int)va_arg(*param, int);
		(*str)++;
	}
	else
	{
		while (ft_isdigit(**str))
		{
			value = value * 10 + (**str - '0');
			(*str)++;
		}
	}
	if (value >= 2147483647)
	{
		e->error_flag = 1;
		value = 0;
	}
	*val = value;
}

void		ft_set_flag(const char **str, t_elem *e, va_list *param)
{
	if (**str == '-' || *(*str + 1) == '-')
		e->align = LEFT;
	if (**str == '0' || (*(*str + 1) == '0' && **str == '-'))
		if (e->align == RIGHT)
			e->pad = '0';
	while (**str == '0' || **str == '-')
		(*str)++;
	ft_set_value(e, &e->width, str, param);
	if (e->width < 0)
	{
		e->width *= -1;
		e->align = LEFT;
	}
}

void		ft_set_prec(const char **str, t_elem *e, va_list *param)
{
	if (**str != '.')
		return ;
	e->prec = 1;
	(*str)++;
	ft_set_value(e, &e->size, str, param);
	if (e->size < 0)
	{
		e->prec = 0;
		e->size = 0;
	}
}

void		ft_set_data(t_elem *e, va_list *param)
{
	if (e->type == 'c')
		e->data = arg_to_chr(e, (int)va_arg(*param, int));
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
