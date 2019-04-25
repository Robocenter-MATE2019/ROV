#pragma once

#include <stdint.h>

template<class BaseType, size_t size_param>
class PolymorphicArray {
public:
	typedef BaseType* BaseTypePtr;
	typedef BaseType** iterator;

	PolymorphicArray() : m_size(0)
	{
		memset(m_data, 0, size_param);
	}
	~PolymorphicArray()
	{
		for (auto &&el : m_data)
		{
			delete el;
		}
	}

	template <class ChildrenType>
	void create()
	{
		if (m_size >= size_param) return;
		m_data[m_size] = new ChildrenType;
		m_size++;
	}

	iterator begin()
	{
		return m_data;
	}
	iterator end()
	{
		return m_data + m_size;
	}

	BaseTypePtr operator[](size_t idx) const
	{
		return m_data[idx];
	}
	BaseTypePtr &operator[](size_t idx)
	{
		return m_data[idx];
	}

	size_t size() const
	{
		return m_size;
	}
	size_t capacity() const
	{
		return size_param;
	}

private:
	BaseTypePtr m_data[size_param];
	size_t m_size;

	PolymorphicArray(const PolymorphicArray<BaseType, size_param>&);
	PolymorphicArray<BaseType, size_param> &operator=(const PolymorphicArray<BaseType, size_param> &rhs);
};
template<class Container, class Method, class ...Args>
void invoke_all(Container &&container, Method &&method, Args &&... args)
{
	for (auto el : container)
	{
		(el->*method)(args...);
	}
}