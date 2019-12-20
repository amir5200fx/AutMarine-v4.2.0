#pragma once
#ifndef _FvReferences_Gravity_Header
#define _FvReferences_Gravity_Header

#include <Geom_Pnt2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvReferences_Gravity
		{

		private:

			Geom_Pnt2d theValue_;

		public:

			FvReferences_Gravity();

			void SetValue(const Geom_Pnt2d& theValue);

			const Geom_Pnt2d& Value() const;
		};
	}
}

#include <FvReferences_GravityI.hxx>

#endif // !_FvReferences_Gravity_Header
