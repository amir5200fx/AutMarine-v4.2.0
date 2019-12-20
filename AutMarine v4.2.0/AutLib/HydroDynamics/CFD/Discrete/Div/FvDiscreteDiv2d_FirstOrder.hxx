#pragma once
#ifndef _FvDiscreteDiv2d_FirstOrder_Header
#define _FvDiscreteDiv2d_FirstOrder_Header

#include <FvDiscreteDiv2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvDiscreteDiv2d_FirstOrder : public FvDiscreteDiv2d
		{

		private:

			const FvVectorField& thePatches_;

		public:

			FvDiscreteDiv2d_FirstOrder(FvMatrix& theAssembly, FvVectorField& theSources, FvVectorField& theX, const FvMesh2d& theMesh, const FvVectorField& thePathces);

			virtual ~FvDiscreteDiv2d_FirstOrder();

			void Assemble(const FvVector& thePhi, const FvVectorField& theVector0);
		};
	}
}

#endif // !_FvDiscreteDiv2d_FirstOrder_Header
