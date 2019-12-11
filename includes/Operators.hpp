#pragma once
#include <set>
#include <map>
#ifdef WIDE
#include "WideCharacter.hpp"
#else
#include "Character.hpp"
#endif

enum class OperatorType {
	op_plus,
	op_minus,
	op_equal,
	op_multiply,
	op_divide,
	op_power,
	op_sqrt,
	op_log,
	op_modulo_down,
	op_modulo_up,
	op_lower,
	op_higher,
	op_abs,
	op_neg,
	op_bool,
	op_neg_bool,
	op_right,
	op_left,
	op_dot,
	op_signum,
	op_shift,
	op_decl,
	op_default,
	op_concrete,
	op_comma,
	op_ins,
	op_brace_open,
	op_brace_close,
	op_parenth_open,
	op_parenth_close,
	op_unspec,
	op_none
};
class Continues {
	bool solitude;
	//czy sam jest ok.
	std::set<Character> options;
	public:
	Continues(): solitude(true) {}
	Continues(const Character & one): solitude(true) {
		options.insert(one);
	}
	bool continuee(const Character & i) {
		return (options.find(i) != options.end());
	}
	void addChar(const Character & i) {
		options.insert(i);
	}
	void addChain(const Chain & str) {
		for(auto i : str) {
			options.insert(Character(i));
		}
	}
	void setNotSolitude() {
		solitude = false;
	}
	bool isSolitude() {
		return solitude;
	}
	void pour();
	//bool operator < (const Continues & 
};
class Operators {
	static Operators instance;
	std::map<Chain, Continues> options;
	std::map<Character, Character> preceders;
	public:
	Operators() {
	}
	void add(const Chain & str, const Continues & c) {
		auto i = options.insert(std::pair(str, c));
		if(!i.second) options.at(str) = c;
	}
	void add(const Chain & str, const Character & one);
	void add(const Character & former, const Character & later) {
		preceders.insert(std::pair(later, former));
	}
	void addDefaults(const Chain & str) {
		for(auto i : str) {

			options.insert(std::pair(Chain(i), Continues()));
		}
	}
	
	bool i_joinable(const Chain & str, const Character & i);
	
	static bool joinable(const Chain & str, const Character & i) {
		return instance.i_joinable(str, i);
	}
	
	static void start() {
		instance.hardcode();
	}
	
	void hardcode();
	static void pour(const Chain & str);
	static void pour();
};
	
OperatorType operator_filtr(const Chain & str);




