#pragma once
#ifndef _FvGeom_Element2d_Header
#define _FvGeom_Element2d_Header

#include <Global_Memory.hxx>
#include <Standard_Stream.hxx>
#include <FvBC_Physics.hxx>
#include <FvGeom_ElementType.hxx>
#include <FvPrimitives_Label.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvConnectivities;

		class FvGeom_Element2d
		{

		private:

			Label theIndex_;

			FvBC_Physics thePhysics_;

			FvGeom_ElementType theType_;

			Global_Handle(FvConnectivities) theConnectivity_;

		public:

			FvGeom_Element2d();

			~FvGeom_Element2d();

			Label Index() const;

			FvBC_Physics Physics() const;

			FvGeom_ElementType Type() const;

			const Global_Handle(FvConnectivities) Connectivity() const;

			void Import(fstream& File);
		};
	}
}

#include <FvGeom_Element2dI.hxx>

#endif // !_FvGeom_Element2d_Header
