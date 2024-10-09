#include"Renderer/RenderCommand.h"
#include"OpenGLFactory.h"

#define GLAD_GL_IMPLEMENTATION
#include<glad/gl.h>

namespace VIEngine {
	DEFINE_RTTI_NO_PARENT(OpenGLRenderCommand)

	OpenGLRenderCommand::OpenGLRenderCommand() : mRenderData() {

	}

	OpenGLRenderCommand::~OpenGLRenderCommand() {
		
	}

	void OpenGLRenderCommand::ClearColorImpl(float r, float g, float b, float w) {
		glClearColor(r, g, b, w);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRenderCommand::DrawIndexedImpl(uint32_t nums, ERendererPrimitive primitive, uint32_t offset) {
		glDrawElements(OpenGLFactory::ToOpenGLPrimitive(primitive), nums, GL_UNSIGNED_INT, (void*)offset);
	}

	void OpenGLRenderCommand::SetAlphaStateImpl(bool enable, ERendererBlendFunction source, ERendererBlendFunction destination, ERendererBlendEquation blendEquation) {
		if (enable == false && mRenderData.IsEnable == false) {
			return;
		}

		if (enable == false && mRenderData.IsEnable == true) {
			glDisable(GL_BLEND);
			mRenderData.IsEnable = false;
			return;
		}

		if (enable == true && mRenderData.IsEnable == false) {
			glEnable(GL_BLEND);
			mRenderData.IsEnable = true;
		}

		if (mRenderData.EnableRendererState != ERendererState::Blending) {
			glEnable(OpenGLFactory::ToOpenGLState(ERendererState::Blending));
			mRenderData.EnableRendererState = ERendererState::Blending;
		}

		if (mRenderData.BlendEquation != blendEquation) {
			glBlendEquation(OpenGLFactory::ToOpenGLBlendEquation(blendEquation));
			mRenderData.BlendEquation = blendEquation;
		}

		if (mRenderData.BlendSource != source || mRenderData.BlendDestination != destination) {
			glBlendFunc(OpenGLFactory::ToOpenGLBlendFunction(source), OpenGLFactory::ToOpenGLBlendFunction(destination));
			mRenderData.BlendSource = source;
			mRenderData.BlendDestination = destination;
		}
	}
}