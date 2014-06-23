#ifndef UTIL_HPP
#define UTIL_HPP

#include <random>

class Random
{
public:
	static int genInt(int lower, int upper);

private:
	static std::default_random_engine m_Generator;
};

#endif