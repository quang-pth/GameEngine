#pragma once

#include"pch.h"
#include<glm/glm.hpp>
#include"VertexFormat.h"

namespace VIEngine {
    class VI_API Sprite {
    public:
        static Sprite* Create(const std::string& filepath);
    public:
        Sprite() = default;
        Sprite(const std::string& filepath);
        ~Sprite();
        void Release();
        VI_FORCE_INLINE class Texture2D* GetTexture() const { return mTexture; }
        VI_FORCE_INLINE bool GetIsDirty() const { return mIsDirty; }
        VI_FORCE_INLINE void SetIsDirty(bool value) { mIsDirty = value; }
        VI_FORCE_INLINE const glm::vec4& GetColor() const { return mColor; }
        VI_FORCE_INLINE void SetColor(const glm::vec4& value) { mColor = value; }
        VI_FORCE_INLINE const std::string& GetFilepath() const { return mFilePath; }
        VI_FORCE_INLINE void SetFilePath(const std::string& value) { mFilePath = value; }
        VI_FORCE_INLINE const std::string& GetName() const { return mName; }
        VI_FORCE_INLINE void SetName(const std::string& value) { mName = value; }
    private:
        class Texture2D* mTexture;
        bool mIsDirty = false;
        std::string mFilePath;
        std::string mName;
        glm::vec4 mColor = glm::vec4(1.0f);
    };
}