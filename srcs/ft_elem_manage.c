/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_elem_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 14:02:06 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/10 19:50:11 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_elem	elem_init(void)
{
	t_elem	e;

	e.zero_flag = 0;
	e.error_flag = 0;
	e.align = RIGHT;
	e.pad = ' ';
	e.width = 0;
	e.prec = 0;
	e.size = 0;
	return (e);
}

t_elem	*elem_create(const char **str, va_list *param)
{
	t_elem	*e;

	e = (t_elem*)malloc(sizeof(t_elem));
	if (!e)
		return (0);
	*e = elem_init();
	ft_set_flag(str, e, param);
	ft_set_prec(str, e, param);
	if (!ft_strchr("cspdiuxX%", **str))
	{
		free(e);
		return (0);
	}
	e->type = **str;
	(*str)++;
	ft_set_data(e, param);
	return (e);
}

void	put_buffer(t_elem *e, char *buffer)
{
	int		i;

	i = 0;
	while (buffer[i])
	{
		if (e->zero_flag && buffer[i] == '.')
			ft_putchar(0);
		else
			ft_putchar(buffer[i]);
		i++;
	}
}

int		elem_print(const char **str, va_list *param)
{
	int		ret;
	char	*buffer;
	t_elem	*e;

	e = elem_create(str, param);
	buffer = ft_fill_buffer(e);
	ret = ft_strlen(buffer);
	if (e->error_flag)
	{
		free(buffer);
		buffer = ft_strdup("");
		ret = 255;
	}
	put_buffer(e, buffer);
	free(buffer);
	free(e->data);
	free(e);
	return (ret);
}
