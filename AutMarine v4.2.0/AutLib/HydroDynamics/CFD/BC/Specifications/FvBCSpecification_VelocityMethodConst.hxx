#pragma once
#ifndef _FvBCSpecification_VelocityMethodConst_Header
#define _FvBCSpecification_VelocityMethodConst_Header

#include <Geom_Pnt2d.hxx>
#include <FvBCSpecification_VelocityMethod.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvBCSpecification_VelocityMethodConst : public FvBCSpecification_VelocityMethod
		{

		private:

			Vec2 theField_;

		public:

			FvBCSpecification_VelocityMethodConst(const Vec2& theField);

			Vec2 Value(const Geom_Pnt2d& theCoord) const;
		};
	}
}

#include <FvBCSpecification_VelocityMethodConstI.hxx>

#endif // !_FvBCSpecification_VelocityMethodConst_Header
