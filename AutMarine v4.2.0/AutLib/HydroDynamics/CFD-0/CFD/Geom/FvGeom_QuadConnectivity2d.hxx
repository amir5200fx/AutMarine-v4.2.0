#pragma once
#ifndef _FvGeom_QuadConnectivity2d_Header
#define _FvGeom_QuadConnectivity2d_Header

#include <FvGeom_ElementConnectivity2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvGeom_QuadConnectivity2d : public FvGeom_ElementConnectivity2d
		{

		private:

			Standard_Integer theV0_;
			Standard_Integer theV1_;
			Standard_Integer theV2_;
			Standard_Integer theV3_;

		public:

			FvGeom_QuadConnectivity2d();

			virtual Standard_Integer Size() const;

			virtual Standard_Integer Value(const Standard_Integer theIndex) const;

			virtual void Import(fstream& File);
		};
	}
}

#include <FvGeom_QuadConnectivity2dI.hxx>

#endif // !_FvGeom_QuadConnectivity_Header
