#pragma once
#ifndef _FvDiscreteDdt2d_Header
#define _FvDiscreteDdt2d_Header

#include <FvDiscrete2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvDiscreteDdt2d : public FvDiscrete2d
		{

		private:

		public:

			virtual ~FvDiscreteDdt2d();

		protected:

			FvDiscreteDdt2d(FvMatrix& theAssembly, FvVectorField& theSources, FvVectorField& theX, const FvMesh2d& theMesh);
		};
	}
}

#endif // !_FvDiscreteDdt2d_Header

