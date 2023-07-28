/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:10:30 by fmanzana          #+#    #+#             */
/*   Updated: 2023/07/28 13:32:52 by fmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <climits>
#include <limits>

class ScalarConverter {
	private:
		std::string	_argv;
		int			_num;
		char		_c;
		float		_f;
		double		_d;
		bool		_possible[4]; // 0-char | 1-int | 2-float | 4-double
		int			_type; // 0-string | 1-char | 2-int | 3-float | 4-double
		bool		_pseudolit;
		bool		_printable;
		ScalarConverter();
		int			parser(const char *str);
		void		converter(void);
	public:
		ScalarConverter(const char *str);
		~ScalarConverter();
		ScalarConverter(const ScalarConverter &cp);
		ScalarConverter &operator=(const ScalarConverter &cp);
		void		printScalars(void);
};

#endif
