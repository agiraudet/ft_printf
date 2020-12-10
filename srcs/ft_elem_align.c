/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_elem_align.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 14:10:36 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/10 14:32:39 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*elem_align(t_elem *e, char *prec)
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
	if (e->type == 'p')
		fix_hex(ret);
	free(prec);
	return (ret);
}

char	*elem_fill_buffer(t_elem *e)
{
	char	*prec;
	char	*buffer;

	if (e->type == '%')
		return (ft_strdup("%"));
	prec = elem_prec(e);
	if (!prec)
		return (0);
	buffer = elem_align(e, prec);
	return (buffer);
}
