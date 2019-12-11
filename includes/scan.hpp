#pragma once
#include "Source.hpp"
#ifdef WIDE
#include "WideToken.hpp"
#else
#include "Token.hpp"
#endif
enum class State {
	non, item, push, exit, error
}; //takie jakby stany automatu
//lexerującego

bool scan(Source & source, TokenList & list);
/* Zastanawiałem się czy TokenListu (bo to wynik)
 * nie zwracać, ale nie chciałem się bawić w std::pair
 * /std::tuple 
 * także sukces lexykacji można było osadzić w source */
