#pragma once
#include "axpch.h"
#include "Core.h"
#include "Events/Event.h"
#include "Renderer/GraphicsContext.h"
#include "GLFW/glfw3.h"

namespace Apex {

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Apex Engine", unsigned int width = 800, unsigned int height = 600)
			: Title(title), Width(width), Height(height) {}
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		~Window();

		void Init(const WindowProps& props);
		void Shutdown();

		void OnUpdate();

		inline unsigned int GetWidth() const { return m_Data.Width; }
		inline unsigned int GetHeight() const { return m_Data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }
		inline void* GetNativeWindow() const { return m_Window; }
		void SetVSync(bool enabled);
		bool IsVSync() const;

		static Window* Create(const WindowProps& props = WindowProps());

	private:
		Window(const WindowProps& props);

		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

};