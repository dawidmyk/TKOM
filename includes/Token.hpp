#pragma once
#include <string>
#include <cstdio>
#include <vector>
#include "Character.hpp"
#include "Keyword.hpp"
#include "Operators.hpp"
//Patrz komentarze do WideToken.hpp
enum class TokenType {
	id, op, keyword, nume, comment, mistake
};

std::string to_string(const TokenType type);

class Token {
	TokenType myType;
	Chain content;
	union {
		KeywordType keyword;
		OperatorType op;
	};
	public:
	Token(const TokenType myType, const Chain & content):
		myType(myType),
		content(content)
		{
		analize();
		}
	std::string to_string() const;
	void analize();
};

class TokenList {
	std::vector<Token> list;
	public:
	void append(const Token token) {
		list.push_back(token);
	}
	void printTokens() const {
		for(auto & token : list) {
			printf("%s", (token.to_string() + '\n').c_str());
		}
	}
	Token last() const {
		//no bo ten ostatni to może być ten błędny
		return list.at(list.size() - 1);
	}
			
};
