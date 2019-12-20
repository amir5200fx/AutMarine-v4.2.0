#include <Duct_Hull.hxx>

void AutLib::CadLib::Duct_Hull::DefaultParameters()
{
	Duct_Dimensions & Dimensions = theParameters_.Dimensions();

	Dimensions.SetNbSections(20);

	Dimensions.SetOveralLength((Standard_Real)160.0);
	Dimensions.SetBreadthAtInlet((Standard_Real)35.0);
	Dimensions.SetBreadthAtOutlet((Standard_Real)20.0);
	Dimensions.SetDepthAtInlet((Standard_Real)15.0);
	Dimensions.SetDepthAtOutlet((Standard_Real)20.0);
	Dimensions.SetHeightAtOutlet((Standard_Real)20.0);
	
	Get_Object(Hull) = theParameters_.HullForm();
	Hull.SetMidLocation((Standard_Real)0.5);

	/* Inlet section Parameters */
	Get_Object(Inlet) = Hull.InletForm();
	Inlet.SetWidth((Standard_Real)0.0);
	Inlet.SetSideSlope((Standard_Real)0.75);
	Inlet.SetUpperTightness((Standard_Real)1.0);
	Inlet.SetLowerTightness((Standard_Real)0.65);

	/* Middle section Parameters */
	Get_Object(Mid) = Hull.MidForm();
	Mid.SetWidth((Standard_Real)0.0);
	Mid.SetSideSlope((Standard_Real)0.5);
	Mid.SetUpperTightness((Standard_Real)0.25);
	Mid.SetLowerTightness((Standard_Real)0.25);

	/* Outlet section Parameters */
	Get_Object(Outlet) = Hull.OutletForm();
	Outlet.SetWidth((Standard_Real)0.0);
	Outlet.SetSideSlope((Standard_Real)0.5);
	Outlet.SetUpperTightness((Standard_Real)1.0);
	Outlet.SetLowerTightness((Standard_Real)1.0);

	Get_Object(Breadth) = theParameters_.Breadth();
	Breadth.SetInletOffset((Standard_Real)0.0);
	Breadth.SetInletRiseWeight((Standard_Real)0.0);
	Breadth.SetInletWeight((Standard_Real)0.0);
	Breadth.SetLeftTurningPosition((Standard_Real)0.5);
	Breadth.SetLeftTurningWidth((Standard_Real)1.0);
	Breadth.SetMidOffset((Standard_Real)0.0);
	Breadth.SetMidWidth((Standard_Real)0.4);
	Breadth.SetOutletOffset((Standard_Real)0.0);
	Breadth.SetOutletRiseWeight((Standard_Real)0.0);
	Breadth.SetOutletWeight((Standard_Real)0.0);
	Breadth.SetRightTurningPosition((Standard_Real)0.5);
	Breadth.SetRightTurningWidth((Standard_Real)1.0);
	
	Get_Object(Depth) = theParameters_.Depth();
	Depth.SetInletOffset((Standard_Real)0.0);
	Depth.SetInletRiseWeight((Standard_Real)0.0);
	Depth.SetInletWeight((Standard_Real)0.0);
	Depth.SetLeftTurningPosition((Standard_Real)0.5);
	Depth.SetLeftTurningWidth((Standard_Real)1.0);
	Depth.SetMidOffset((Standard_Real)0.0);
	Depth.SetMidWidth((Standard_Real)1.0);
	Depth.SetOutletOffset((Standard_Real)0.0);
	Depth.SetOutletRiseWeight((Standard_Real)0.0);
	Depth.SetOutletWeight((Standard_Real)0.0);
	Depth.SetRightTurningPosition((Standard_Real)0.5);
	Depth.SetRightTurningWidth((Standard_Real)1.0);

	Get_Object(Generator) = theParameters_.Generator();
	Generator.SetRisePoint((Standard_Real)0.6);
	Generator.SetPosition((Standard_Real)0.5);
	Generator.SetRiseTangent((Standard_Real)0.3);
	Generator.SetOutletTangent((Standard_Real)0.2);

	Apply_Smoothing_ = Standard_True;
}