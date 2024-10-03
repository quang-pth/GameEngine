#include"VertexArray.h"
#include"ResourceManager.h"

namespace VIEngine {
	DEFINE_RTTI(VertexArray, Object::RunTimeType)
	
	VertexArray* VertexArray::Create() {
		return ResourceManager::Get().NewVertexArray();
	}
}