#pragma once
#ifndef _FvBCSpecification_VelocityMethodComposite_Header
#define _FvBCSpecification_VelocityMethodComposite_Header

#include <FvBCSpecification_VelocityMethod.hxx>
#include <FvField2d_Scalar.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvBCSpecification_VelocityMethodComposite : public FvBCSpecification_VelocityMethod
		{

		private:

			const FvField2d_Scalar& theXComponent_;
			const FvField2d_Scalar& theYComponent_;

		public:

			FvBCSpecification_VelocityMethodComposite(const FvField2d_Scalar& theXComponent, const FvField2d_Scalar& theYComponent);

			Standard_Real xValue(const Geom_Pnt2d& theCoord) const;

			Standard_Real yValue(const Geom_Pnt2d& theCoord) const;

			virtual Vec2 Value(const Geom_Pnt2d& theCoord) const;
		};
	}
}

#include <FvBCSpecification_VelocityMethodCompositeI.hxx>

#endif // !_FvBCSpecification_VelocityMethodComposite_Header
