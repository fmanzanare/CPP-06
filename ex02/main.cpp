/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:28:12 by fmanzana          #+#    #+#             */
/*   Updated: 2023/07/28 18:28:39 by fmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Base	*generate(void) {
	std::srand(std::time(NULL));
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

int main(void) {
	Base	*ptr;

	ptr = generate();
	identify(ptr);

	delete ptr;

	return (0);
}
