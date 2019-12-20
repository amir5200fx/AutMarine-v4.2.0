#pragma once
#ifndef _FvReferences_Gravity_Header
#define _FvReferences_Gravity_Header

#include <FvPrimitives_Vec2.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvReferences_Gravity
		{

		private:

			Vec2 theValue_;

		public:

			FvReferences_Gravity();

			void SetValue(const Vec2& theValue);

			const Vec2& Value() const;
		};
	}
}

#include <FvReferences_GravityI.hxx>

#endif // !_FvReferences_Gravity_Header
