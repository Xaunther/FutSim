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
public:
	//! Type for the result.
	using result_type = tEnumType;
	//! Type for the distribution parameters.
	using param_type = std::discrete_distribution<tIntType>::param_type;

	/**
	 * @name Constructs a new distribution object
	 * @details See <a href="https://en.cppreference.com/w/cpp/numeric/random/discrete_distribution/discrete_distribution">std::discrete_distribution constructors</a>
	*/
	//@{
	CEnumDistribution() :
		std::discrete_distribution<tIntType>() {}

	template<typename tInputIt>
	CEnumDistribution( tInputIt aFirst, tInputIt aLast ) :
		std::discrete_distribution<tIntType>( aFirst, aLast ) {}

	CEnumDistribution( std::initializer_list<double> aWeights ) :
		std::discrete_distribution<tIntType>( aWeights ) {}

	template<typename tUnaryOperation>
	CEnumDistribution( std::size_t aCount, double aXmin, double aXmax, tUnaryOperation aUnaryOp ) :
		std::discrete_distribution<tIntType>( aCount, aXmin, aXmax, aUnaryOp ) {}

	explicit CEnumDistribution( const param_type& aParams ) :
		std::discrete_distribution<tIntType>( aParams ) {}
	//@}
};

} // futsim namespace