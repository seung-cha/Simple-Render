#pragma once

namespace SimpleRenderPure
{
	class Disposable
	{
	public:
		Disposable() {};
		virtual ~Disposable() {};

		virtual void Dispose() = 0;

	};

}