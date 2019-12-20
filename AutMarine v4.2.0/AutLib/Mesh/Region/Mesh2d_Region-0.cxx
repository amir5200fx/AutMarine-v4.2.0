#include <Mesh2d_Region.hxx>

#include <Entity_Box2d.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_BlockEdgeOnPlane.hxx>
#include <SizeMap2d_SharpCornersSizeMapTool.hxx>
#include <SizeMap2d_AdaptiveCurvesSizeMapTool.hxx>

using namespace AutLib;
using namespace GeoLib;
using namespace CadLib;
using namespace MeshLib;

Standard_Integer AutLib::MeshLib::Mesh2d_Region::NbBoundaries() const
{
	return (Standard_Integer)theBoundaries_.size();
}

Standard_Integer AutLib::MeshLib::Mesh2d_Region::NbFeatures() const
{
	return (Standard_Integer)theFeaturePoints_.size();
}

Global_Handle(GeoMesh_BackGroundMesh2d) AutLib::MeshLib::Mesh2d_Region::BackGroundMesh() const
{
	return theBackMesh_;
}

void AutLib::MeshLib::Mesh2d_Region::CreateBoundary(const Standard_String Name)
{
	Global_Handle(SizeMap2d_AdaptiveCurvesSizeMapTool) Boundary = new SizeMap2d_AdaptiveCurvesSizeMapTool(theReference_, thePlane_);

	ImportBoundary(Name, Boundary);
}

void AutLib::MeshLib::Mesh2d_Region::CreateFeaturePoint(const Standard_String Name)
{
	Global_Handle(SizeMap2d_SharpCornersSizeMapTool) Feature = new SizeMap2d_SharpCornersSizeMapTool(theReference_, thePlane_);

	ImportFeature(Name, Feature);
}

void AutLib::MeshLib::Mesh2d_Region::DeleteBoundary(const Standard_String Name)
{
	TColSizeMap2d_StringMapOfHAdaptiveCurvesSizeMapTool::iterator Iter = theBoundaries_.find(Name);

	if (Iter EQUAL theBoundaries_.end())
	{
		cout << " The Boundary NOT found :" << Name << endl;
		return;
	}

	if (NOT Iter->second->NbCurvePatches())
	{
		theBoundaries_.erase(Name);
		return;
	}

	if (NbBoundaries() EQUAL 1)
	{
		theBoundaries_.erase(Name);
		return;
	}

	TColStd_Ary1dOfString Patches;
	Iter->second->RetrieveCurvePatchesTo(Patches);

	theBoundarySelected_ = theBoundaries_.begin();

	forThose(Index, 0, MaxIndexOf(Patches))
		ImportPart(Patches[Index]);

	theBoundaries_.erase(Name);

	theBoundarySelected_ = theBoundaries_.end();
}

void AutLib::MeshLib::Mesh2d_Region::DeleteFeaturePoint(const Standard_String Name)
{
	TColSizeMap2d_StringMapOfHSharpCornersSizeMapTool::iterator Iter = theFeaturePoints_.find(Name);

	if (Iter EQUAL theFeaturePoints_.end())
	{
		cout << " The Feature NOT found :" << Name << endl;
		return;
	}

	if (NOT Iter->second->NbPointPatches())
	{
		theFeaturePoints_.erase(Name);
		return;
	}

	if (NbFeatures() EQUAL 1)
	{
		theFeaturePoints_.erase(Name);
		return;
	}

	TColStd_Ary1dOfString Patches;
	Iter->second->RetrievePointPatchesTo(Patches);

	theFeatureSelected_ = theFeaturePoints_.begin();

	forThose(Index, 0, MaxIndexOf(Patches))
		ImportFeature(Patches[Index]);

	theFeaturePoints_.erase(Name);

	theFeatureSelected_ = theFeaturePoints_.end();
}

Global_Handle(SizeMap2d_BoundarySizeMapTool) AutLib::MeshLib::Mesh2d_Region::SelectBoundary(const Standard_String Name)
{
	TColSizeMap2d_StringMapOfHAdaptiveCurvesSizeMapTool::iterator Iter = theBoundaries_.find(Name);

	if (Iter EQUAL theBoundaries_.end())
	{
		cout << " The Boundary NOT found :" << Name << endl;
		return 0;
	}
	theBoundarySelected_ = Iter;

	return theBoundarySelected_->second;
}

Global_Handle(SizeMap2d_BoundarySizeMapTool) AutLib::MeshLib::Mesh2d_Region::SelectFeature(const Standard_String Name)
{
	TColSizeMap2d_StringMapOfHSharpCornersSizeMapTool::iterator Iter = theFeaturePoints_.find(Name);

	if (Iter EQUAL theFeaturePoints_.end())
	{
		cout << " The Feature NOT found :" << Name << endl;
		return 0;
	}
	theFeatureSelected_ = Iter;

	return theFeatureSelected_->second;
}

void AutLib::MeshLib::Mesh2d_Region::ImportPart(const Standard_String Name)
{
	if (theBoundarySelected_ EQUAL theBoundaries_.end())
	{
		cout << " There is no selected boundary" << endl;
		return;
	}

	Get_Const_Object(PlaneCurve) = *thePlane_->Edges();

	Global_Handle(Cad2d_BlockEdgeOnPlane) Patch = PlaneCurve.GetBlockCurve(Name);
	if (NOT Patch) return;

	TColSizeMap2d_StringMapOfHAdaptiveCurvesSizeMapTool::iterator Iter = thePatchToBoundary_.find(Name);
	if (Iter EQUAL thePatchToBoundary_.end())
	{
		thePatchToBoundary_[Name] = theBoundarySelected_->second;
		theBoundarySelected_->second->ImportCurvePatch(Name);
	}
	else
	{
		if (NOT Iter->second->RemoveCurvePatch(Name))
		{
			CloseProgram(" Mesh2d_ToolUniformRegion::ImportPart()");
		}

		thePatchToBoundary_.erase(Name);

		thePatchToBoundary_[Name] = theBoundarySelected_->second;
		theBoundarySelected_->second->ImportCurvePatch(Name);
	}
}

void AutLib::MeshLib::Mesh2d_Region::ImportFeature(const Standard_String Name)
{
	if (theFeatureSelected_ EQUAL theFeaturePoints_.end())
	{
		cout << " There is no selected Feature" << endl;
		return;
	}

	Get_Const_Object(Corners) = *thePlane_->Corners();

	Global_Handle(M_CAD Cad2d_BlockPointOnPlane) Patch = Corners.GetBlockPoint(Name);
	if (NOT Patch) return;

	TColSizeMap2d_StringMapOfHSharpCornersSizeMapTool::iterator Iter = thePointToFeature_.find(Name);
	if (Iter EQUAL thePointToFeature_.end())
	{
		thePointToFeature_[Name] = theFeatureSelected_->second;
		theFeatureSelected_->second->ImportPointPatch(Name);
	}
	else
	{
		if (NOT Iter->second->RemovePointPatch(Name))
		{
			CloseProgram(" Mesh2d_ToolUniformRegion::ImportFeature()");
		}

		thePointToFeature_.erase(Name);

		thePointToFeature_[Name] = theFeatureSelected_->second;
		theFeatureSelected_->second->ImportPointPatch(Name);
	}
}

void AutLib::MeshLib::Mesh2d_Region::UnSelectPart(const Standard_String Name)
{
	if (theBoundarySelected_ EQUAL theBoundaries_.end())
	{
		cout << " There is no selected boundary" << endl;
		return;
	}

	Get_Const_Object(PlaneCurve) = *thePlane_->Edges();

	Global_Handle(Cad2d_BlockEdgeOnPlane) Patch = PlaneCurve.GetBlockCurve(Name);
	if (NOT Patch) return;

	if (NOT theBoundarySelected_->second->RemoveCurvePatch(Name))
		return;

	thePatchToBoundary_.erase(Name);
}

void AutLib::MeshLib::Mesh2d_Region::UnSelectFeature(const Standard_String Name)
{
	if (theFeatureSelected_ == theFeaturePoints_.end())
	{
		cout << " There is no selected Feature" << endl;
		return;
	}

	Get_Const_Object(PlanePoints) = *thePlane_->Corners();

	Global_Handle(M_CAD Cad2d_BlockPointOnPlane) Patch = PlanePoints.GetBlockPoint(Name);
	if (NOT Patch) return;

	if (NOT theFeatureSelected_->second->RemovePointPatch(Name))
		return;

	thePointToFeature_.erase(Name);
}

void AutLib::MeshLib::Mesh2d_Region::PrintBoundaries(Standard_OStream & Ostream) const
{
	Ostream << "-----------------{ Boundary Informations }-----------------\n";
	Ostream << " Nb. of Boundaries= " << NbBoundaries() << endl;

	TColSizeMap2d_StringMapOfHAdaptiveCurvesSizeMapTool::const_iterator Iter = theBoundaries_.begin();
	while (Iter NOT_EQUAL theBoundaries_.end())
	{
		Ostream << endl;
		Ostream << " Boundary Name = " << Iter->first << endl;
		Iter->second->PrintEdges(Ostream);
		Iter++;
	}
	Ostream << "-----------------{ End of Boundary Informations }-----------------\n";
}

void AutLib::MeshLib::Mesh2d_Region::PrintFeatures(Standard_OStream & Ostream) const
{
	Ostream << "-----------------{ Feature Informations }-----------------\n";
	Ostream << " Nb. of Feautures= " << NbFeatures() << endl;

	TColSizeMap2d_StringMapOfHSharpCornersSizeMapTool::const_iterator Iter = theFeaturePoints_.begin();
	while (Iter NOT_EQUAL theFeaturePoints_.end())
	{
		Ostream << endl;
		Ostream << " Feature Name = " << Iter->first << endl;
		Iter->second->PrintPoints(Ostream);
		Iter++;
	}
	Ostream << "-----------------{ End of Feature Informations }-----------------\n";
}

void AutLib::MeshLib::Mesh2d_Region::Perform()
{
	Entity_Box2d Domain = thePlane_->BoundingBox();

	const Standard_Real Diameter = Domain.Diameter();
	Domain = Domain.OffsetBox(0.02*Diameter);

	TColSizeMap2d_StringMapOfHAdaptiveCurvesSizeMapTool::iterator Iter1 = theBoundaries_.begin();
	while (Iter1 NOT_EQUAL theBoundaries_.end())
	{
		Iter1->second->SetDomain(Domain);
		Iter1->second->CreateSizeMap();
		Iter1++;
	}

	TColSizeMap2d_StringMapOfHSharpCornersSizeMapTool::iterator Iter2 = theFeaturePoints_.begin();
	while (Iter2 NOT_EQUAL theFeaturePoints_.end())
	{
		if (Iter2->second->MeshConditions().CustomSurfaceSize())
		{
			Iter2->second->SetDomain(Domain);
			Iter2->second->CreateSizeMap();
		}
		Iter2++;
	}

	UnionMaps();
}

void AutLib::MeshLib::Mesh2d_Region::Clear()
{
	TColSizeMap2d_StringMapOfHAdaptiveCurvesSizeMapTool::iterator Iter1 = theBoundaries_.begin();
	while (Iter1 NOT_EQUAL theBoundaries_.end())
	{
		FreePointer(Iter1->second);
		Iter1++;
	}

	TColSizeMap2d_StringMapOfHSharpCornersSizeMapTool::iterator Iter2 = theFeaturePoints_.begin();
	while (Iter2 NOT_EQUAL theFeaturePoints_.end())
	{
		FreePointer(Iter2->second);
		Iter2++;
	}

	if (theGenerated_)
	{
		theGenerated_->ReleaseMemory();

		FreePointer(theGenerated_);
	}
}

void AutLib::MeshLib::Mesh2d_Region::Init()
{
	Global_Handle(SizeMap2d_AdaptiveCurvesSizeMapTool) Default = new SizeMap2d_AdaptiveCurvesSizeMapTool(theReference_, thePlane_);

	ImportBoundary("Default", Default);

	Get_Const_Object(PlaneCurve) = *thePlane_->Edges();
	TColCad2d_HAry1dOfBlockEdgeOnPlane Patches;
	PlaneCurve.RetrieveTo(Patches);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Patches)
	)
	{
		thePatchToBoundary_[Patches[Index]->Name()] = Default;
		Default->ImportCurvePatch(Patches[Index]->Name());
	}
}

void AutLib::MeshLib::Mesh2d_Region::ImportBoundary(const Standard_String Name, Global_Handle(SizeMap2d_AdaptiveCurvesSizeMapTool) SizeControl)
{
	std::pair<TColSizeMap2d_StringMapOfHAdaptiveCurvesSizeMapTool::iterator, Standard_Boolean> ret;
	ret = theBoundaries_.insert(std::pair<Standard_String, Global_Handle(SizeMap2d_AdaptiveCurvesSizeMapTool)>(Name, SizeControl));

	if (ret.second EQUAL Standard_False)
	{
		ImportBoundary(Name + "(1)", SizeControl);
		return;
	}
}

void AutLib::MeshLib::Mesh2d_Region::ImportFeature(const Standard_String Name, Global_Handle(SizeMap2d_SharpCornersSizeMapTool) SizeControl)
{
	std::pair<TColSizeMap2d_StringMapOfHSharpCornersSizeMapTool::iterator, Standard_Boolean> ret;
	ret = theFeaturePoints_.insert(std::pair<Standard_String, Global_Handle(SizeMap2d_SharpCornersSizeMapTool)>(Name, SizeControl));

	if (ret.second EQUAL Standard_False)
	{
		ImportFeature(Name + "(1)", SizeControl);
		return;
	}
}

void AutLib::MeshLib::Mesh2d_Region::RetrieveTo(TColSizeMap2d_HAry1dOfAdaptiveCurvesSizeMapTool & Maps) const
{
	Maps.Resize(NbBoundaries());

	Standard_Integer K = 0;
	TColSizeMap2d_StringMapOfHAdaptiveCurvesSizeMapTool::const_iterator Iter = theBoundaries_.begin();
	while (Iter NOT_EQUAL theBoundaries_.end())
	{
		Maps[K++] = (Global_Handle(SizeMap2d_AdaptiveCurvesSizeMapTool))Iter->second;
		Iter++;
	}
}

void AutLib::MeshLib::Mesh2d_Region::RetrieveTo(TColSizeMap2d_HAry1dOfSharpCornersSizeMapTool & Maps) const
{
	Maps.Resize(NbFeatures());

	Standard_Integer K = 0;
	TColSizeMap2d_StringMapOfHSharpCornersSizeMapTool::const_iterator Iter = theFeaturePoints_.begin();
	while (Iter NOT_EQUAL theFeaturePoints_.end())
	{
		Maps[K++] = (Global_Handle(SizeMap2d_SharpCornersSizeMapTool))Iter->second;
		Iter++;
	}
}