#pragma once
#ifndef _FvDiscreteDiv2d_Header
#define _FvDiscreteDiv2d_Header

#include <FvDiscrete2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvDiscreteDiv2d : public FvDiscrete2d
		{

		private:


		public:

			virtual ~FvDiscreteDiv2d();

		protected:

			FvDiscreteDiv2d(FvMatrix& theAssembly, FvVectorField& theSources, FvVectorField& theX, const FvMesh2d& theMesh);

		};
	}
}

#endif // !_FvDiscreteDiv2d_Header
