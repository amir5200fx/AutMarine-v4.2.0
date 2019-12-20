#pragma once
#ifndef _FvVariables_Assembly_Header
#define _FvVariables_Assembly_Header

#include <Global_Macros.hxx>
#include <FvMatrix.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvVariables_Assembly
		{

		private:

			FvMatrix& theAc_;
			FvMatrix& theAm_;

		public:

			FvVariables_Assembly(FvMatrix& theContinuity, FvMatrix& theMomentum);

			const FvMatrix& Continuity() const;

			const FvMatrix& Momentum() const;

			FvMatrix& Continuity();

			FvMatrix& Momentum();
		};
	}
}

#include <FvVariables_AssemblyI.hxx>

#endif // !_FvVariables_Assembly_Header
