/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 18:18:25 by skarayil          #+#    #+#             */
/*   Updated: 2026/10/29 18:18:28 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argo.h"

static int	put_char(int c)
{
	if (write(1, &c, 1) != 1)
		return (-1);
	return (1);
}

static int	put_number(int n)
{
	char			digits[12];
	int				count;
	unsigned int	u;

	count = 0;
	if (n < 0)
	{
		if (put_char('-') < 0)
			return (-1);
		u = (unsigned int)(-(n + 1)) + 1;
	}
	else
		u = (unsigned int)n;
	while (u > 0)
	{
		digits[count++] = '0' + u % 10;
		u /= 10;
	}
	if (count == 0)
		digits[count++] = '0';
	while (count > 0)
	{
		if (put_char(digits[--count]) < 0)
			return (-1);
	}
	return (1);
}

static int	put_string(const char *s)
{
	if (put_char('"') < 0)
		return (-1);
	while (*s)
	{
		if (*s == '"' || *s == '\\')
		{
			if (put_char('\\') < 0)
				return (-1);
		}
		if (put_char(*s++) < 0)
			return (-1);
	}
	return (put_char('"'));
}

int	serialize(json *value)
{
	size_t	i;

	if (!value)
		return (-1);
	if (value->type == INTEGER)
		return (put_number(value->value.integer));
	if (value->type == STRING)
		return (put_string(value->value.string));
	if (put_char('{') < 0)
		return (-1);
	i = 0;
	while (i < value->value.object.size)
	{
		if (i && put_char(',') < 0)
			return (-1);
		if (put_string(value->value.object.data[i].key) < 0)
			return (-1);
		if (put_char(':') < 0)
			return (-1);
		if (serialize(value->value.object.data[i].value) < 0)
			return (-1);
		i++;
	}
	return (put_char('}'));
}
