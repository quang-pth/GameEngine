#include"VertexBuffer.h"
#include"Core/Application.h"
#include"Resource/ResourceManager.h"

namespace VIEngine {
	DEFINE_RTTI(VertexBuffer, Object::RunTimeType)

	VertexBuffer* VertexBuffer::Create() {
		return ResourceManager::Get().NewVertexBuffer();
	}
}