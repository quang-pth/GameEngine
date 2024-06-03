#include"RTTI.h"

namespace VIEngine {
	RTTI::RTTI(const char* typeName, const RTTI* parent) : mTypeName(typeName), mParentClass(parent) {

	}

	bool RTTI::IsTypeOf(const RTTI& other) const {
		return !strcmp(mTypeName, other.mTypeName);
	}

	bool RTTI::IsDerivedFrom(const RTTI& other) const {
		const RTTI* parent = this;

		while (parent) {
			if (!strcmp(parent->mTypeName, other.mTypeName)) {
				return true;
			}

			parent = parent->mParentClass;
		}

		return false;
	}

	const char* RTTI::GetTypeName() const { 
		return mTypeName; 
	}

	const RTTI* RTTI::GetParentClass() const { 
		return mParentClass; 
	}
}