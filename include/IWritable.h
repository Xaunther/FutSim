#pragma once

#include <ostream>

namespace futsim
{

/**
 * @brief Interface for classes that can be saved and loaded from input/output streams.
 */
class IWritable
{
public:
	/**
	 * @brief Virtual destructor for base class.
	 */
	virtual ~IWritable() = default;

	/**
	 * @brief Output class to stream.
	 * @param aOutput Output stream.
	 */
	virtual void SaveToTXT( std::ostream& aOutput ) const = 0;
};

} // futsim namespace