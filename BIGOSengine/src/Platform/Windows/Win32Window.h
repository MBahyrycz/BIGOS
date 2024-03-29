#pragma once

#include "Engine/Core/App/Window.h"
#include "Engine/Renderer/API/GraphicsContext.h"

namespace BIGOS {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow() = default;
		WindowsWindow(const WindowProps& props);
		~WindowsWindow();
		
		virtual bool Init() override;
		virtual void ShutDown() override;

		virtual void OnUpdate() override;

		virtual uint32_t GetWidth() const override { return m_Data.Width; };
		virtual uint32_t GetHeight() const override { return m_Data.Height; };

		virtual void SetVsync(bool enabled) override;
		virtual bool IsVSync() const override { return m_Data.Vsync; }

		virtual void SetTitle(const std::string& title) override;
		virtual const std::string& GetTitle() override { return m_Data.Title; }

		virtual void SetEventCallback(const EventCallbackFn& callback) override;

		virtual void* GetNativeWindowHandle() const override { return m_hWnd; }
		virtual void* GetNativeWindowInstance() const override { return m_hInstance; }

		friend class RendererAPI;
	private:
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	private:
		HWND m_hWnd;
		HINSTANCE m_hInstance;
		HDC m_hDc;
	};

	//void FocusCallback(Window* window, bool focused);
}