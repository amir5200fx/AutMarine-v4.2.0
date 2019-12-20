#pragma once
#ifndef _FvDiscrete2d_Header
#define _FvDiscrete2d_Header

namespace AutLib
{
	namespace FvLib
	{

		class FvMatrix;
		class FvVector;
		class FvMesh2d;
		class FvVectorField;

		class FvDiscrete2d
		{

		private:

			FvMatrix& theAssembly_;

			FvVectorField& theSources_;
			FvVectorField& theX_;

			const FvMesh2d& theMesh_;

		public:

			virtual ~FvDiscrete2d();

			const FvMatrix& Assembly() const;

			const FvMesh2d& Mesh() const;

			const FvVectorField& Source() const;

			const FvVectorField& X() const;

			FvMatrix& Assembly();

			FvVectorField& Source();

			FvVectorField& X();

		protected:

			FvDiscrete2d(FvMatrix& theAssembly, FvVectorField& theSources, FvVectorField& theX, const FvMesh2d& theMesh);
			
		};
	}
}

#include <FvDiscrete2dI.hxx>

#endif // !_FvDiscrete2d_Header
