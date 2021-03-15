#include "bgspch.h"
#include "Engine/Renderer/API/Framebuffer.h"
#include "Engine/Renderer/API/RendererAPI.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Core/Core.h"

#include "Platform/DirectX/Direct3DFramebuffer.h"

namespace BIGOS {

	std::shared_ptr<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:		BGS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");	return nullptr;
		case RendererAPI::API::OPENGL:		BGS_CORE_ASSERT(false, "RendererAPI::OPENGL is currently not supported!");	return nullptr;
		case RendererAPI::API::DIRECT3D:	return std::make_shared<Direct3DFramebuffer>(spec);
		case RendererAPI::API::VULKAN:		BGS_CORE_ASSERT(false, "RendererAPI::VULKAN is currently not supported!");	return nullptr;
		}

		BGS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}