#pragma once
inline
Standard_Real AutLib::MeshLib::Mesh3d_Optimization::CalcQuality(const Mesh3d_Element & theElement) const
{
	Get_Const_Pointer(Node0) = theElement.Node(0);
	Get_Const_Pointer(Node1) = theElement.Node(1);
	Get_Const_Pointer(Node2) = theElement.Node(2);
	Get_Const_Pointer(Node3) = theElement.Node(3);

	Debug_Null_Pointer(Node0);
	Debug_Null_Pointer(Node1);
	Debug_Null_Pointer(Node2);
	Debug_Null_Pointer(Node3);

	return theQualityMap_.CalcQuality(Node0->Coord(), Node1->Coord(), Node2->Coord(), Node3->Coord());
}