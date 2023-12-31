/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:10:51 by fmanzana          #+#    #+#             */
/*   Updated: 2023/08/01 13:19:58 by fmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "Arguments must be 2 [program_name + value_to_be_converted]" << std::endl;
		return (1);
	}

	ScalarConverter::converter(argv[1]);

	return (0);
}
