#pragma once
#ifndef _FvDiscreteLaplacian_Basic2d_Header
#define _FvDiscreteLaplacian_Basic2d_Header

#include <FvDiscreteLaplacian2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvMaterial_Viscosity;

		class FvDiscreteLaplacian_Basic2d : public FvDiscreteLaplacian2d
		{

		private:

			const FvVectorField& thePatches_;

		public:

			FvDiscreteLaplacian_Basic2d(FvMatrix& theAssembly, FvVectorField& theSources, FvVectorField& theX, const FvMesh2d& theMesh, const FvVectorField& thePatches);

			virtual ~FvDiscreteLaplacian_Basic2d();

			void Assemble(const FvMaterial_Viscosity& theViscosity, const FvVectorField& theVector0);
		};
	}
}

#endif // !_FvDiscreteLaplacian_Basic2d_Header
