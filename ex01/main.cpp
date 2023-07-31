/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:01:22 by fmanzana          #+#    #+#             */
/*   Updated: 2023/07/31 18:29:12 by fmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.hpp"

uintptr_t serialize(Data *ptr) {
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data *deserialize(uintptr_t raw) {
	return (reinterpret_cast<Data *>(raw));
}

int main(void) {
	Data	data;

	data.x = 10;
	data.y = 5.15f;
	data.c = 'a';

	uintptr_t	ptr;
	Data		*data_ptr;

	ptr = serialize(&data);
	data_ptr = deserialize(ptr);

	std::cout << "Original Data: " << &data << std::endl;
	std::cout << "uinptr_t: " << &ptr << std::endl;
	std::cout << "Data ptr: " << data_ptr << "\n" << std::endl;

	std::cout << "Data ptr info:" << std::endl;
	std::cout << data_ptr->c << " | " << data_ptr ->y << " | " << data_ptr->x << std::endl;
}

