#pragma once

#include"pch.h"

namespace VIEngine {
	class VI_API RenderBatch {

	};

	class VI_API BatchRenderer {
	public:
		BatchRenderer();
		~BatchRenderer();

		void SubmitBatch(class VertexBuffer*, class IndexBuffer*, class Texture2D*);
		bool HasSlot();
	private:
		std::vector<class Texture2D*> mTextures;
	};
}