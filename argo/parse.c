/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 18:18:16 by skarayil          #+#    #+#             */
/*   Updated: 2026/10/29 18:18:18 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argo.h"

static char	*read_string(FILE *stream)
{
	char	*out;
	char	*tmp;
	size_t	len;
	size_t	cap;
	int		c;

	len = 0;
	cap = 16;
	out = malloc(cap);
	if (!out)
		return (NULL);
	if (!expect(stream, '"'))
		return (free(out), (char *)NULL);
	while ((c = getc(stream)) != EOF && c != '"')
	{
		if (c == '\\')
		{
			c = getc(stream);
			if (c != '\\' && c != '"')
			{
				free(out);
				unexpected(stream);
				return (NULL);
			}
		}
		if (len + 1 >= cap)
		{
			cap *= 2;
			tmp = realloc(out, cap);
			if (!tmp)
				return (free(out), (char *)NULL);
			out = tmp;
		}
		out[len++] = (char)c;
	}
	if (c != '"')
	{
		free(out);
		printf("Unexpected end of input\n");
		return (NULL);
	}
	out[len] = '\0';
	return (out);
}

int	parse_string(json **dst, FILE *stream)
{
	json	*v;
	char	*s;

	s = read_string(stream);
	if (!s)
		return (-1);
	v = calloc(1, sizeof(json));
	if (!v)
		return (free(s), -1);
	v->type = STRING;
	v->value.string = s;
	*dst = v;
	return (1);
}

int	parse_integer(json **dst, FILE *stream)
{
	int		c;
	int		sign;
	int		n;
	json	*v;

	sign = 1;
	n = 0;
	c = peek(stream);
	if (c == '-')
	{
		getc(stream);
		sign = -1;
		c = peek(stream);
	}
	if (!isdigit((unsigned char)c))
		return (unexpected(stream), -1);
	while (isdigit((unsigned char)(c = peek(stream))))
		n = n * 10 + (getc(stream) - '0');
	v = calloc(1, sizeof(json));
	if (!v)
		return (-1);
	v->type = INTEGER;
	v->value.integer = n * sign;
	*dst = v;
	return (1);
}

static int	add_pair(json *obj, char *key, json *val)
{
	pair	*tmp;
	size_t	size;

	size = obj->value.object.size;
	tmp = realloc(obj->value.object.data, (size + 1) * sizeof(pair));
	if (!tmp)
		return (-1);
	obj->value.object.data = tmp;
	tmp[size].key = key;
	tmp[size].value = val;
	obj->value.object.size++;
	return (1);
}

int	parse_map(json **dst, FILE *stream)
{
	json	*obj;
	char	*key;
	json	*val;

	if (!expect(stream, '{'))
		return (-1);
	obj = calloc(1, sizeof(json));
	if (!obj)
		return (-1);
	obj->type = MAP;
	if (accept(stream, '}'))
		return (*dst = obj, 1);
	while (1)
	{
		key = read_string(stream);
		if (!key)
			return (free_json(obj), -1);
		if (!expect(stream, ':'))
			return (free(key), free_json(obj), -1);
		val = NULL;
		if (parse_value(&val, stream) != 1)
			return (free(key), free_json(obj), -1);
		if (add_pair(obj, key, val) != 1)
			return (free(key), free_json(val), free_json(obj), -1);
		if (accept(stream, '}'))
			break ;
		if (!expect(stream, ','))
			return (free_json(obj), -1);
	}
	*dst = obj;
	return (1);
}

int	parse_value(json **dst, FILE *stream)
{
	int	c;

	c = peek(stream);
	if (c == '"')
		return (parse_string(dst, stream));
	if (c == '{')
		return (parse_map(dst, stream));
	if (c == '-' || isdigit((unsigned char)c))
		return (parse_integer(dst, stream));
	unexpected(stream);
	return (-1);
}
