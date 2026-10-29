/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 18:17:29 by skarayil          #+#    #+#             */
/*   Updated: 2026/10/29 18:17:30 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argo.h"

int	argo(json **dst, FILE *stream)
{
	if (parse_value(dst, stream) != 1)
		return (-1);
	if (peek(stream) != EOF)
	{
		unexpected(stream);
		free_json(*dst);
		*dst = NULL;
		return (-1);
	}
	return (1);
}
