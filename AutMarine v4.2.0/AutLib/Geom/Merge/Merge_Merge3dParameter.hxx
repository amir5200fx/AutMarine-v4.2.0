#pragma once
#ifndef _Merge_Merge3dParameter_Header
#define _Merge_Merge3dParameter_Header

#include <Standard_Real.hxx>
#include <Standard_Integer.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Merge_Merge3dParameter
		{

		private:

			Standard_Real theXmin_;
			Standard_Real theYmin_;
			Standard_Real theZmin_;

			Standard_Real theDelta_;

			Standard_Integer theMaxIndex_;

		public:

			Merge_Merge3dParameter();

			Standard_Real Xmin() const;

			Standard_Real Ymin() const;

			Standard_Real Zmin() const;

			Standard_Real Delta() const;

			Standard_Integer MaxIndex() const;

			void SetXmin(const Standard_Real Value);

			void SetYmin(const Standard_Real Value);

			void SetZmin(const Standard_Real Value);

			void SetDelta(const Standard_Real Value);

			void SetMaxIndex(const Standard_Integer Value);
		};
	}
}

#include <Merge_Merge3dParameterI.hxx>

#endif // !_Merge_Merge3dParameter_Header
