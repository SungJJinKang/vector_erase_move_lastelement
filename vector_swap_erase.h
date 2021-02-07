#pragma once

#include <cassert>
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
	/// <returns>iterator at replaced element's pos</returns>
	template <typename T, typename Allocator>
	typename void vector_swap_erase(std::vector<T, Allocator>& vector, typename std::vector<T, Allocator>::size_type erasedElementIndex)
	{
		size_t size = vector.size();

		assert(size != 0);
		assert(erasedElementIndex >= 0 && erasedElementIndex < size); // out of range

		if (erasedElementIndex != size - 1)
		{// if i isn't last element
			std::iter_swap(vector.begin() + erasedElementIndex, vector.end() - 1);
		}

		vector.pop_back();
		return; //fast because vector is internally just array, so this is just adding array offset to pointer
	}

	template <typename T, typename Allocator>
	typename void vector_swap_erase(std::vector<T, Allocator>& vector, typename std::vector<T, Allocator>::iterator erasedElementIterator)
	{
		assert(vector.size() != 0);
		assert(vector.end() != erasedElementIterator); // erasedElementIterator should be valid iterator

		if (vector.end() - 1 != erasedElementIterator)
		{// if i isn't last element
			std::iter_swap(erasedElementIterator, vector.end() - 1);
		}

		vector.pop_back();
		return; //fast because vector is internally just array, so this is just adding array offset to pointer
	}
}