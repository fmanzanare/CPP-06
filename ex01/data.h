/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:09:56 by fmanzana          #+#    #+#             */
/*   Updated: 2023/07/28 16:57:31 by fmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
#define DATA_H

#include <iostream>

typedef struct Data {
	int		x;
	float	y;
	char	c;
}			Data;

uintptr_t serialize(Data *ptr);
Data *deserialize(uintptr_t raw);

#endif
