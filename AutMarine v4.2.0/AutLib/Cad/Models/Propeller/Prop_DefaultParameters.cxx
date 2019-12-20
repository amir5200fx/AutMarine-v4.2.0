#include <Prop_Propeller.hxx>

void AutLib::CadLib::Prop_Propeller::DefaultParameters()
{
	theParameters_.SetNbBlades(6);
	theParameters_.SetDiameter(300 * 0.02);
	theParameters_.SetHubRadius(30 * 0.02);

	theParameters_.SetNbSections(48);
	theParameters_.SetNbSpans(20);

	Get_Object(Blade) = theParameters_.BladeParameters();
	
	Get_Object(Pitch) = Blade.PitchForm();
	Pitch.SetRootPitch(55);
	Pitch.SetTipPitch(25);
	Pitch.SetRootSteep(0.5);
	Pitch.SetTipSteep(0.8);

	Get_Object(Skew) = Blade.SkewForm();
	Skew.SetRootSteep(0.5);
	Skew.SetTipSkew(100 * 0.02);  // 100
	Skew.SetTipSteep(0.5);

	Get_Object(Chord) = Blade.ChordForm();
	Chord.SetMaxChordLocation(0.6);
	Chord.SetRootChord(20 * 0.02);
	Chord.SetMaxChord(80 * 0.02);
	Chord.SetTipChord(0);  // 0
	Chord.SetRootWeight(0.5);
	Chord.SetTipWeight(0.8);

	Get_Object(Camber) = Blade.CamberForm();
	Camber.SetMaxCamberLocation(0.5);
	Camber.SetMaxCamber(0.01);
	Camber.SetRootCamber(0.004);
	Camber.SetTipCamber(0);
	Camber.SetRootWeight(0.5);
	Camber.SetTipWeight(0.5);

	Get_Object(Thickness) = Blade.ThicknessForm();
	Thickness.SetRootThickness(6 * 0.02);
	Thickness.SetTipThickness(3 * 0.02);
	Thickness.SetRootSteep(0.5);
	Thickness.SetTipSteep(0.5);

	Get_Object(Rake) = Blade.RakeForm();
	Rake.SetTipRake(30 * 0.02);

	Get_Object(Hub) = theParameters_.HubParameters();
	Hub.SetHubLength(70.0*0.02);
	Hub.SetHubWeight(0.5);
	Hub.SetShaftLength(2400 * 0.02);
	Hub.SetShaftOffset(50 * 0.02);
	Hub.SetShaftRadius(15 * 0.02);
}

//void AutLib::CadLib::Prop_Propeller::DefaultParameters()
//{
//	theParameters_.SetNbBlades(6);
//	theParameters_.SetDiameter(300);
//	theParameters_.SetHubRadius(30);
//
//	theParameters_.SetNbSections(48);
//	theParameters_.SetNbSpans(20);
//
//	Get_Object(Blade) = theParameters_.BladeParameters();
//
//	Get_Object(Pitch) = Blade.PitchForm();
//	Pitch.SetRootPitch(55);
//	Pitch.SetTipPitch(25);
//	Pitch.SetRootSteep(0.5);
//	Pitch.SetTipSteep(0.8);
//
//	Get_Object(Skew) = Blade.SkewForm();
//	Skew.SetRootSteep(0.5);
//	Skew.SetTipSkew(100);  // 100
//	Skew.SetTipSteep(0.5);
//
//	Get_Object(Chord) = Blade.ChordForm();
//	Chord.SetMaxChordLocation(0.6);
//	Chord.SetRootChord(20);
//	Chord.SetMaxChord(80);
//	Chord.SetTipChord(0);  // 0
//	Chord.SetRootWeight(0.5);
//	Chord.SetTipWeight(0.8);
//
//	Get_Object(Camber) = Blade.CamberForm();
//	Camber.SetMaxCamberLocation(0.5);
//	Camber.SetMaxCamber(0.01);
//	Camber.SetRootCamber(0.004);
//	Camber.SetTipCamber(0);
//	Camber.SetRootWeight(0.5);
//	Camber.SetTipWeight(0.5);
//
//	Get_Object(Thickness) = Blade.ThicknessForm();
//	Thickness.SetRootThickness(6);
//	Thickness.SetTipThickness(3);
//	Thickness.SetRootSteep(0.5);
//	Thickness.SetTipSteep(0.5);
//
//	Get_Object(Rake) = Blade.RakeForm();
//	Rake.SetTipRake(30);
//
//	Get_Object(Hub) = theParameters_.HubParameters();
//	Hub.SetHubLength(70.0);
//	Hub.SetHubWeight(0.5);
//	Hub.SetShaftLength(800);
//	Hub.SetShaftOffset(50);
//	Hub.SetShaftRadius(15);
//}