#ifdef WIDE
#include "WideCharacter.hpp"
#else
#include "Character.hpp"
#endif
enum class KeywordType {
	t_loop, t_return, t_end, t_none
};

KeywordType key_filtr(const Chain & str);
/* rozpoznaje czy jest keywordem
 * i zwraca odpowiedni symbol */
