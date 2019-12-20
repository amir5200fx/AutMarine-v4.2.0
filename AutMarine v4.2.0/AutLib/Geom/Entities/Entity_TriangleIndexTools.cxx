#include <Entity_TriangleIndexTools.hxx>

#include <TColEntity_HAry1dOfBasicQueueOfEdgeIndex.hxx>

void AutLib::GeoLib::Entity_TriangleIndexTools::FormEdgesOfElements
(
	const TColEntity_Ary1dOfTriangleIndex & Elements,
	TColEntity_Ary1dOfEdgeIndex & Edges
)
{
	Standard_Integer MaxIndex = 0;

	forThose
	(
		Index,
		0,
		MaxIndexOf(Elements)
	)
	{
		Get_Const_Object(Element) = Elements[Index];

		if (Element.V0() > MaxIndex) MaxIndex = Element.V0();
		if (Element.V1() > MaxIndex) MaxIndex = Element.V1();
		if (Element.V2() > MaxIndex) MaxIndex = Element.V2();
	}

	TColEntity_HAry1dOfBasicQueueOfEdgeIndex EdgesAroundPoints(MaxIndex);
	TColEntity_BasicQueueOfEdgeIndex AllEdges;

	EdgesAroundPoints.Init(NULL);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Elements)
	)
	{
		Get_Const_Object(Element) = Elements[Index];

		forThose
		(
			I,
			0,
			2
		)
		{
			Standard_Integer Id1 = (I + 1) % 3;
			Standard_Integer Id2 = (Id1 + 1) % 3;

			Standard_Integer V1 = Element.Value(Id1);
			Standard_Integer V2 = Element.Value(Id2);

			Standard_Boolean Create = Standard_False;

			if (IsNULL(EdgesAroundPoints[Index_Of(V1)]) OR IsNULL(EdgesAroundPoints[Index_Of(V2)]))
			{
				Create = Standard_True;
			}
			else
			{
				Standard_Integer Size1 = EdgesAroundPoints[Index_Of(V1)]->Size();
				Standard_Integer Size2 = EdgesAroundPoints[Index_Of(V2)]->Size();

				TColEntity_Ary1dOfEdgeIndex TempEdges;

				Standard_Integer Compare;

				if (Size1 <= Size2)
				{
					EdgesAroundPoints[Index_Of(V1)]->RetrieveTo(TempEdges);

					Compare = V2;
				}
				else
				{
					EdgesAroundPoints[Index_Of(V2)]->RetrieveTo(TempEdges);

					Compare = V1;
				}

				Standard_Boolean Exist = Standard_False;

				forThose
				(
					J,
					0,
					MaxIndexOf(TempEdges)
				)
				{
					if (TempEdges[J].V1() EQUAL Compare)
					{
						Exist = Standard_True;

						break;
					}
				}

				if (NOT Exist)
					Create = Standard_True;
			}

			if (Create)
			{
				if (IsNULL(EdgesAroundPoints[Index_Of(V1)])) EdgesAroundPoints[Index_Of(V1)] = new TColEntity_BasicQueueOfEdgeIndex;
				if (IsNULL(EdgesAroundPoints[Index_Of(V2)])) EdgesAroundPoints[Index_Of(V2)] = new TColEntity_BasicQueueOfEdgeIndex;

				EdgesAroundPoints[Index_Of(V1)]->EnQueue(Entity_EdgeIndex(V1, V2));
				EdgesAroundPoints[Index_Of(V2)]->EnQueue(Entity_EdgeIndex(V2, V1));

				AllEdges.EnQueue(Entity_EdgeIndex(V1, V2));
			}
		}
	}
}