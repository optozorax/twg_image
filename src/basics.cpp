#include <string>
#include <cmath>
#include <twg/basics.h>

namespace twg 
{

//-----------------------------------------------------------------------------
double computeCycle(double pos, CycleType type) {
	switch (type) {
		case CYCLE_NULL:
			return (pos < 0) ? 0 : ((pos > 1) ? 1 : pos);
		case CYCLE_SIN:
			pos = std::fmod(std::fabs(pos), 2.0);
			pos = (pos > 1) ? 2-pos : pos;
			return pos;
		case CYCLE_TAN:
			return fmod(fabs(pos), 1.0);
	}
}


}