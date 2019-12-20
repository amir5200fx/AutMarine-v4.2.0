#pragma once
#ifndef _FvBodyForce2d_Free_Header
#define _FvBodyForce2d_Free_Header

#include <FvBodyForce2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvBodyForce2d_Free : public FvBodyForce2d
		{

		private:


		public:

			FvBodyForce2d_Free();

			virtual ~FvBodyForce2d_Free();

			virtual Geom_Pnt2d Value(const Geom_Pnt2d& theCoord) const;
		};
	}
}

#include <FvBodyForce2d_FreeI.hxx>

#endif // !_FvBodyForce2d_Free_Header
