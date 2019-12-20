#pragma once
#ifndef _FvGeom_Face2d_Header
#define _FvGeom_Face2d_Header

#include <FvGeom_FaceConnectivity2d.hxx>
#include <FvBC_Physics.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvGeom_Face2d
		{

		private:

			Standard_Integer theIndex_;

			FvGeom_FaceConnectivity2d theConnectivity_;

			FvBC_Physics thePhysics_;

		public:

			FvGeom_Face2d();

			Standard_Integer Index() const;

			FvBC_Physics Physics() const;

			const FvGeom_FaceConnectivity2d& Connectivity() const;

			void Import(fstream& File);
		};
	}
}

#include <FvGeom_Face2dI.hxx>

#endif // !_FvGeom_Face2d_Header
