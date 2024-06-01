#include"RTTI.h"

namespace VIEngine {
	RTTI::RTTI(const char* type, const RTTI* parent) : mType(type), mParentClass(parent) {

	}

	bool RTTI::IsTypeOf(const RTTI& other) const {
		return !strcmp(mType, other.mType);
	}

	bool RTTI::IsDerivedFrom(const RTTI& other) const {
		const RTTI* parent = this;
		
		while (parent) {
			if (!strcmp(parent->mType, other.mType)) {
				return true;
			}

			parent = parent->mParentClass;
		}

		return false;
	}

	const char* RTTI::GetTypeName() const { 
		return mType; 
	}

	const RTTI* RTTI::GetParentClass() const { 
		return mParentClass; 
	}
}