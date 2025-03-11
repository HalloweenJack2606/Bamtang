#pragma once
#include "Core/CoreMinimal.h"

namespace Ludens
{
	using MouseCode = uint16;

	namespace Mouse
	{
		enum : MouseCode
		{
			//@note: from glfw3.h
			Button0 = 0,
			Button1 = 1,
			Button2 = 2,
			Button3 = 3,
			Button4 = 4,
			Button5 = 5,
			Button6 = 6,
			Button7 = 7,

			ButtonLeft = Button0,
			ButtonRight = Button1,
			ButtonMiddle = Button2
		};
	}
}