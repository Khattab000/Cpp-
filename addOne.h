#pragma once
// used with UsingFunctionTemplatesInMultipleFiles.cpp and addOne.cpp

//normally only contatains forward declaration but for templated functions its recommended to put the full definition here and including it wherever you wanna use it
template<typename T>
T addOne(T x)    // function template definition
{
	return x + 1;
}