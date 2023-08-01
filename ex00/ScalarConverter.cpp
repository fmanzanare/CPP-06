/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:13:55 by fmanzana          #+#    #+#             */
/*   Updated: 2023/08/01 16:25:17 by fmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

std::string ScalarConverter::_argv = "";
int ScalarConverter::_num = 0;
char ScalarConverter::_c = 0;
float ScalarConverter::_f = 0;
double ScalarConverter::_d = 0;
bool ScalarConverter::_possible[4] = {false, false, false, false};
int ScalarConverter::_type = 0;
bool ScalarConverter::_pseudolit = false;
bool ScalarConverter::_printable = false;


std::string charArrToString(const char *str) {
	std::string		res = "";

	for (int i = 0; i < (int)strlen(str); i++)
		res += str[i];

	return (res);
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
		if (_argv == pseudolits[i]) {
			_pseudolit = true;
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

	// Checks if the arguments is zero.
	bool only_zero = true;
	for (int i = 0; i < (int)strlen(str); i++) {
		if (str[i] != '0' && str[i] != '.' && str[i] != 'f')
			only_zero = false;
	}
	if (only_zero)
		return (5);

	// Checks if the number is float or double
	if (point == 1 && fchar == 1)
		return (3);
	else if (point == 1)
		return (4);

	// Default return value is for int
	return (2);
}

void	ScalarConverter::converter(const char *str) {
	_argv = charArrToString(str);
	_pseudolit = false;
	_type = parser(str);
	_printable = true;

	long	tmp;
	double	d_tmp;

	switch (_type) {
		case 0:
			_possible[0] = false;
			_possible[1] = false;
			_possible[2] = false;
			_possible[3] = false;
			break ;
		case 1:
			_num = static_cast<int>(_argv.at(0));
			if (_num < 32 || _num > 255 || _num == 127) {
				_possible[0] = false;
				_printable = false;
			}
			else {
				_possible[0] = true;
				_c = _argv.at(0);
			}
			_possible[1] = true;
			_possible[2] = true;
			_possible[3] = true;
			_f = static_cast<float>(_c);
			_d = static_cast<double>(_c);
			break ;
		case 2:
			tmp = std::atol(_argv.c_str());
			if (tmp > INT_MAX || tmp < INT_MIN) {
				_possible[0] = false;
				_possible[1] = false;
			} else if (tmp < 32 || tmp > 255 || tmp == 127) {
				_possible[0] = false;
				_possible[1] = true;
				_printable = false;
				_num = static_cast<int>(tmp);
			} else {
				_possible[0] = true;
				_possible[1] = true;
				_num = static_cast<int>(tmp);
				_c = static_cast<char>(tmp);
			}
			_possible[2] = true;
			_possible[3] = true;
			_f = static_cast<float>(tmp);
			_d = static_cast<double>(tmp);
			break;
		case 3:
			d_tmp = std::strtod(_argv.c_str(), NULL);
			if (d_tmp > std::numeric_limits<float>::max()
				|| d_tmp < std::numeric_limits<float>::min()) {
				_possible[0] = false;
				_possible[1] = false;
				_possible[2] = false;
			} else {
				tmp = static_cast<int>(d_tmp);
				if (tmp > INT_MAX || tmp < INT_MIN) {
					_possible[0] = false;
					_possible[1] = false;
					_possible[2] = true;
					_f = static_cast<float>(d_tmp);
				} else if (tmp < 32 || tmp > 255 || tmp == 127) {
					_possible[0] = false;
					_possible[1] = true;
					_possible[2] = true;
					_printable = false;
					_num = static_cast<int>(d_tmp);
					_f = static_cast<float>(d_tmp);
				} else {
					_possible[0] = true;
					_possible[1] = true;
					_possible[2] = true;
					_num = static_cast<int>(d_tmp);
					_c = static_cast<char>(d_tmp);
					_f = static_cast<float>(d_tmp);
				}
			}
			_possible[3] = true;
			_d = static_cast<double>(d_tmp);
			if (_pseudolit) {
				_possible[0] = false;
				_possible[1] = false;
				_num = 0;
				_c = 0;
			}
			break;
		case 4:
			_d = std::strtod(_argv.c_str(), NULL);
			if (_d > std::numeric_limits<float>::max()
				|| _d < std::numeric_limits<float>::min()) {
				_possible[0] = false;
				_possible[1] = false;
				_possible[2] = false;
			} else {
				tmp = static_cast<int>(_d);
				if (tmp > INT_MAX || tmp < INT_MIN) {
					_possible[0] = false;
					_possible[1] = false;
					_possible[2] = true;
					_f = static_cast<float>(_d);
				} else if (tmp < 32 || tmp > 255 || tmp == 127) {
					_possible[0] = false;
					_possible[1] = true;
					_possible[2] = true;
					_printable = false;
					_num = static_cast<int>(_d);
					_f = static_cast<float>(_d);
				} else {
					_possible[0] = true;
					_possible[1] = true;
					_possible[2] = true;
					_num = static_cast<int>(_d);
					_c = static_cast<char>(_d);
					_f = static_cast<float>(_d);
				}
			}
			_possible[3] = true;
			if (_pseudolit) {
				_possible[0] = false;
				_possible[1] = false;
				_num = 0;
				_c = 0;
			}
			break ;
		case 5:
			_possible[0] = false;
			_printable = false;
			_c = 0;
			_num = 0;
			_possible[1] = true;
			_f = 0.0f;
			_possible[2] = true;
			_d = 0.0;
			_possible[3] = true;
			break;
		default:
			break ;
	}
	printScalars();
}

void	ScalarConverter::printScalars(void) {
	if (_pseudolit) {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		if (_pseudolit && _type == 4)
			std::cout << "float: " << _argv << "f" << std::endl;
		else if (_pseudolit)
			std::cout << "float: " << _argv << std::endl;
		if (_pseudolit && _type == 3) {
			std::cout << "double: ";
			for (int i = 0; i < (int)_argv.size() - 1; i++)
				std::cout << _argv.at(i);
			std::cout << std::endl;
		} else if (_pseudolit)
			std::cout << "double: " << _argv << std::endl;
		return ;
	}

	if (!_possible[0] && !_printable)
		std::cout << "char: Non displayable" << std::endl;
	else if (!_possible[0])
		std::cout << "char: impossible" << std::endl;
	else
		std::cout << "char: " << _c << std::endl;

	if (!_possible[1])
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << _num << std::endl;

	if (!_possible[2])
		std::cout << "float: impossible" << std::endl;
	else if (_f - _num == 0)
		std::cout << "float: " << _f << ".0f" << std::endl;
	else
		std::cout << "float: " << _f << "f" << std::endl;

	if (!_possible[3])
		std::cout << "double: impossible" << std::endl;
	else if (_d - _num == 0)
		std::cout << "double: " << _d << ".0" << std::endl;
	else
		std::cout << "double: " << _d << std::endl;
}

/*
	The class is static and it cannot be instantiated.
	(Constructors, destructor and assignation operator are private)
*/
ScalarConverter::ScalarConverter() {}

ScalarConverter::~ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter &cp) {
	*this = cp;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &cp) {
	_argv = cp._argv;
	_num = cp._num;
	_c = cp._c;
	_f = cp._f;
	_d = cp._d;
	for (int i = 0; i < 4; i++) {
		_possible[i] = cp._possible[i];
	}
	_type = cp._type;
	_pseudolit = cp._pseudolit;
	_printable = cp._printable;
	return (*this);
}
