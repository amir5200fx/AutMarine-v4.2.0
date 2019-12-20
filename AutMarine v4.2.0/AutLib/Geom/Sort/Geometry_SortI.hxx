template<typename T>
inline void AutLib::GeoLib::Geometry_Sort<T>::Sort(ADT_Ary1d<T>& a, TColStd_Ary1dOfInteger & s)
{
	for (int i = a.Size() / 2 - 1; i >= 0; --i)
		Geometry_Sort<T>::PercDown(a, s, i, a.Size());

	for (int j = a.Size() - 1; j > 0; --j)
	{
		std::swap(a[0], a[j]);
		std::swap(s[0], s[j]);

		Geometry_Sort<T>::PercDown(a, s, 0, j);
	}
}

template<typename T>
inline void AutLib::GeoLib::Geometry_Sort<T>::Sort(ADT_Ary1d<T>& a)
{
	for (int i = a.Size() / 2 - 1; i >= 0; --i)
		Geometry_Sort<T>::PercDown(a, i, a.Size());

	for (int j = a.Size() - 1; j > 0; --j)
	{
		std::swap(a[0], a[j]);
		Geometry_Sort<T>::PercDown(a, 0, j);
	}
}

template<typename T>
inline void AutLib::GeoLib::Geometry_Sort<T>::PercDown(ADT_Ary1d<T>& a, TColStd_Ary1dOfInteger & s, Standard_Integer i, const Standard_Integer n)
{
	Standard_Integer child;
	Standard_Integer s_tmp;
	T tmp;

	for (tmp = a[i], s_tmp = s[i]; left_child(i) < n; i = child)
	{
		child = left_child(i);
		if (child != n - 1 && a[child] < a[child + 1])
			++child;
		if (tmp < a[child])
		{
			a[i] = a[child];
			s[i] = s[child];
		}
		else
			break;
	}
	a[i] = tmp;
	s[i] = s_tmp;
}

template<typename T>
inline void AutLib::GeoLib::Geometry_Sort<T>::PercDown(ADT_Ary1d<T>& a, Standard_Integer i, const Standard_Integer n)
{
	Standard_Integer child;
	T tmp;

	for (tmp = a[i]; left_child(i) < n; i = child)
	{
		child = left_child(i);
		if (child != n - 1 && a[child] < a[child + 1])
			++child;
		if (tmp < a[child])
			a[i] = a[child];
		else
			break;
	}
	a[i] = tmp;
}