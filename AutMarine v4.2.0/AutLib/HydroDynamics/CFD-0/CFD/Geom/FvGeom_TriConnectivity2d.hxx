#pragma once
#ifndef _FvGeom_TriConnectivity2d_Header
#define _FvGeom_TriConnectivity2d_Header

#include <FvGeom_ElementConnectivity2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvGeom_TriConnectivity2d : public FvGeom_ElementConnectivity2d
		{

		private:

			Standard_Integer theV0_;
			Standard_Integer theV1_;
			Standard_Integer theV2_;

		public:

			FvGeom_TriConnectivity2d();

			virtual Standard_Integer Size() const;

			virtual Standard_Integer Value(const Standard_Integer theIndex) const;

			virtual void Import(fstream& File);
		};
	}
}

#include <FvGeom_TriConnectivity2dI.hxx>

#endif // !_FvGeom_TriConnectivity2d_Header
