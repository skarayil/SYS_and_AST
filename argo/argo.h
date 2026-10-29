/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 18:17:01 by skarayil          #+#    #+#             */
/*   Updated: 2026/10/29 18:17:02 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGO_H
# define ARGO_H

# include <ctype.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_type
{
	MAP = 1,
	INTEGER,
	STRING
}						t_type;

typedef struct s_json	json;

typedef struct s_pair
{
	char				*key;
	json				*value;
}						pair;

typedef struct s_map
{
	pair				*data;
	size_t				size;
}						map;

struct					s_json
{
	t_type				type;
	union
	{
		int				integer;
		char			*string;
		map				object;
	} value;
};

void					free_json(json *value);

int						peek(FILE *stream);
void					unexpected(FILE *stream);
int						accept(FILE *stream, int c);
int						expect(FILE *stream, int c);

int						parse_value(json **dst, FILE *stream);
int						parse_integer(json **dst, FILE *stream);
int						parse_string(json **dst, FILE *stream);
int						parse_map(json **dst, FILE *stream);

int						serialize(json *value);
int						argo(json **dst, FILE *stream);

#endif