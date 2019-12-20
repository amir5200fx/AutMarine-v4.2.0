#include <Examples\Cad\Example_Solid.hxx>

#include <Prop_Propeller.hxx>
#include <Cad3d_Solid.hxx>
#include <Cad3d_BlockEntityOnSolid.hxx>

using namespace AutLib;
using namespace CadLib;

void AutLib::Example_Solid::MakePropellerCase1()
{
	Open_OutputFile_TecPlot(Plot, "Example_MakePropellerCase1");

	Prop_Propeller Propeller;

	Get_Object(Parameters) = Propeller.Parameters();
	Parameters.SetToRemoveHubApex();
	
	Get_Object(Hub) = Parameters.HubParameters();
	Hub.SetShaftLength(0);

	Propeller.SetToDiscreteMyModel();
	Propeller.Make();	
	Propeller.ExportMyModelToPlt(Plot);

	Global_Handle(Cad3d_Solid) Solid = Propeller.GetSolid();

	Get_Pointer(Surfaces) = Solid->Surfaces();
	Debug_Null_Pointer(Surfaces);

	Surfaces->Print(Standard_True);

	Get_Const_Pointer(Block) = Surfaces->SelectBlockEntity("Default Block Surface");
	Debug_Null_Pointer(Block);

	Block->SelectEntity(1);
	Block->SelectEntity(2);
	Block->SelectEntity(4);
	Block->SelectEntity(23);
	Surfaces->Split("Hub");

	Block = Surfaces->SelectBlockEntity("Default Block Surface");
	Debug_Null_Pointer(Block);

	Block->SelectEntity(3);
	Surfaces->Split("Hub Apex");

	Block = Surfaces->SelectBlockEntity("Default Block Surface");
	Debug_Null_Pointer(Block);

	Block->SelectEntity(24);
	Block->SelectEntity(25);
	Block->SelectEntity(26);
	Block->SelectEntity(27);
	Block->SelectEntity(28);
	Block->SelectEntity(29);
	Surfaces->Split("Tip");

	Block = Surfaces->SelectBlockEntity("Default Block Surface");
	Debug_Null_Pointer(Block);

	Block->SelectEntity(7);
	Block->SelectEntity(10);
	Block->SelectEntity(13);
	Block->SelectEntity(16);
	Block->SelectEntity(19);
	Block->SelectEntity(22);
	Surfaces->Split("Trailing Edge");

	Block = Surfaces->SelectBlockEntity("Default Block Surface");
	Surfaces->RenameBlock("Blades");

	Solid->ExportBlockSurfacesToPlt(Plot);

	Open_OutputFile_txt(Report, "Example_MakePropellerCase1");
	Solid->Report(Report);
	Surfaces->Print(Standard_True, Report);

	FreePointer(Solid);

	/*Propeller.SetIGESFileName("MyPropeller.igs");
	Propeller.ExportToIGES();*/

	

	/*fstream File;
	File.open("MyPropeller.igs", ios::out);

	Propeller.ExportToIGES(File);*/

	//Propeller.ExportMyCurvesToPlt(Plot);
	//Propeller.ExportMyBladesToPlt(Plot);
	//Propeller.ExportMyHubToPlt(Plot);
	//Propeller.Profiles().ExportSkewProfileToPlt(Profile);
}