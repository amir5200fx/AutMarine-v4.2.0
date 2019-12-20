#pragma once
#ifndef _Ship_StemForm_Header
#define _Ship_StemForm_Header

#include <Standard_TypeDef.hxx>
#include <Standard_OStream.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Ship_StemForm
		{

		private:

			Standard_Real BowRounding_;
			Standard_Real StemRake_;
			Standard_Real StemCurvature_;
			Standard_Real StemCurvaturePos_;
			Standard_Real ForeFootShape_;

		public:

			Ship_StemForm();

			void SetBowRounding(const Standard_Real Value);

			void SetStemRake(const Standard_Real Value);

			void SetStemCurvature(const Standard_Real Value);

			void SetStemCurvaturePosition(const Standard_Real Value);

			void SetForeFootShape(const Standard_Real Value);

			Standard_Real BowRounding() const;

			Standard_Real Rake() const;

			Standard_Real StemCurvature() const;

			Standard_Real StemCurvaturePosition() const;

			Standard_Real ForeFootShape() const;

			void Print(Standard_OStream& Ostream = cout) const;
		};
	}
}

#endif // !_Ship_StemForm_Header
