#pragma once
#ifndef _FvSources2d_BodyForce_Header
#define _FvSources2d_BodyForce_Header

#include <FvSources2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvBodyForce2d;

		class FvSources2d_BodyForce : public FvSources2d
		{

		private:

			const FvBodyForce2d& theBodyForce_;

		public:

			FvSources2d_BodyForce(const FvBodyForce2d& theBodyForce);

			virtual Geom_Pnt2d Value(const FvEntity_Element2d& theElement) const;
		};
	}
}

#endif // !_FvSources2d_BodyForce_Header
