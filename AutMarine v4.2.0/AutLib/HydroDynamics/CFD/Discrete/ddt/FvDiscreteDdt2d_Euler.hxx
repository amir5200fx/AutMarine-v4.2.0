#pragma once
#ifndef _FvDiscreteDdt2d_Euler_Header
#define _FvDiscreteDdt2d_Euler_Header

#include <FvDiscreteDdt2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvMaterial_Density;
		class FvParameters_TimeConfig;

		class FvDiscreteDdt2d_Euler : public FvDiscreteDdt2d
		{

		private:

			const FvParameters_TimeConfig& theTimeConfig_;

		public:

			FvDiscreteDdt2d_Euler(FvMatrix& theAssembly, FvVectorField& theSources, FvVectorField& theX, const FvMesh2d& theMesh, const FvParameters_TimeConfig& theTimeConfig);

			const FvParameters_TimeConfig& TimeConfig() const;

			void Assemble(const FvMaterial_Density& theDensity, const FvVectorField& theVector0);
		};
	}
}

#include <FvDiscreteDdt2d_EulerI.hxx>

#endif // !_FvDiscreteDdt2d_Euler_Header
