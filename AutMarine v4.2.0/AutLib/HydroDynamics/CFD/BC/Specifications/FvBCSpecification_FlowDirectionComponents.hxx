#pragma once
#ifndef _FvBCSpecification_FlowDirectionComponents_Header
#define _FvBCSpecification_FlowDirectionComponents_Header

#include <FvBCSpecification_FlowDirection.hxx>
#include <FvField2d_Vector.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvBCSpecification_FlowDirectionComponents : public FvBCSpecification_FlowDirection
		{

		private:

			const FvField2d_Vector& theField_;

		public:

			FvBCSpecification_FlowDirectionComponents(const FvField2d_Vector& theField);

			virtual ~FvBCSpecification_FlowDirectionComponents();

			Vec2 Direction(const Geom_Pnt2d& theCoord) const;
		};
	}
}

#include <FvBCSpecification_FlowDirectionComponentsI.hxx>

#endif // !_FvBCSpecification_FlowDirectionComponents_Header
