#pragma once
#ifndef _Merge_Merge2dParameter_Header
#define _Merge_Merge2dParameter_Header

#include <Standard_Real.hxx>
#include <Standard_Integer.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Merge_Merge2dParameter
		{

		private:

			Standard_Real theXmin_;
			Standard_Real theYmin_;

			Standard_Real theDelta_;

			Standard_Integer theMaxIndex_;

		public:

			Merge_Merge2dParameter();

			Standard_Real Xmin() const;

			Standard_Real Ymin() const;

			Standard_Real Delta() const;

			Standard_Integer MaxIndex() const;

			void SetXmin(const Standard_Real Value);

			void SetYmin(const Standard_Real Value);

			void SetDelta(const Standard_Real Value);

			void SetMaxIndex(const Standard_Integer Value);
		};
	}
}

#include <Merge_Merge2dParameterI.hxx>

#endif // !_Merge_Merge2dParameter_Header
