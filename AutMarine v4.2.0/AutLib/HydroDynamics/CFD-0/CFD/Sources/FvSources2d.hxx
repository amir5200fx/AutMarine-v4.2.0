#pragma once
#ifndef _FvSources2d_Header
#define _FvSources2d_Header

#include <Geom_Pnt2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvVariables2d;
		class FvEntity_Element2d;

		class FvSources2d
		{

		private:


		public:

			virtual Geom_Pnt2d Value(const FvEntity_Element2d& theElement) const = 0;

		protected:

			FvSources2d();

		};
	}
}

#endif // !_FvSources2d_Header
