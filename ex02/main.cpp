/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:28:12 by fmanzana          #+#    #+#             */
/*   Updated: 2023/08/01 11:49:24 by fmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Base	*generate(void) {

	int	r = std::rand();

	while (r > 3)
		r = 1 + std::rand() / ((RAND_MAX + 1u) / 3);

	switch (r) {
		case 1:
			return (new A());
			break ;
		case 2:
			return (new B());
			break ;
		case 3:
			return (new C());
			break ;
		default:
			return (NULL);
			break ;
	}
}

void	identify(Base *p) {
	if (dynamic_cast<A *>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B *>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C *>(p))
		std::cout << "C" << std::endl;
}

void	identify(Base &p) {
	Base obj;

	try {
		obj = dynamic_cast<A &>(p);
		std::cout << "A" << std::endl;
	} catch (std::exception &e) {}
	try {
		obj = dynamic_cast<B &>(p);
		std::cout << "B" << std::endl;
	} catch (std::exception &e) {}
	try {
		obj = dynamic_cast<C &>(p);
		std::cout << "C" << std::endl;
	} catch (std::exception &e) {}
}

int main(void) {
	std::srand(std::time(NULL));
	Base	*ptr;

	ptr = generate();
	identify(ptr);

	delete ptr;

	ptr = generate();
	identify(*ptr);

	delete ptr;

	return (0);
}
