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

	void OpenGLRenderCommand::EnableBlendingImpl(ERendererBlendFunction source, ERendererBlendFunction destination, ERendererBlendEquation blendEquation) {
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

	void OpenGLRenderCommand::DisableBlendingImpl() {
		if (mRenderData.DisableRendererState == ERendererState::Blending) return;

		glDisable(OpenGLFactory::ToOpenGLState(ERendererState::Blending));
		mRenderData.DisableRendererState = ERendererState::Blending;
	}
}