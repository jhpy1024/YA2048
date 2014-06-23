#include "Util.hpp"

std::default_random_engine Random::m_Generator;

int Random::genInt(int lower, int upper)
{
	std::uniform_int_distribution<int> distribution(lower, upper);
	return distribution(m_Generator);
}