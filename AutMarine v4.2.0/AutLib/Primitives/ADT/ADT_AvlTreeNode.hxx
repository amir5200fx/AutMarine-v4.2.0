#pragma once
#ifndef _ADT_AvlTreeNode_Header
#define _ADT_AvlTreeNode_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{
	template<typename Comparable>
	class ADT_AvlTree;

	template<typename Comparable>
	class ADT_NumbAvlTree;

	template<typename Comparable>
	class ADT_AdressAvlTree;

	template<typename Comparable>
	class ADT_AvlTreeNode
	{
		friend class ADT_AvlTree<Comparable>;
		friend class ADT_NumbAvlTree<Comparable>;
		friend class ADT_AdressAvlTree<Comparable>;

	private:

		Comparable theElement_;

		ADT_AvlTreeNode<Comparable>* theLeft_;
		ADT_AvlTreeNode<Comparable>* theRight_;

		Standard_Integer theHeight_;

	public:

		ADT_AvlTreeNode(const Comparable& Element, ADT_AvlTreeNode<Comparable>* Left, ADT_AvlTreeNode<Comparable>* Right, const Standard_Integer Height = 0);
	};
}

#include <ADT_AvlTreeNodeI.hxx>

#endif // !_ADT_AvlTreeNode_Header
