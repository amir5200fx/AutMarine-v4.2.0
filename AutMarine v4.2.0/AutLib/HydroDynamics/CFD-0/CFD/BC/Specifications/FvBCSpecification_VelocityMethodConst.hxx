#pragma once
#ifndef _FvBCSpecification_VelocityMethodConst_Header
#define _FvBCSpecification_VelocityMethodConst_Header

#include <Geom_Pnt2d.hxx>
#include <FvBCSpecification_Velocity.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvBCSpecification_VelocityMethodConst : public FvBCSpecification_Velocity
		{

		private:

			Geom_Pnt2d theField_;

		public:

			FvBCSpecification_VelocityMethodConst(const Geom_Pnt2d& theField);

			Geom_Pnt2d Value(const Geom_Pnt2d& theCoord) const;
		};
	}
}

#include <FvBCSpecification_VelocityMethodConstI.hxx>

#endif // !_FvBCSpecification_VelocityMethodConst_Header
