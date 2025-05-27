#pragma once

#include <fstream>
#include <iostream>
#include <functional>
#include <string_view>

/**
 * @brief Abstract class for all tests.
*/
class ATest
{
public:
	/**
	 * @brief Default constructor.
	 * @param aName Name of the test.
	 */
	explicit ATest( const std::string_view aName );

	/**
	 * @brief Virtual destructor to avoid instantiation of interface class.
	*/
	virtual ~ATest();

	/**
	 * @brief Public interface to run the test.
	*/
	void Run();

	/**
	 * @brief Exception checker.
	*/
	static void CheckException( const std::function<void()>& aFunction, const std::string_view aExpectedErrorMsg );

private:
	/**
	 * @brief Results checker.
	*/
	void CheckResults( const std::vector<std::string>& aObtained, const std::vector<std::string>& aExpected );

	/**
	 * @brief Private implementation to test exceptions.
	*/
	virtual void TestExceptions() = 0;

	/**
	 * @brief Private implementation to get the obtained results from the test.
	*/
	virtual std::vector<std::string> ObtainedResults() noexcept = 0;

	/**
	 * @brief Private implementation to get the expected results from the test.
	*/
	virtual constexpr std::vector<std::string> ExpectedResults() noexcept = 0;

	//! Stream for the expected results.
	std::ofstream mExpectedStream;
	//! Stream for the obtained results.
	std::ofstream mObtainedStream;
	//! Name for the test.
	const std::string_view mName;
};

/**
 * @brief Macro to initialize derived test class from ATest.
*/
#define INITIALIZE_CLASS( CLASS )												\
	class CLASS : public ATest													\
	{																			\
	public:																		\
		explicit CLASS( const std::string_view aName ) :									\
			ATest( aName )														\
		{																		\
		}																		\
	private:																	\
		void TestExceptions() override; 									\
		std::vector<std::string> ObtainedResults() noexcept override; 	\
		std::vector<std::string> ExpectedResults() noexcept override; 	\
	};

/**
 * @brief Macro to write the main function.
*/
#define INITIALIZE_MAIN( CLASS )				\
	int main() try								\
	{											\
		CLASS{ #CLASS }.Run();					\
		return 0;								\
	}											\
	catch(const std::exception& aException)		\
	{											\
		std::cerr << aException.what() << "\n";	\
		throw;									\
	}

/**
 * @brief Macro to initialize the code to perform the test.
*/
#define INITIALIZE_TEST( CLASS )		\
	INITIALIZE_CLASS( CLASS )			\
	INITIALIZE_MAIN( CLASS )
