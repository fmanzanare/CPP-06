/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:09:56 by fmanzana          #+#    #+#             */
/*   Updated: 2023/07/31 18:29:01 by fmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>

typedef struct Data {
	int		x;
	float	y;
	char	c;
}			Data;

uintptr_t serialize(Data *ptr);
Data *deserialize(uintptr_t raw);

#endif
