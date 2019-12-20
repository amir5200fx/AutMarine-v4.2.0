#pragma once
#ifndef _Prop_BladeForm_Header
#define _Prop_BladeForm_Header

#include <Prop_PitchForm.hxx>
#include <Prop_SkewForm.hxx>
#include <Prop_ChordForm.hxx>
#include <Prop_CamberForm.hxx>
#include <Prop_RakeForm.hxx>
#include <Prop_ThicknessForm.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Prop_BladeForm
		{

		private:

			Prop_PitchForm thePitch_;

			Prop_ChordForm theChord_;

			Prop_CamberForm theChamber_;

			Prop_SkewForm theSkew_;

			Prop_ThicknessForm theThickness_;

			Prop_RakeForm theRake_;

		public:

			Prop_BladeForm();

			const Prop_PitchForm& PitchForm() const;

			const Prop_ChordForm& ChordForm() const;

			const Prop_CamberForm& CamberForm() const;

			const Prop_SkewForm& SkewForm() const;

			const Prop_ThicknessForm& ThicknessForm() const;

			const Prop_RakeForm& RakeForm() const;

			Prop_PitchForm& PitchForm();

			Prop_ChordForm& ChordForm();

			Prop_CamberForm& CamberForm();

			Prop_SkewForm& SkewForm();

			Prop_ThicknessForm& ThicknessForm();

			Prop_RakeForm& RakeForm();
		};
	}
}

#include <Prop_BladeFormI.hxx>

#endif // !_Prop_BladeForm_Header
