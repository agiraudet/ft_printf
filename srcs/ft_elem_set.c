/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_elem_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 14:36:18 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/07 17:41:47 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	elem_set_value(int *value, const char **str, va_list *param)
{
	if (**str == '*')
	{
		*value = (int)va_arg(*param, int);
		(*str)++;
	}
	else
	{
		while (ft_isdigit(**str))
		{
			*value = *value * 10 + (**str - '0');
			(*str)++;
		}
	}
}

void	elem_set_flag(const char **str, t_elem *e, va_list *param)
{
	if (**str == '-' || *(*str + 1) == '-')
		e->align = LEFT;
	if (**str == '0' || (*(*str + 1) == '0' && **str == '-'))
		if (e->align == RIGHT)
			e->pad = '0';
	while (**str == '0' || **str == '-')
		(*str)++;
	elem_set_value(&e->width, str, param);
	if (e->width < 0)
	{
		e->width *= -1;
		e->align = LEFT;
	}
}

void	elem_set_prec(const char **str, t_elem *e, va_list *param)
{
	if (**str != '.')
		return ;
	e->prec = 1;
	(*str)++;
	elem_set_value(&e->size, str, param);
	if (e->size < 0)
	{
		e->prec = 0;
		e->size = 0;
	}
}

void	elem_set_data(t_elem *e, va_list *param)
{
	if (e->type == 'c')
		e->data = ft_ctostr((int)va_arg(*param, int));
	if (e->type == 's')
		e->data = arg_to_str(e, ft_strdup((char*)va_arg(*param, char*)));
	if (e->type == 'p')
		e->data = arg_to_ptr((long)va_arg(*param, long));
	if (e->type == 'd' || e->type == 'i')
		e->data = ft_itoa((int)va_arg(*param, int));
	if (e->type == 'u')
		e->data = ft_utoa((unsigned int)va_arg(*param, unsigned int));
	if (e->type == 'x')
		e->data = ft_itoa_base((long)va_arg(*param, long), "0123456789abcdef");
	if (e->type == 'X')
		e->data = ft_itoa_base((long)va_arg(*param, long), "0123456789ABCDEF");
	if (e->type == '%')
		e->data = ft_strdup("%");
}
