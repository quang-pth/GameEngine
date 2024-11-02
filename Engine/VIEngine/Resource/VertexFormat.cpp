#include"VertexFormat.h"
#include<glm/glm.hpp>

namespace VIEngine {
    VertexFormat::VertexFormat() : mVertexAttributes() {

    }

    VertexFormat::~VertexFormat() {

    }

    void VertexFormat::AddAttribute(EVertexAttributeType type, const std::string& name, bool normalize) {
        mVertexAttributes.push_back({type, normalize, mStride, mLocation, name});
        mLocation++;
        switch (type)
        {
        case EVertexAttributeType::Int:
            mStride += sizeof(int);
            break;
        case EVertexAttributeType::Int2:
            mStride += sizeof(glm::ivec2);
            break;
        case EVertexAttributeType::Int3:
            mStride += sizeof(glm::ivec3);
            break;
        case EVertexAttributeType::Int4:
            mStride += sizeof(glm::ivec4);
            break;
        case EVertexAttributeType::Float:
            mStride += sizeof(float);
            break;
        case EVertexAttributeType::Float2:
            mStride += sizeof(glm::vec2);
            break;
        case EVertexAttributeType::Float3:
            mStride += sizeof(glm::vec3);
            break;
        case EVertexAttributeType::Float4:
            mStride += sizeof(glm::vec4);
            break;
        case EVertexAttributeType::Mat2:
            mStride += sizeof(glm::mat2);
            break;
        case EVertexAttributeType::Mat3:
            mStride += sizeof(glm::mat3);
            break;
        case EVertexAttributeType::Mat4:
            mStride += sizeof(glm::mat4);
            break;
        default:
            VI_ASSERT(false && "Invalid vertex attribute type");
            break;
        }
    }
}