#pragma once

#include"pch.h"

namespace VIEngine {
    enum class EVertexAttributeType {
        Int,
        Int2,
        Int3,
        Int4,
        Float,
        Float2,
        Float3,
        Float4
    };

    struct VI_API VertexAttribute {
        EVertexAttributeType Type;
        bool Normalized;
        uint16_t Offset;
        uint16_t Location;
        std::string Name;
        uint16_t NumsComponent;
    };

    class VI_API VertexFormat {
    public:
        VertexFormat();
        ~VertexFormat();
        void AddAttribute(EVertexAttributeType type, const std::string& name, bool normalized = false);
        VI_FORCE_INLINE uint16_t GetStride() const { return mStride; }
        VI_FORCE_INLINE const std::vector<VertexAttribute>& GetVertexAttributes() const { return mVertexAttributes; }
    protected:
        std::vector<VertexAttribute> mVertexAttributes;
        uint16_t mStride = 0;
        uint16_t mLocation = 0;
    };
}