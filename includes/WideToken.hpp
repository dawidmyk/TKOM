#pragma once
#include <string>
#include <vector>
#include <cwchar>
#include "WideCharacter.hpp"
#include "Operators.hpp"
#include "Keyword.hpp"
enum class TokenType {
	id, op, keyword, nume, comment, mistake
};

std::wstring to_string(const TokenType type);

class Token {
	TokenType myType;
	Chain content;
	/* nawet jak wiemy dokładnie jakim jest symbolem
	 * np TokenType::keyword i 
	 * KeywordType::t_end, to i tak przechowujemy
	 * przeparsowany tekst */
	union {
		KeywordType keyword;
		OperatorType op;
	};
	/* jeśli nie jest ani keywordem ani opem, to ta unia
	 * jest niepotrzebna i są w niej śmieci
	 * jeśli jest keywordem to op jest śmieciem itd. */
	public:
	Token(const TokenType myType, const Chain & content):
		myType(myType),
		content(content)
		{
		analize(); //tu robimy "dekorację"
		/* bo metoda scan nie rozróżnia keywordów od idów
		 * i nie rozpoznaje poszczególnych operatorów,
		 * to jest robione tutaj */
		}
	std::wstring to_string() const;
	void analize();
};

class TokenList {
	std::vector<Token> list;
	public:
	void append(const Token token) {
		list.push_back(token);
	}
	void printTokens() {
		for(auto & token : list) {
			wprintf(L"%ls", (token.to_string() + (wchar_t)'\n').c_str());
		}
	}
	Token last() const {
		return list.at(list.size() - 1);
	}
			
};
