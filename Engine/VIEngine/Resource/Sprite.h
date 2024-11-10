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
        VI_FORCE_INLINE class VertexArray* GetVertexArray() const { return mVertexArray; }
        VI_FORCE_INLINE class Shader* GetShader() const { return mShader; }
        VI_FORCE_INLINE uint8_t GetSampleTextureID() const { return mSampleTextureID; }
        VI_FORCE_INLINE void SetSampleTextureID(uint8_t value) { mSampleTextureID = value; }
        VI_FORCE_INLINE int16_t GetBatchSlot() const { return mBatchSlot; }
        VI_FORCE_INLINE void SetBatchSlot(int16_t value) { mBatchSlot = value; }
        VI_FORCE_INLINE bool GetIsDirty() const { return mIsDirty; }
        VI_FORCE_INLINE void SetIsDirty(bool value) { mIsDirty = value; }
        VI_FORCE_INLINE const glm::vec4& GetColor() const { return mColor; }
        VI_FORCE_INLINE void SetColor(const glm::vec4& value) { mColor = value; }
        VI_FORCE_INLINE const std::string& GetFilepath() const { return mFilePath; }
        VI_FORCE_INLINE void SetFilePath(const std::string& value) { mFilePath = value; }
        VI_FORCE_INLINE const std::string& GetName() const { return mName; }
        VI_FORCE_INLINE void SetName(const std::string& value) { mName = value; }
        VI_FORCE_INLINE void SetDepth(float value) { mDepth = value; }
        VI_FORCE_INLINE float GetDepth() const { return mDepth; }
    private:
        class Texture2D* mTexture;
        class VertexArray* mVertexArray;
        class Shader* mShader;
        uint8_t mSampleTextureID = 0;
        int16_t mBatchSlot = 0;
        bool mIsDirty = false;
        std::string mFilePath;
        std::string mName;
        glm::vec4 mColor = glm::vec4(1.0f);
        VertexFormat mVertexFormat;
        float mDepth = 0.0f;
    };
}