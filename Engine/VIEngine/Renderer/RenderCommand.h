#pragma once

#include"pch.h"

namespace VIEngine {
	using RenderCommandCallback = std::function<void()>;

	class RenderCommand {
	public:
		RenderCommand() = default;
		RenderCommand(const RenderCommand&) = default;
		RenderCommand(const RenderCommandCallback& command) : mCommand(command) {}

		void Execute() { mCommand(); }

	private:
		RenderCommandCallback mCommand;
	};
}