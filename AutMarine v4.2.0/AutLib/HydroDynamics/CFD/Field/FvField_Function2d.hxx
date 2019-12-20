#pragma once
#ifndef _FvField_Function2d_Header
#define _FvField_Function2d_Header

#include <FvField2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		template<typename Type_>
		class FvField_Function2d : public FvField2d<Type_>
		{

		private:

			Type_(*theValueFunction_)(const Geom_Pnt2d& theCoord);

		public:

			FvField_Function2d(Type_(*theValueFunction)(const Geom_Pnt2d& theCoord));

			Type_ Value(const Geom_Pnt2d& theCoord) const;
		};
	}
}

#include <FvField_Function2dI.hxx>

#endif // !_FvField_Function2d_Header
