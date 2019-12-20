#pragma once
#ifndef _FvReferences_Info_Header
#define _FvReferences_Info_Header

#include <FvPrimitives_Vec2.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvReferences_Info
		{

		public:

			static Vec2 Gravity();

			static Scalar Pressure();
		};
	}
}

#endif // !_FvReferences_Info_Header
