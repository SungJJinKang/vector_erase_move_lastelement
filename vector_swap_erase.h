#pragma once

#include <vector>
#include <algorithm>

namespace std
{
	/// <summary>
	/// How Work?? : 
	/// 
	/// This is how vector::erase works.
	/// 	1  2  3  4  5
	///
	///	1  X  3  4  5 (X is deleted element)
	/// 
	/// 	1 * *3  4  5 * *(element '3', '4', '5' is reallocated, this is sometimes too expensive)
	/// 
	///  How my library's vector_swap_erase works
	/// 
	/// 	1  2  3  4  5
	/// 
	/// 	1  X  3  4  5 (X is deleted element)
	/// 
	/// 	1 * *5 * *3  4  (only element '5' is reallocated)
	/// 
	/// 
	/// why iterator argument isn't supported?? : with iterator, should iterate to end element to find last element.
	/// but with index argument, can access to last element directly ( stl_vector internally has pointer of last elemet )
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="vector"></param>
	/// <param name="erasedElementIndex">index of erased element ( 0 ~ vector size )</param>
	/// <returns>iterator at replaced element's new iterator, check with vector::end()</returns>
	template <typename T, typename Allocator>
	typename std::vector<T, Allocator>::iterator vector_swap_erase(std::vector<T, Allocator>& vector, typename std::vector<T, Allocator>::size_type erasedElementIndex)
	{
		size_t size = vector.size();

		if (size == 0 || erasedElementIndex < 0 || erasedElementIndex >= size)
			return vector.end();

		if (erasedElementIndex != size - 1)
		{// if i isn't last element
			std::iter_swap(vector.begin() + erasedElementIndex, vector.end() - 1);
		}

		vector.pop_back();
		return vector.begin() + erasedElementIndex; //fast because vector is internally just array, so this is just adding array offset to pointer
	}

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="Allocator"></typeparam>
	/// <param name="vector"></param>
	/// <param name="erasedElementIterator"></param>
	/// <returns>iterator at replaced element's new iterator, check with vector::end()</returns>
	template <typename T, typename Allocator>
	typename std::vector<T, Allocator>::iterator vector_swap_erase(std::vector<T, Allocator>& vector, typename std::vector<T, Allocator>::iterator erasedElementIterator)
	{
		if (vector.size() == 0) 
			return vector.end();

		auto endIterator = vector.end();
		if (erasedElementIterator == endIterator)
			return vector.end(); // if erasedElementIterator is endIterator

		if (endIterator - 1 != erasedElementIterator)
		{// if i isn't last element
			std::iter_swap(erasedElementIterator, vector.end() - 1);
		}

		vector.pop_back();
		return erasedElementIterator; //fast because vector is internally just array, so this is just adding array offset to pointer
	}
}
