#include"VertexArray.h"
#include"ResourceManager.h"

namespace VIEngine {
	DEFINE_RTTI(VertexArray, Object::RunTimeType)
	
	VertexArray* VertexArray::Create(bool useBatchedVertex) {
		return ResourceManager::Get().NewVertexArray(useBatchedVertex);
	}
	
	VertexArray* VertexArray::Create(const VertexFormat& vertexFormat) {
		return ResourceManager::Get().NewVertexArray(vertexFormat);
	}
}