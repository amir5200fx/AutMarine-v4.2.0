#pragma once
#ifndef _Prop_ExpandedView_Header
#define _Prop_ExpandedView_Header

#include <TColStd_Ary1dOfReal.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Prop_ExpandedView
		{

		private:

			TColStd_Ary1dOfReal theX_;

			TColStd_Ary1dOfReal theXS_;
			TColStd_Ary1dOfReal theTF_;
			TColStd_Ary1dOfReal theTB_;
			TColStd_Ary1dOfReal theYF_;
			TColStd_Ary1dOfReal theYB_;

		public:

			Prop_ExpandedView(const Standard_Integer theNbSegments);

			Standard_Real X(const Standard_Integer theIndex) const;

			Standard_Real XS(const Standard_Integer theIndex) const;

			Standard_Real TF(const Standard_Integer theIndex) const;

			Standard_Real TB(const Standard_Integer theIndex) const;

			Standard_Real YF(const Standard_Integer theIndex) const;

			Standard_Real YB(const Standard_Integer theIndex) const;

			void SetX(const Standard_Integer theIndex, const Standard_Real theValue);

			void SetXS(const Standard_Integer theIndex, const Standard_Real theValue);

			void SetTF(const Standard_Integer theIndex, const Standard_Real theValue);

			void SetTB(const Standard_Integer theIndex, const Standard_Real theValue);

			void SetYF(const Standard_Integer theIndex, const Standard_Real theValue);

			void SetYB(const Standard_Integer theIndex, const Standard_Real theValue);
		};
	}
}

#include <Prop_ExpandedViewI.hxx>

#endif // !_Prop_ExpandedView_Header
