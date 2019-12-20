#pragma once
#ifndef _Ship_Dimensions_Header
#define _Ship_Dimensions_Header

#include <Standard_TypeDef.hxx>
#include <Standard_OStream.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Ship_Dimensions
		{

		private:

			Standard_Real theDraft_;
			Standard_Real theTransomHeight_;

			Standard_Real theDepthAtBow_;
			Standard_Real theDepthAtTransom_;

			Standard_Real theBeamOnDeck_;
			Standard_Real theLenghtOnDeck_;

			Standard_Integer theNbNetRows_;
			Standard_Integer theNbNetColumns_;

		public:

			Ship_Dimensions();

			Standard_Real Draft() const;

			Standard_Real TransomHeight() const;

			Standard_Real DepthAtBow() const;

			Standard_Real DepthAtTransom() const;

			Standard_Real BeamOnDeck() const;

			Standard_Real LengthOnDeck() const;

			Standard_Integer NbNetRows() const;

			Standard_Integer NbNetColumns() const;

			void SetDraft(const Standard_Real Value);

			void SetTransonHeight(const Standard_Real Value);

			void SetDepthAtBow(const Standard_Real Value);

			void SetDepthAtTransom(const Standard_Real Value);

			void SetBeamOnDeck(const Standard_Real Value);

			void SetLengthOnDeck(const Standard_Real Value);

			void SetNbNetRows(const Standard_Integer Value);

			void SetNbNetColumns(const Standard_Integer Value);

			void Print(Standard_OStream& Ostream = cout) const;
		};
	}
}

#endif // !_Ship_Dimensions_Header
