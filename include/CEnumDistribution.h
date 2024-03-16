#pragma once

#include <random>

namespace futsim
{

/**
 * @brief Class that defines a distribution that produces random enum values.
 * @details It wraps an <a href="https://en.cppreference.com/w/cpp/numeric/random/discrete_distribution">std::discrete_distribution</a> to convert the integer values into an enum.
 * @pre The enum must be representable with integer values in the range \f$[0,n]\f$, where n is the number of weights.
*/
template <typename tEnumType, typename tIntType = int>
class CEnumDistribution : public std::discrete_distribution<tIntType>
{
};

} // futsim namespace