/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_elem_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:04:32 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/07 18:21:09 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*elem_fill_str_prec(t_elem *e)
{
	char	*ret;
	char	*src;
	int		i;
	int		datalen;

	src = e->data;
	datalen = ft_strlen(src);
	if (e->prec && e->size < datalen)
		datalen = e->size;
	ret = (char*)malloc(sizeof(char) * (datalen + 1));
	if (!ret)
		return (0);
	i = 0;
	while (i < datalen)
		ret[i++] = *src++;
	ret[i] = '\0';
	return (ret);
}

char	*elem_fill_nbr_prec(t_elem *e)
{
	char	*ret;
	char	*src;
	int		i;
	int		datalen;
	int		padlen;

	src = e->data;
	datalen = ft_strlen(src);
	padlen = 0;
	if (e->prec && !e->size && *src == '0' && datalen == 1)
		return (ft_strdup(""));
	if (e->prec && e->size > datalen)
		padlen = e->size -datalen;
	padlen += (ft_strchr(src, '-') && e->prec && e->size >= datalen) ? 1 : 0;
	ret = (char*)malloc(sizeof(char) * (datalen + padlen + 1));
	if (!ret)
		return (0);
	i = 0;
	while (i < padlen)
		ret[i++] = '0';
	while (i < datalen + padlen)
		ret[i++] = *src++;
	ret[i] = '\0';
	fix_minus(ret);
	return (ret);
}

char	*elem_fill_prec(t_elem *e)
{
	char	*prec;

	if (ft_strchr("pdiuxX", e->type))
		prec = elem_fill_nbr_prec(e);
	else
	{
		e->pad = ' ';
		prec = elem_fill_str_prec(e);
	}
	return (prec);
}

char	*elem_fill_align(t_elem *e, char *prec)
{
	char	*ret;
	int		datalen;
	int		padlen;
	int		i;
	int		j;

	datalen = ft_strlen(prec);
	padlen = 0;
	if (e->prec)
		e->pad = ' ';
	if (e->width > datalen)
		padlen = e->width - datalen;
	ret = (char*)malloc(sizeof(char) * (datalen + padlen + 1));
	if (!ret)
		return (0);
	i = 0;
	if (ft_atoi(prec) < 0 && e->prec)
		e->pad = ' ';
	if (e->align == RIGHT)
		while (i < padlen)
			ret[i++] = e->pad;
	j = 0;
	while (j < datalen)
		ret[i++] = prec[j++];
	while (i < padlen + datalen)
		ret[i++] = ' ';
	ret[i] = '\0';
	fix_minus(ret);
	if (!ft_strchr(ret, '('))
		fix_hex(e, &ret);
	free(prec);
	return (ret);
}

char	*elem_fill_buffer(t_elem *e)
{
	char	*prec;
	char	*buffer;

	if (e->type == '%')
		return (ft_strdup("%"));
	prec = elem_fill_prec(e);
	if (!prec)
		return (0);
	buffer = elem_fill_align(e, prec);
	return (buffer);
}
