#include <iostream>
#include <tuple>
#include <functional>

template <typename ...Types>
class Package
{
public:
	template <size_t arg_idx>
	void insert(const std::tuple_element_t<arg_idx, std::tuple<Types...>>& value)
	{
		std::get<arg_idx>(m_data) = value;
	}

	constexpr size_t getNumArgs() const noexcept
	{
		return std::tuple_size<std::tuple<int>>::value;
	}

	template <size_t arg_idx>
	const std::tuple_element_t<arg_idx, std::tuple<Types...>>& getElement() const
	{
		return std::get<arg_idx>(m_data);
	}

	const std::tuple<Types...> getTuple() const
	{
		return m_data;
	}

private:
	std::tuple<Types...> m_data;
};


template <typename Functor, typename T>
void _unpack(const std::tuple<T>& last_tup, Functor fn)
{
	int a = 30;
}

template <typename Functor, typename T1, typename ...Ts>
void _unpack(const std::tuple<T1, Ts...>& tup, Functor fn)
{
	int a = 30;
	//_unpack()
}

template <typename Functor, typename T1, typename ...Ts>
void unpack(const Package<T1, Ts...>& input_pack, Functor fn)
{
	size_t num_args = input_pack.getNumArgs();
	_unpack(input_pack.getTuple(), fn);
}
/// <summary>
/// 
/// </summary>
/// <param name="arg1"></param>
/// <param name="arg2"></param>
/// <returns></returns>
Package<int, int> adder(int arg1, int arg2)
{
	Package<int, int> ret_package;
	ret_package.insert<0>(arg1 + arg2);
	ret_package.insert<1>(arg1 - arg2);

	return ret_package;
}

/// <summary>
/// 
/// </summary>
/// <param name="arg1"></param>
void scaler(int arg1)
{
	std::cout << arg1 * 5 << std::endl;
}


int main(void)
{
	auto pack_from_adder = adder(3, 5);
	std::cout << pack_from_adder.getNumArgs() << std::endl;

	unpack(pack_from_adder, scaler);
	
	return 0;
}