#pragma once
#ifndef _FvBCSpecification_VelocityMethodComposite_Header
#define _FvBCSpecification_VelocityMethodComposite_Header

#include <Standard_TypeDef.hxx>
#include <FvBCSpecification_VelocityMethod.hxx>
#include <FvField2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvBCSpecification_VelocityMethodComposite : public FvBCSpecification_VelocityMethod
		{

		private:

			const FvField2d<Standard_Real>& theXComponent_;
			const FvField2d<Standard_Real>& theYComponent_;

		public:

			FvBCSpecification_VelocityMethodComposite(const FvField2d<Standard_Real>& theXComponent, const FvField2d<Standard_Real>& theYComponent);

			Standard_Real xValue(const Geom_Pnt2d& theCoord) const;

			Standard_Real yValue(const Geom_Pnt2d& theCoord) const;

			virtual Geom_Pnt2d Value(const Geom_Pnt2d& theCoord) const;
		};
	}
}

#include <FvBCSpecification_VelocityMethodCompositeI.hxx>

#endif // !_FvBCSpecification_VelocityMethodComposite_Header
