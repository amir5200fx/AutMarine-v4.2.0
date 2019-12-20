#pragma once
#ifndef _FvField2d_Const_Header
#define _FvField2d_Const_Header

#include <FvField2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		template<typename T>
		class FvField2d_Const : public FvField2d<T>
		{

		private:

			T theValue_;

		public:

			FvField2d_Const(const T& theValue);

			virtual T Value(const Geom_Pnt2d& theCoord) const;
		};
	}
}

#include <FvField2d_ConstI.hxx>

#endif // !_FvField_Const_Header
