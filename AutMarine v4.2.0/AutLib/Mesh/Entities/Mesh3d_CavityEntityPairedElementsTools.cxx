#include <Mesh3d_CavityEntityPairedElementsTools.hxx>

#include <Mesh3d_Edge.hxx>
#include <Mesh3d_ElementTools.hxx>
#include <Mesh3d_CavityEntityNonConvexity.hxx>

using namespace AutLib;
using namespace MeshLib;

Global_Handle(Mesh3d_Facet) AutLib::MeshLib::Mesh3d_CavityEntityPairedElementsTools::PairedFacetOf(const Global_Handle(Mesh3d_Edge) theEdge)
{
	Debug_Null_Pointer(theEdge);
	Get_Const_Object(Edge) = *theEdge;

	if (NOT Edge.IsOnFront()) { THROW_STANDARD_EXCEPTION(" The Edge is not on front"); }

	TColMesh3d_HAry1dOfElement Elements = Edge.RetrieveElements();
	if (Elements.Size() NOT_EQUAL 2) { THROW_STANDARD_EXCEPTION(" the Edge is not right type"); }

	Debug_Null_Pointer(Elements[0]);
	Debug_Null_Pointer(Elements[1]);

	Global_Handle(Mesh3d_Facet) Paired(0);
	Try_Exception_Handle_Exit(Paired = Mesh3d_ElementTools::CommonFacet(*Elements[0], *Elements[1]));
	if (NOT Paired) { THROW_STANDARD_EXCEPTION("the elements are not paired"); }

	return Paired;
}