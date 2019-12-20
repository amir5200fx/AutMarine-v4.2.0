#pragma once
#ifndef _FvBC_Boundary_Header
#define _FvBC_Boundary_Header

#include <FvBC_Physics.hxx>
#include <FvBC_Type.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvBC_Boundary
		{

		private:

			FvBC_Physics thePhysics_;

			FvBC_Type theType_;

		public:

			virtual ~FvBC_Boundary();

			void SetPhysics(const FvBC_Physics thePhysics);

			FvBC_Physics Physics() const;

			FvBC_Type Type() const;

		protected:

			FvBC_Boundary(const FvBC_Type theType);
		};
	}
}

#include <FvBC_BoundaryI.hxx>

#endif // !_FvBC_Boundary_Header
