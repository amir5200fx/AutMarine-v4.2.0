#pragma once
template<typename T>
inline AutLib::GeoLib::Geometry_ItemsSort<T>::Geometry_ItemsSort(Standard_Boolean(*IsLess)(const T &, const T &))
	: IsLess_(IsLess)
{
}

template<typename T>
inline void AutLib::GeoLib::Geometry_ItemsSort<T>::Peform(ADT_Ary1d<T>& a) const
{
	for (int i = a.Size() / 2 - 1; i >= 0; --i)
		PercDown(a, i, a.Size());

	for (int j = a.Size() - 1; j > 0; --j)
	{
		std::swap(a[0], a[j]);
		PercDown(a, 0, j);
	}
}

template<typename T>
inline void AutLib::GeoLib::Geometry_ItemsSort<T>::PercDown
(
	ADT_Ary1d<T>& a, 
	Standard_Integer i, 
	const Standard_Integer n
) const
{
	Standard_Integer child;
	T tmp;

	for (tmp = a[i]; left_child(i) < n; i = child)
	{
		child = left_child(i);
		if (child != n - 1 AND (IsLess_(a[child], a[child + 1])))
			++child;
		if (IsLess_(tmp, a[child]))
			a[i] = a[child];
		else
			break;
	}
	a[i] = tmp;
}