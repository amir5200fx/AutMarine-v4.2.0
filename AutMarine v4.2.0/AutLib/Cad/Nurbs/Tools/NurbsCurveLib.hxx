#pragma once
#ifndef _NurbsCurveLib_Header
#define _NurbsCurveLib_Header

#include <TColStd_Ary1dOfReal.hxx>
#include <TColStd_Ary2dOfReal.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class NurbsCurveLib
		{

		public:

			static Standard_Integer Bin(const Standard_Integer K, const Standard_Integer I);

			static Standard_Integer FindSpan(const Standard_Real U, const Standard_Integer Degree, const Standard_Integer MaxIndex, const TColStd_Ary1dOfReal& Knots);

			static Standard_Real BasisFun(const Standard_Integer Span, const Standard_Real Parameter, const Standard_Integer Degree, const TColStd_Ary1dOfReal& Knots);

			static void BasisFuns(const Standard_Integer Span, const Standard_Real Parameter, const Standard_Integer Degree, const TColStd_Ary1dOfReal& Knots, TColStd_Ary1dOfReal& Basis);

			static void DersBasisFuns(const Standard_Integer Span, const Standard_Real Parameter, const Standard_Integer Degree, const Standard_Integer Nth, const TColStd_Ary1dOfReal& Knots, TColStd_Ary2dOfReal& Ders);

			static void FormU(const Standard_Integer Degree, const Standard_Integer MaxIndex, const TColStd_Ary1dOfReal& Parameters, TColStd_Ary1dOfReal& Knots);
		};
	}
}

#endif // !_NurbsCurveLib_Header
