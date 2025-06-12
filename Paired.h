#pragma once

//used with ClassTemplates.cpp

//dont forget full defintions for templates are needed and dw they are exempted of ODR 
template <typename T>
struct Paired
{
	T first;
	T second;
};

template<typename T>
constexpr T max(Paired<T> p)
{
	return(p.first > p.second) ? p.first : p.second;
}