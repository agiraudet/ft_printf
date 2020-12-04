/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_elem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 18:32:27 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/04 23:10:30 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	elem_set_value(int *value, const char **str, va_list *param)
{
	if (**str == '*')
	{
		*value = (int)va_arg(*param, int);
		(*str)++;
		return ;
	}
	while (ft_isdigit(**str))
	{
		*value = *value * 10 + (**str - '0');
		(*str)++;
	}
}

void	elem_set_flag(const char **str, t_elem *e, va_list *param)
{
	if (**str == '-' || *(*str + 1) == '-')
		e->align = LEFT;
	if ((**str == '0' || (*(*str + 1) == '0' && **str == '-')) && e->align == RIGHT)
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
}

void	elem_set_data(t_elem *e, va_list *param)
{
	if (e->type == 'c')
		e->data = ft_ctostr((int)va_arg(*param, int));
	if (e->type == 's')
		e->data = ft_strdup((char*)va_arg(*param, char*));
	if (e->type == 'p')
		e->data = ft_itoa_base((long)va_arg(*param, long), "0123456789abcdef");
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

t_elem	*elem_create(const char **str, va_list *param)
{
	t_elem	*e;

	e = (t_elem*)malloc(sizeof(t_elem));
	if (!e)
		return (0);
	*e = elem_init();
	elem_set_flag(str, e, param);
	elem_set_prec(str, e, param);
	if (!ft_strchr("cspdiuxX%", **str))
	{
		free(e);
		return (0);
	}
	e->type = **str;
	(*str)++;
	elem_set_data(e, param);
	return (e);
}
