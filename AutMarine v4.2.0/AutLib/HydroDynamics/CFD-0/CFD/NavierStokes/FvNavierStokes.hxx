#pragma once
#ifndef _FvNavierStokes_Header
#define _FvNavierStokes_Header

namespace AutLib
{
	namespace FvLib
	{

		class FvMesh2d;
		class FvParameters;
		class FvBC;
		class FvVariables2d;
		class FvMaterial;

		class FvNavierStokes
		{

		private:

			const FvMesh2d& theMesh_;

			const FvParameters& theParameters_;

			const FvBC& theBoundaryCondition_;

			const FvVariables2d& theVariables_;

			const FvMaterial& theMaterial_;

		protected:

			FvNavierStokes(const FvMesh2d& theMesh, const FvParameters& theParameters, const FvBC& theBoundaryCondition, const FvVariables2d& theVariables, const FvMaterial& theMaterial);

		public:

			virtual ~FvNavierStokes();

			const FvMesh2d& Mesh() const;

			const FvParameters& Parameters() const;

			const FvBC& BoundaryCondition() const;

			const FvVariables2d& Variables() const;
		};
	}
}

#include <FvNavierStokesI.hxx>

#endif // !_FvNavierStokes_Header
