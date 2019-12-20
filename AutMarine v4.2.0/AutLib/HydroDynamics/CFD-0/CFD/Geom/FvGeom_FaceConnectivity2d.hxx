#pragma once
#ifndef _FvGeom_FaceConnectivity2d_Header
#define _FvGeom_FaceConnectivity2d_Header

#include <Standard_TypeDef.hxx>
#include <Standard_Stream.hxx>
#include <Standard_IStream.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvGeom_FaceConnectivity2d
		{

		private:

			Standard_Integer theV0_;
			Standard_Integer theV1_;

		public:

			FvGeom_FaceConnectivity2d();

			Standard_Integer Value(const Standard_Integer theIndex) const;

			void Import(fstream& File);
		};
	}
}

#include <FvGeom_FaceConnectivity2dI.hxx>

#endif // !_FvGeom_FaceConnectivity2d_Header
