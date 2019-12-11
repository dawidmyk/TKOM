#pragma once
#ifdef WIDE
#include "WideCharacter.hpp"
#include "WideToken.hpp"
#else
#include "Character.hpp"
#include "Token.hpp"
#endif

class Source {
	static int tabWidth;
	/* te wszystkie inty są zbierane dla
	 * ewentualnego komunikatu o błedzie */
	int assigned;
	int readed;
	/* assigned - readed (mniej więcej) rozpina
	 * analizowany token */
	/* readed jest inkrementowane z każdym znakiem
	 * assigned aktualizowane tylko gdy rozpoczyna
	 * się token, trzeba pokazać gdzie zaczyna się 
	 * błędny token, a nie gdzie wykryto błąd */
	int width;
	int tabs; /* taby mogą różnie zajmować,
	* dlatego mamy oddzielną zmienną */
	int height;
	public:
	virtual Character nextChar() = 0;
	static void setTabWidth(int width) {
		tabWidth = width;
	}
	Source(): assigned(0), readed(0), width(0),
		tabs(0), height(0) {}
	Character getNextChar();
	void assign() {
		assigned = readed - 1;
		/* no bo scan wywoła assign dopiero po getNextChar, 
		 * jeśli się okaże że ten char rozpoczyna Token */
	}
	void printError(const Token & mistake);
	//reszta informacji jest tutaj w Source
	const static int critical;
	//nie możemy pozwolić na nieograniczoną długość
	//tokenu, critical to maksymalna długość
};




	



			
					
				
		
