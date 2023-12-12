#pragma once

namespace SimpleRender
{
	class RenderApplication;
}

namespace SimpleRenderPure
{
	/// <summary>
	/// Interface to receive contiguous key input
	/// Pass a reference to an application.
	/// 
	/// Automatically registers for input when created.
	/// </summary>
	class ContiguousKeyInput
	{
	public:
		ContiguousKeyInput(SimpleRender::RenderApplication* application);
		virtual ~ContiguousKeyInput();

		void RegisterContiguousKeyInput();
		void UnregisterContiguousKeyInput();

		virtual void OnContiguousKeyInput() = 0;
		


	private:
		SimpleRender::RenderApplication* application;
	};


}