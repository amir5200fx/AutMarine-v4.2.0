#pragma once
#ifndef _FvVelocity2d_Header
#define _FvVelocity2d_Header

#include <FvNavierStokes.hxx>
#include <FvSources2d_List.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvSources2d_Methods;

		class FvVelocity2d : public FvNavierStokes
		{

		private:

			FvSources2d_List theSources_;

		public:

			FvVelocity2d(const FvMesh2d& theMesh, const FvParameters& theParameters, const FvBC& theBoundaryCondition, const FvVariables2d& theVariables, const FvMaterial& theMaterial, const FvSources2d_Methods& theMethods);


		};
	}
}

#endif // !_FvVelocity2d_Header
