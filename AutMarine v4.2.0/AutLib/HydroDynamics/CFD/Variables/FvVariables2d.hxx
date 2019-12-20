#pragma once
#ifndef _FvVariables2d_Header
#define _FvVariables2d_Header

#include <FvVariables_Primitives2d.hxx>
#include <FvVariables_Sources2d.hxx>
#include <FvVariables_FluxVelocity.hxx>
#include <FvVariables_Assembly.hxx>
#include <FvMemory2d.hxx>

namespace AutLib
{
	namespace FvLib
	{
		
		class FvVariables2d
		{

		private:

			FvVariables_Primitives2d theCellVariables0_;
			FvVariables_Primitives2d theCellVariables_;
			FvVariables_Primitives2d theFaceVariables_;

			FvVariables_Sources2d theSources_;
			FvVariables_Sources2d theCorrectionSources_;

			FvVariables_FluxVelocity theFluxVelocity_;

			FvVariables_Assembly theAssembly_;

		public:

			FvVariables2d(FvMemory2d& theMemory);

			const FvVariables_Primitives2d& CellVariables0() const;

			const FvVariables_Primitives2d& CellVariables() const;

			const FvVariables_Primitives2d& FaceVariables() const;

			const FvVariables_Sources2d& Sources() const;

			const FvVariables_FluxVelocity& FluxVelocity() const;

			const FvVariables_Assembly& Assembly() const;

			FvVariables_Primitives2d& CellVariables0();

			FvVariables_Primitives2d& CellVariables();

			FvVariables_Primitives2d& FaceVariables();

			FvVariables_Sources2d& Sources();

			FvVariables_FluxVelocity& FluxVelocity();

			FvVariables_Assembly& Assembly();
		};
	}
}

#include <FvVariables2dI.hxx>

#endif // !_FvVariables_Header
