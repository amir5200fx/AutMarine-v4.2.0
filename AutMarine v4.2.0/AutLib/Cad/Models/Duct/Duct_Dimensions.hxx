#pragma once
#ifndef _Duct_Dimensions_Header
#define _Duct_Dimensions_Header

#include <Standard_TypeDef.hxx>
#include <Standard_OStream.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Duct_Dimensions
		{

		private:

			Standard_Real theHeightAtOutlet_;

			Standard_Real theOveralLength_;
			Standard_Real theBreadthAtInlet_;
			Standard_Real theBreadthAtOutlet_;
			Standard_Real theDepthAtInlet_;
			Standard_Real theDepthAtOutlet_;

			Standard_Integer theNbSections_;

		public:

			Duct_Dimensions();

			Standard_Integer NbSections() const;

			Standard_Real OveralLength() const;

			Standard_Real BreadthAtInlet() const;

			Standard_Real BreadthAtOutlet() const;

			Standard_Real DepthAtInlet() const;

			Standard_Real DepthAtOutlet() const;

			Standard_Real HeightAtOutlet() const;

			void SetNbSections(const Standard_Integer theNbSections);

			void SetOveralLength(const Standard_Real theOveralLength);

			void SetBreadthAtInlet(const Standard_Real theBeamAtInlet);

			void SetBreadthAtOutlet(const Standard_Real theBeamAtOutlet);

			void SetDepthAtInlet(const Standard_Real theDepthAtInlet);

			void SetDepthAtOutlet(const Standard_Real theDepthAtOutlet);

			void SetHeightAtOutlet(const Standard_Real theHeightAtOutlet);
		};
	}
}

#include <Duct_DimensionsI.hxx>

#endif // !_Duct_Dimensions_Header
