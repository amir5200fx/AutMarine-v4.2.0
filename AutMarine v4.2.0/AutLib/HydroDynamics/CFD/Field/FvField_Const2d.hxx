#pragma once
#ifndef _FvField_Const2d_Header
#define _FvField_Const2d_Header

#include <FvField2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		template <typename Type_>
		class FvField_Const2d : public FvField2d<Type_>
		{

		private:

			Type_ theValue_;

		public:

			FvField_Const2d(const Type_& theValue);

			const Type_& Value(const Geom_Pnt2d& theCoord) const;
		};
	}
}

#include <FvField_Const2dI.hxx>

#endif // !_FvField_Const2d_Header
