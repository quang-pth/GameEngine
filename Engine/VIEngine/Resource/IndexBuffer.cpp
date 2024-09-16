#include"IndexBuffer.h"
#include"ResourceManager.h"

namespace VIEngine {
	DEFINE_RTTI(IndexBuffer, Object::RunTimeType)

	IndexBuffer* IndexBuffer::Create() {
		return ResourceManager::Get().NewIndexBuffer();
	}
}