#pragma once
#ifndef _FvField2d_Vector_Header
#define _FvField2d_Vector_Header

#include <Geom_Pnt2d.hxx>
#include <FvField2d_Variable.hxx>

namespace AutLib
{
	namespace FvLib
	{
		class FvField2d_Vector : public FvField2d_Variable
		{

		private:

			Geom_Pnt2d theValue_;

		public:

			FvField2d_Vector();

			FvField2d_Vector(const Geom_Pnt2d& theValue);

			virtual ~FvField2d_Vector();

			void SetValue(const Geom_Pnt2d& theValue);

			const Geom_Pnt2d& Value() const;
		};
	}
}

#include <FvField2d_VectorI.hxx>

#endif // !_FvField2d_Vector_Header
