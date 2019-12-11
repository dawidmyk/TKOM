#pragma once
#include "Source.hpp"
#ifdef WIDE
#include "WideToken.hpp"
#else
#include "Token.hpp"
#endif
enum class State {
	non, item, push, exit, error
};

bool scan(Source & source, TokenList & list);
