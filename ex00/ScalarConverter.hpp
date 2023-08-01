/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:10:30 by fmanzana          #+#    #+#             */
/*   Updated: 2023/08/01 16:09:38 by fmanzana         ###   ########.fr       */
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
		static std::string	_argv;
		static int			_num;
		static char			_c;
		static float		_f;
		static double		_d;
		static bool			_possible[4]; // 0-char | 1-int | 2-float | 4-double
		static int			_type; // 0-string | 1-char | 2-int | 3-float | 4-double
		static bool			_pseudolit;
		static bool			_printable;
		static int			parser(const char *str);
		static void			printScalars(void);

		ScalarConverter();
		~ScalarConverter();
		ScalarConverter(const ScalarConverter &cp);
		ScalarConverter &operator=(const ScalarConverter &cp);
	public:
		static void		converter(const char *str);
};

#endif
