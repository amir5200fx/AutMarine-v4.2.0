#pragma once
#ifndef _FvSolverConfig_Header
#define _FvSolverConfig_Header

#include <FvPrimitives_Label.hxx>
#include <FvPrimitives_Scalar.hxx>

namespace AutLib
{
	namespace FvLib
	{
		
		class FvSolverConfig
		{

		private:

			Scalar theTime_;

			Label theMaxIters_;
			Label theIters_;

			Scalar theMaxRes_;
			Scalar theRes_;

		public:

			virtual ~FvSolverConfig();

			void SetTime(const Scalar theTime);

			void SetMaxIterations(const Label theMaxIters);

			void SetNbIterations(const Label theNbIterations);

			void SetMaxResidual(const Scalar theValue);

			void SetResidual(const Scalar theValue);

			Scalar Time() const;

			Label MaxIterations() const;

			Label NbIterations() const;

			Scalar MaxResidual() const;

			Scalar Residual() const;

		protected:

			FvSolverConfig(const Label theMaxIters, const Scalar theMaxRes);
		};
	}
}

#include <FvSolverConfigI.hxx>

#endif // !_FvSolverConfig_Header
