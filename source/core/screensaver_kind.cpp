#include "screensaver_kind.hpp"

SCREENSAVER_KIND & operator ++ (SCREENSAVER_KIND & screensaver_kind, int) {
	int i = static_cast<int>(screensaver_kind);
	screensaver_kind = static_cast<SCREENSAVER_KIND>((i == 0)? 1 : i << 1);
	return screensaver_kind;
}
