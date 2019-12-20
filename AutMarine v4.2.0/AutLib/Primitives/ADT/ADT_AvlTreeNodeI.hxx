#pragma once

template<typename Comparable>
inline AutLib::ADT_AvlTreeNode<Comparable>::ADT_AvlTreeNode
(
	const Comparable & Element,
	ADT_AvlTreeNode<Comparable>* Left,
	ADT_AvlTreeNode<Comparable>* Right, 
	const Standard_Integer Height
)
	: theElement_(Element)
	, theLeft_(Left)
	, theRight_(Right)
	, theHeight_(Height)
{
}