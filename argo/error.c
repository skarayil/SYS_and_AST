/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 18:17:56 by skarayil          #+#    #+#             */
/*   Updated: 2026/10/29 18:17:58 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argo.h"

int	peek(FILE *stream)
{
	int	c;

	c = getc(stream);
	if (c != EOF)
		ungetc(c, stream);
	return (c);
}

void	unexpected(FILE *stream)
{
	int	c;

	c = peek(stream);
	if (c == EOF)
		printf("Unexpected end of input\n");
	else
		printf("Unexpected token '%c'\n", c);
}

int	accept(FILE *stream, int c)
{
	if (peek(stream) == c)
	{
		getc(stream);
		return (1);
	}
	return (0);
}

int	expect(FILE *stream, int c)
{
	if (accept(stream, c))
		return (1);
	unexpected(stream);
	return (0);
}
