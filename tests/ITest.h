#pragma once

#include <functional>
#include <string_view>

/**
 * @brief Interface class for all tests.
*/
class ITest
{
public:
	/**
	 * @brief Virtual destructor to avoid instantiation of interface class.
	*/
	virtual ~ITest() = default;

	/**
	 * @brief Public interface to run the test.
	*/
	void Run() const;

	/**
	 * @brief Exception checker.
	*/
	static void CheckException( const std::function<void()>& aFunction, const std::string_view aExpectedErrorMsg );

private:
	/**
	 * @brief Private implementation to run the test.
	*/
	virtual void DoRun() const = 0;
};

/**
 * @brief Macro to initialize derived test class from ITest.
*/
#define INITIALIZE_CLASS( CLASS )		\
	class CLASS : public ITest			\
	{									\
		void DoRun() const override; 	\
	};

/**
 * @brief Macro to write the main function.
*/
#define INITIALIZE_MAIN( CLASS )				\
	int main() try								\
	{											\
		CLASS{}.Run();							\
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
