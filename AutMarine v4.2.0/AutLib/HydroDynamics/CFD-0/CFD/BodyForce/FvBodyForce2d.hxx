#pragma once
#ifndef _FvBodyForce2d_Header
#define _FvBodyForce2d_Header

#include <Geom_Pnt2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvBodyForce2d
		{

		private:


		public:

			virtual ~FvBodyForce2d();

			virtual Geom_Pnt2d Value(const Geom_Pnt2d& theCoord) const = 0;

		protected:

			FvBodyForce2d();
		};
	}
}

#endif // !_FvBodyForce_Header
