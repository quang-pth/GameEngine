#include"VertexFormat.h"
#include<glm/glm.hpp>

namespace VIEngine {
    VertexFormat::VertexFormat() : mVertexAttributes() {

    }

    VertexFormat::~VertexFormat() {

    }

    void VertexFormat::AddAttribute(EVertexAttributeType type, const std::string& name, bool normalize) {
        uint16_t numsComponent = 0;
        uint16_t offset = mStride;
        switch (type)
        {
        case EVertexAttributeType::Int:
            mStride += sizeof(int);
            numsComponent = 1;
            break;
        case EVertexAttributeType::Int2:
            mStride += sizeof(glm::ivec2);
            numsComponent = 2;
            break;
        case EVertexAttributeType::Int3:
            mStride += sizeof(glm::ivec3);
            numsComponent = 3;
            break;
        case EVertexAttributeType::Int4:
            mStride += sizeof(glm::ivec4);
            numsComponent = 4;
            break;
        case EVertexAttributeType::Float:
            mStride += sizeof(float);
            numsComponent = 1;
            break;
        case EVertexAttributeType::Float2:
            mStride += sizeof(glm::vec2);
            numsComponent = 2;
            break;
        case EVertexAttributeType::Float3:
            mStride += sizeof(glm::vec3);
            numsComponent = 3;
            break;
        case EVertexAttributeType::Float4:
            mStride += sizeof(glm::vec4);
            numsComponent = 4;
            break;
        default:
            VI_ASSERT(false && "Invalid vertex attribute type");
            break;
        }

        mVertexAttributes.push_back({ type, normalize, offset, mLocation, name, numsComponent });
        mLocation++;
    }
}