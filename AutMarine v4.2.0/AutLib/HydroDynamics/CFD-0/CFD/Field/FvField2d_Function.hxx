#pragma once
#ifndef _FvField_Function_Header
#define _FvField_Function_Header

#include <FvField2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		template<typename T>
		class FvField2d_Function : public FvField2d<T>
		{

		private:

			T(*theValueFunction_)(const Geom_Pnt2d& theCoord);

		public:

			FvField2d_Function(T(*theValueFunction)(const Geom_Pnt2d&));

			virtual T Value(const Geom_Pnt2d& theCoord) const;
		};
	}
}

#include <FvField2d_FunctionI.hxx>

#endif // !_FvField_Function_Header
