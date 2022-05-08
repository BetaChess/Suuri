#ifndef BIGUINT_H
#define BIGUINT_H

#include <cmath>
#include <vector>
#include <type_traits>
namespace suuri
{
	class BigUInt
	{
	public:
		using DigitType = uint32_t;

		template<
			typename dT,
			typename = std::enable_if_t<std::is_arithmetic_v<typename std::iterator_traits<dT>::value_type>>,
			typename T = typename dT::value_type
		>
		explicit operator T() const
		{
			
		};

	private:
		std::vector<DigitType> digits_;

	};
}

#endif // BIGUINT_H
