#pragma once
#ifndef _Numeric_AdptIntegral_Header
#define _Numeric_AdptIntegral_Header

#include <Standard_Integer.hxx>
#include <Standard_Real.hxx>
#include <Global_Debug.hxx>
#include <TColStd_Ary1dOfReal.hxx>
#include <TColStd_Ary1dOfInteger.hxx>

namespace AutLib
{
	namespace NumLib
	{

		template<typename T>
		class Numeric_AdptIntegral
		{

		private:

			const T* theObject_;

			Standard_Real(*theIntegrand_)(const Standard_Real, const T&);

			Standard_Boolean IsDone_;
			Standard_Boolean IsConverged_;

			Standard_Real theLower_;
			Standard_Real theUpper_;

			Standard_Real theTolerance_;
			Standard_Real theResult_;

			Standard_Integer theMaxIters_;
			Standard_Integer theInitialIter_;

		public:

			Numeric_AdptIntegral(const T* Object);

			Numeric_AdptIntegral(const T* Object, Standard_Real(*Integrand)(const Standard_Real, const T&));

			Numeric_AdptIntegral(const T* Object, Standard_Real(*Integrand)(const Standard_Real, const T&), const Standard_Real Lower, const Standard_Real Upper);

			Numeric_AdptIntegral(const T* Object, Standard_Real(*Integrand)(const Standard_Real, const T&), const Standard_Real Lower, const Standard_Real Upper, const Standard_Real Tolerance);

			void Perform();

			void SetIntegrand(Standard_Real(*Integrand)(const Standard_Real Parameter, const T& Object));

			void SetLower(const Standard_Real Value);

			void SetUpper(const Standard_Real Value);

			void SetTolerance(const Standard_Real Value);

			void SetMaxIteration(const Standard_Integer Iters);

			void SetInitIter(const Standard_Integer Value);

			Standard_Boolean IsDone() const;

			Standard_Boolean IsConverged() const;

			Standard_Real Result() const;

			Standard_Integer MaxNbIterations() const;
		};
	}
}

#include <Numeric_AdptIntegralI.hxx>

#endif // !_Numeric_AdptIntegral_header
