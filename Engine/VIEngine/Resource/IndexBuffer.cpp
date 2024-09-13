#include"IndexBuffer.h"
#include"Core/Application.h"
#include"Resource/ResourceManager.h"

namespace VIEngine {
	DEFINE_RTTI(IndexBuffer, Object::RunTimeType)

	IndexBuffer* IndexBuffer::Create() {
		return ResourceManager::Get().NewIndexBuffer();
	}
}