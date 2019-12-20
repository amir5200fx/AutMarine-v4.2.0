#pragma once
#ifndef _FvGeom_Face2d_Header
#define _FvGeom_Face2d_Header

#include <FvConnectivities_Dual.hxx>
#include <FvBC_Physics.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvGeom_Face2d
		{

		private:

			Label theIndex_;

			FvConnectivities_Dual theConnectivity_;

			FvBC_Physics thephysics_;

		public:

			FvGeom_Face2d();

			Label Index() const;

			FvBC_Physics Physics() const;

			const FvConnectivities_Dual& Connectivity() const;

			void Import(fstream& File);
		};
	}
}

#include <FvGeom_Face2dI.hxx>

#endif // !_FvGeom_Face2d_Header
