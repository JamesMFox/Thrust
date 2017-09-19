#pragma once
#include "Vec2.h"
#include <string.h> 

template <typename T>
class _Mat3
{
public:
	_Mat3& operator =(const _Mat3& rhs)
	{
		memcpy(elemtents, rhs.elements, sizeof(elements));
		return *this;
	}
	_Mat3& operator *=(const float rhs)
	{
		for(T& e : elements)
		{
			e *= rhs;
		}
		return *this;
	}
	_Mat3 operator *(const T rhs) const
	{
		_Mat3 result = *this;
		return result *= rhs;
	}
	_Mat3 operator *(const _Mat3& rhs) const
	{
		_Mat3 result;
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				T sum = (T)0.0;
				for (int i = 0; i < 3; i++)
				{
					sum += elements[j][i] * rhs.elements[i][k];
				}
				result.elements[j][k] = sum;
			}
		}
		return result;
	}
	_Mat3& operator *=(const _Mat3& rhs)
	{
		return *this = (*this*rhs);
	}
public:
	// [row][col]
	T elements[3][3];
};

typedef _Mat3<float> Mat3;