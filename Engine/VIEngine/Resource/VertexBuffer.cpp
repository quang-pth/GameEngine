#include"VertexBuffer.h"
#include"ResourceManager.h"

namespace VIEngine {
	DEFINE_RTTI(VertexBuffer, Object::RunTimeType)

	VertexBuffer* VertexBuffer::Create() {
		return ResourceManager::Get().NewVertexBuffer();
	}
}