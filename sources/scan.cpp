#include "scan.hpp"
#include "Operators.hpp"
bool scan(Source & source, TokenList & result) {
	Chain actual;
	bool toDiscard = true;
	State actualState = State::non;
	TokenType nextType;
	Character current;
	/* dzięki temu że trzymamy go tu, nie musimy go trzymać w
	 * Sourc'ie */
	int limit = 1;
	bool limitAchieved = false; //czy zebrało się za dużo znaków
	//w tokenie
	int nested = 0; //zagnieżdżanie komentarzy jest możliwe
	//ale to jest zrobione poza gramatyką jakąkolwiek
	while(actualState != State::exit && actualState != State::error) {
		/* exit będzie na końcu pliku
		* i są pewne błędy, które można wykryć już na etapie leksera
		* i wtedy będzie State error */
		if(actualState == State::push) { 
			/* stan dodawania nowego tokena
			 * do wyniku */
			if(nextType == TokenType::op && !Operators::joinable(actual, '\0'))
					actualState = State::error;
					/* tylko w zbieraniu operatora mogliśmy
					 * się byli pomylić */
			else if(limitAchieved)
					actualState = State::error;
			else {
				result.append(Token(nextType, actual));
				actual.clear(); 
				/* skoro już wysłaliśmy token,
				 * to możemy zacząć zbierać nowy token */
				if(current.isSpace()||nextType == TokenType::comment) toDiscard = true;
				/* po białym znaku i po komentarzu trzeba poprosić o nowy znak,
				 * w przeciwnym razie nowy istotny 
				 * znak już się pojawił i siedzi w current */
				else toDiscard = false;
				if(current.isEnd()) actualState = State::exit;
				else actualState = State::non;
			}
		}
		else {
			if(toDiscard) current = source.getNextChar();
			if(actualState == State::non) {
				limit = 0;
				/* non oznacza że aktualnie nie zbieramy
				 * żadnego tokena, ale jesteśmy gotowi
				 * zacząć */
				toDiscard = true;
				if(current.isEnd()) actualState = State::exit;
				else if(!current.isSpace()) {
					/* jeżeli jest biały znak, to nic tak
					 * naprawdę się nie zaczyna */
					source.assign();
					/* źródło musi wiedzieć że tu zaczyna
					 * się nowo rozpoczęty token
					 * żeby mogło np. dobrze zaraportować błąd
					 * w tym tokenie */
					actualState = State::item;
					if(current.isDigit()) nextType = TokenType::nume;
					else if(current.isLetter()) nextType = TokenType::id;
					else if(current.isOp()) {
						if(current.getChar() == ']') actualState = State::non;
						else if(current.getChar() == '[') nextType = TokenType::comment;
						
						/* znak zamknięcia komentarza gdy nie rozpoczęto
						 * komentarza nic nie robi*/
						else nextType = TokenType::op;
					}
					else actualState = State::non;
					/* powyższe jest bardzo ważne, bo pozwoli odrzucić wszystkie znaki
					 * które są niewiadomo czym (i nie będą one powodowały błędu)
					 * po prostu je olejemy
					 * np. jakieś znaki o numerze ascii 1 (oczywiście co innego
					 * będzie przy opcji WIDE), tak więc możemy się spodziewać że
					 * przy nieustawionym WIDE oleje albo przekręci różne ś albo ↑ */
					if(nextType != TokenType::comment && actualState == State::item)
						/* komentarz jest tokenem, który także zbieramy
						 * ale nie zbieramy do niego tych [] które go
						 * zaczynają i kończą */
						actual.append(current);
				}
			}
			else if(actualState == State::item) {
				/* poniższy blok musi być pierwszy bo w komentarzu
				 * mogą się znajdować wszystkie inne znaki */
				if(nextType == TokenType::comment) {
					if(current.isEnd()) actualState = State::push;
					// pozwalam na niedomykanie komentarzy na końcu pliku
					else {
						if(current.getChar()=='[') nested++;
						else if(current.getChar()==']') {
							if(nested == 0)
							actualState = State::push;
							else nested--;
						}
						if(actualState == State::item) actual.append(current);
					}
				}
				else if(isWhite(current)) actualState = State::push;
				/* był item, a teraz jest spacja, trzeba go wysłać,
				 * bo wiadomo że teraz się skończył */
				else if(current.isOp()) { 
					if(nextType == TokenType::op && Operators::joinable(actual, current))
						//a +='3 -> to są 3 operatory: + = oraz '
						actual.append(current);
					else actualState = State::push;
				}
				else if(current.isDigit()) {
					if(nextType == TokenType::op) actualState = State::push;
					else actual.append(current);
					limit++;
					if(limit == Source::critical) {
						limitAchieved = true;
						actualState = State::push;
					}
					// tk345 to akceptowalny identyfikator
				}
				else if(current.isLetter()) {
					
					if(nextType == TokenType::op) actualState = State::push;
					else if(nextType == TokenType::nume) actualState = State::error;
					// token typu 454df jest błędny, nie miałby czego oznaczać
					else actual.append(current);
					limit++;
					if(limit == Source::critical) {
						limitAchieved = true;
						actualState = State::push;
					}
				}
			}
		}
	}
	if(actualState == State::error) result.append(Token(TokenType::mistake, actual));
	return (actualState == State::exit);
	// w przeciwnym razie jest State error, czyli nie ma sukcesu
}
