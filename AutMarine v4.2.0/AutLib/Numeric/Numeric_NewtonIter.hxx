#pragma once
#ifndef _Numeric_NewtonIter_Header
#define _Numeric_NewtonIter_Header

#include <Standard_Integer.hxx>
#include <Standard_Real.hxx>
#include <Global_Debug.hxx>

namespace AutLib
{
	namespace NumLib
	{

		enum NewtonIterCondition
		{
			NewtonIter_LEVEL_EXCEEDED,
			NewtonIter_ZERODIVIDE,
			NewtonIter_CONVERGED
		};

		template<typename T>
		class Numeric_NewtonIter
		{

		private:

			const T* theObject_;

			Standard_Real(*theValueFunction_)(const Standard_Real, const T&);
			Standard_Real(*theDeriveFunction_)(const Standard_Real, const T&);

			NewtonIterCondition theCondition_;

			Standard_Integer theMaxIterations_;
			Standard_Integer theIter_;

			Standard_Real theTolerance_;
			Standard_Real theUnderRelaxation_;

			Standard_Real theResidual_;
			Standard_Real theResult_;
			Standard_Real theSmall_;
			Standard_Real theZero_;

			Standard_Boolean IsDone_;

		public:

			Numeric_NewtonIter(const T* Object, const Standard_Real Tolerance);

			Numeric_NewtonIter(const T* Object, Standard_Real(*Function)(const Standard_Real, const T&), Standard_Real(*Derive)(const Standard_Real, const T&), const Standard_Real Tolerance);

			void SetIterations(const Standard_Integer nbIterations);

			void SetTolerance(const Standard_Real Tolerance);

			void SetSmall(const Standard_Real Small);

			void SetUnderRelaxation(const Standard_Real UnderRelaxation);

			void SetZero(const Standard_Real Zero);

			void Iterate(const Standard_Real guess);

			NewtonIterCondition Condition() const;

			Standard_Real Result() const;

			Standard_Real Residual() const;

			Standard_Integer NbIterated() const;

			Standard_Boolean IsDone() const;
		};
	}
}

#include <Numeric_NewtonIterI.hxx>

#endif // !_Numeric_NewtonIter_Header
