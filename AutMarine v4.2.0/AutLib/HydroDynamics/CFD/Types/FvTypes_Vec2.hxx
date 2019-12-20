#pragma once
#ifndef _FvTypes_Vec2_Header
#define _FvTypes_Vec2_Header

#include <FvTypes.hxx>
#include <FvPrimitives_Vec2.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvTypes_Vec2 : public FvTypes
		{

		private:

			Vec2 theValue_;

		public:

			FvTypes_Vec2();

			FvTypes_Vec2(const Vec2& theValue);

			virtual ~FvTypes_Vec2();

			void SetValue(const Vec2& theValue);

			const Vec2& Value() const;
		};
	}
}

#include <FvTypes_Vec2I.hxx>

#endif // !_FvTypes_Vec2_Header
