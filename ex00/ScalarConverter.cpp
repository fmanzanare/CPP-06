/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:13:55 by fmanzana          #+#    #+#             */
/*   Updated: 2023/07/28 14:06:36 by fmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

std::string charArrToString(const char *str) {
	std::string		res = "";

	for (int i = 0; i < (int)strlen(str); i++)
		res += str[i];

	return (res);
}

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const char *str) {
	this->_argv = charArrToString(str);
	this->_pseudolit = false;
	this->_type = parser(str);
	this->_printable = true;
	converter();
	printScalars();
}

ScalarConverter::~ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter &cp) {
	*this = cp;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &cp) {
	this->_argv = cp._argv;
	this->_num = cp._num;
	this->_c = cp._c;
	this->_f = cp._f;
	this->_d = cp._d;
	for (int i = 0; i < 4; i++) {
		this->_possible[i] = cp._possible[i];
	}
	this->_type = cp._type;
	this->_pseudolit = cp._pseudolit;
	this->_printable = cp._printable;
	return (*this);
}

int	ScalarConverter::parser(const char *str) {
	std::string	pseudolits[] = {
		"+inff",
		"-inff",
		"nanf",
		"+inf",
		"-inf",
		"nan"
	};
	int		point = 0;
	int		fchar = 0;

	// Checks if the argument is a pseudliteral.
	for (int i = 0; i < 6; i++) {
		if (this->_argv == pseudolits[i]) {
			this->_pseudolit = true;
			if (i < 3)
				return (3);
			else
				return (4);
		}
	}

	// Checks if it is only one char
	if (!isdigit((int)str[0]) && (int)strlen(str) == 1)
		return (1);

	// Checks if there are more than one '.' or 'f'
	for (int i = 0; i < (int)strlen(str); i++) {
		if (str[i] == '.')
			point++;
		else if (str[i] == 'f')
			fchar++;
	}
	if (point > 1 || fchar > 1)
		return (0);

	// Checks if the argument is not a number
	for (int i = 0; i < (int)strlen(str); i++) {
		if ((!isdigit((int)str[i]) && str[i] != 'f' && str[i] != '.' && str[0] != '-')
			|| str[0] == 'f' || str[0] == '.'
			|| (str[i] == 'f' && i != (int)strlen(str) - 1))
			return (0);
	}

	// Checks if the number is float or double
	if (point == 1 && fchar == 1)
		return (3);
	else if (point == 1)
		return (4);

	// Default return value is for int
	return (2);
}

void	ScalarConverter::converter(void) {
	long	tmp;
	double	d_tmp;

	switch (this->_type) {
		case 0:
			this->_possible[0] = false;
			this->_possible[1] = false;
			this->_possible[2] = false;
			this->_possible[3] = false;
			break ;
		case 1:
			this->_num = static_cast<int>(this->_argv.at(0));
			if (this->_num < 32 || this->_num > 255 || this->_num == 127) {
				this->_possible[0] = false;
				this->_printable = false;
			}
			else {
				this->_possible[0] = true;
				this->_c = this->_argv.at(0);
			}
			this->_possible[1] = true;
			this->_possible[2] = true;
			this->_possible[3] = true;
			this->_f = static_cast<float>(this->_c);
			this->_d = static_cast<double>(this->_c);
			break ;
		case 2:
			tmp = std::atol(this->_argv.c_str());
			if (tmp > INT_MAX || tmp < INT_MIN) {
				this->_possible[0] = false;
				this->_possible[1] = false;
			} else if (tmp < 32 || tmp > 255 || tmp == 127) {
				this->_possible[0] = false;
				this->_possible[1] = true;
				this->_printable = false;
				this->_num = static_cast<int>(tmp);
			} else {
				this->_possible[0] = true;
				this->_possible[1] = true;
				this->_num = static_cast<int>(tmp);
				this->_c = static_cast<char>(tmp);
			}
			this->_possible[2] = true;
			this->_possible[3] = true;
			this->_f = static_cast<float>(tmp);
			this->_d = static_cast<double>(tmp);
			break;
		case 3:
			d_tmp = std::strtod(this->_argv.c_str(), NULL);
			if (d_tmp > std::numeric_limits<float>::max()
				|| d_tmp < std::numeric_limits<float>::min()) {
				this->_possible[0] = false;
				this->_possible[1] = false;
				this->_possible[2] = false;
			} else {
				tmp = static_cast<int>(d_tmp);
				if (tmp > INT_MAX || tmp < INT_MIN) {
					this->_possible[0] = false;
					this->_possible[1] = false;
					this->_possible[2] = true;
					this->_f = static_cast<float>(d_tmp);
				} else if (tmp < 32 || tmp > 255 || tmp == 127) {
					this->_possible[0] = false;
					this->_possible[1] = true;
					this->_possible[2] = true;
					this->_printable = false;
					this->_num = static_cast<int>(d_tmp);
					this->_f = static_cast<float>(d_tmp);
				} else {
					this->_possible[0] = true;
					this->_possible[1] = true;
					this->_possible[2] = true;
					this->_num = static_cast<int>(d_tmp);
					this->_c = static_cast<char>(d_tmp);
					this->_f = static_cast<float>(d_tmp);
				}
			}
			this->_possible[3] = true;
			this->_d = static_cast<double>(d_tmp);
			if (this->_pseudolit) {
				this->_possible[0] = false;
				this->_possible[1] = false;
				this->_num = 0;
				this->_c = 0;
			}
			break;
		case 4:
			this->_d = std::strtod(this->_argv.c_str(), NULL);
			if (this->_d > std::numeric_limits<float>::max()
				|| this->_d < std::numeric_limits<float>::min()) {
				this->_possible[0] = false;
				this->_possible[1] = false;
				this->_possible[2] = false;
			} else {
				tmp = static_cast<int>(this->_d);
				if (tmp > INT_MAX || tmp < INT_MIN) {
					this->_possible[0] = false;
					this->_possible[1] = false;
					this->_possible[2] = true;
					this->_f = static_cast<float>(this->_d);
				} else if (tmp < 32 || tmp > 255 || tmp == 127) {
					this->_possible[0] = false;
					this->_possible[1] = true;
					this->_possible[2] = true;
					this->_printable = false;
					this->_num = static_cast<int>(this->_d);
					this->_f = static_cast<float>(this->_d);
				} else {
					this->_possible[0] = true;
					this->_possible[1] = true;
					this->_possible[2] = true;
					this->_num = static_cast<int>(this->_d);
					this->_c = static_cast<char>(this->_d);
					this->_f = static_cast<float>(this->_d);
				}
			}
			this->_possible[3] = true;
			if (this->_pseudolit) {
				this->_possible[0] = false;
				this->_possible[1] = false;
				this->_num = 0;
				this->_c = 0;
			}
			break ;
		default:
			break ;
	}
}

void	ScalarConverter::printScalars(void) {
	if (this->_pseudolit) {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		if (this->_pseudolit && this->_type == 4)
			std::cout << "float: " << this->_argv << "f" << std::endl;
		else if (this->_pseudolit)
			std::cout << "float: " << this->_argv << std::endl;
		if (this->_pseudolit && this->_type == 3) {
			std::cout << "double: ";
			for (int i = 0; i < (int)this->_argv.size() - 1; i++)
				std::cout << this->_argv.at(i);
			std::cout << std::endl;
		} else if (this->_pseudolit)
			std::cout << "double: " << this->_argv << std::endl;
		return ;
	}

	if (!this->_possible[0] && !this->_printable)
		std::cout << "char: Non displayable" << std::endl;
	else if (!this->_possible[0])
		std::cout << "char: impossible" << std::endl;
	else
		std::cout << "char: " << this->_c << std::endl;

	if (!this->_possible[1])
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << this->_num << std::endl;

	if (!this->_possible[2])
		std::cout << "float: impossible" << std::endl;
	else if (this->_f - this->_num == 0)
		std::cout << "float: " << this->_f << ".0f" << std::endl;
	else
		std::cout << "float: " << this->_f << "f" << std::endl;

	if (!this->_possible[3])
		std::cout << "double: impossible" << std::endl;
	else if (this->_d - this->_num == 0)
		std::cout << "double: " << this->_d << ".0" << std::endl;
	else
		std::cout << "double: " << this->_d << std::endl;
}
