#pragma once

namespace SimpleRenderPure
{
	class Disposable
	{
	public:
		Disposable() {};
		~Disposable() {};

		virtual void Dispose() = 0;

	};

}