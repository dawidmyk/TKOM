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
	int assigned;
	int readed;
	int width;
	int tabs;
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
	}
	void printError(const Token & mistake);
	const static int critical;
};




	



			
					
				
		
