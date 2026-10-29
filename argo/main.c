/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 18:17:15 by skarayil          #+#    #+#             */
/*   Updated: 2026/10/29 18:17:18 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argo.h"

int	main(void)
{
	json	*value;

	value = NULL;
	if (argo(&value, stdin) != 1)
		return (1);
	if (serialize(value) < 0 || write(1, "\n", 1) != 1)
	{
		free_json(value);
		return (1);
	}
	free_json(value);
	return (0);
}
