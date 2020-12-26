#pragma once
#include "bgspch.h"

#include "Engine/Core/Core.h"
#include "Engine/Events/Event.h"

#include <map>

namespace BIGOS {

	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "Test window" , 
					uint32_t width = 1600, 
					uint32_t height = 900)
			: Title(title), Width(width), Height(height)
		{

		}
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		
		virtual bool Init() = 0;
		virtual void ShutDown() = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		static Window* StartUpWindow(const WindowProps& props);

		static void RegisterWindowClass(void* handle, Window* window);
		static Window* GetWindowClass(void* handle);

		struct WindowData {
			std::string Title;
			uint32_t Width, Height;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	private:
		static std::map<void*, Window*> s_Handles;
	};

}