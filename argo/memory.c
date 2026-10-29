/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 18:18:06 by skarayil          #+#    #+#             */
/*   Updated: 2026/10/29 18:18:09 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argo.h"

void	free_json(json *value)
{
	size_t	i;

	if (!value)
		return ;
	if (value->type == STRING)
		free(value->value.string);
	else if (value->type == MAP)
	{
		i = 0;
		while (i < value->value.object.size)
		{
			free(value->value.object.data[i].key);
			free_json(value->value.object.data[i].value);
			i++;
		}
		free(value->value.object.data);
	}
	free(value);
}
