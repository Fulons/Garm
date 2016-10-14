#include "Renderere.h"


namespace garm {
	namespace graphics {

		uint32_t Entity::IDGenerator = 1;


		bool operator ==(const Entity& e1, const Entity& e2){return (e1.getId() == e2.getId()) && (e1.getComponentKey() == e2.getComponentKey());}

	}
}