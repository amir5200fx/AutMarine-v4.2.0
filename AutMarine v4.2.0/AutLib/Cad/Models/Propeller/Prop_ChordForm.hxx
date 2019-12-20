#pragma once
#ifndef _Prop_ChordForm_Header
#define _Prop_ChordForm_Header

#include <Standard_Real.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Prop_ChordForm
		{

		private:

			Standard_Real theRootChord_;
			Standard_Real theTipChord_;

			Standard_Real theMaxChord_;
			Standard_Real theMaxChordLocation_;

			Standard_Real theRootWeight_;
			Standard_Real theTipWeight_;

		public:

			Prop_ChordForm();

			Standard_Real RootChord() const;

			Standard_Real TipChord() const;

			Standard_Real MaxChord() const;

			Standard_Real MaxChordLocation() const;

			Standard_Real RootWeight() const;

			Standard_Real TipWeight() const;

			void SetRootChord(const Standard_Real Value);

			void SetTipChord(const Standard_Real Value);

			void SetMaxChord(const Standard_Real Value);

			void SetMaxChordLocation(const Standard_Real Value);

			void SetRootWeight(const Standard_Real Value);

			void SetTipWeight(const Standard_Real Value);
		};
	}
}

#include <Prop_ChordFormI.hxx>

#endif // !_Prop_ChordForm_Header
