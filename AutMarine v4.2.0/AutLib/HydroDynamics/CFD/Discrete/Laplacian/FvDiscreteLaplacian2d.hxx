#pragma once
#ifndef _FvDiscreteLaplacian2d_Header
#define _FvDiscreteLaplacian2d_Header

#include <FvDiscrete2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvDiscreteLaplacian2d : public FvDiscrete2d
		{

		private:


		protected:

			virtual ~FvDiscreteLaplacian2d();

		public:

			FvDiscreteLaplacian2d(FvMatrix& theAssembly, FvVectorField& theSources, FvVectorField& theX, const FvMesh2d& theMesh);
		};
	}
}

#endif // !_FvDiscreteLaplacian2d_Header
