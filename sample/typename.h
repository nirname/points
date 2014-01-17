#ifndef TYPE_NAME_H
#define TYPE_NAME_H 1

template <typename T>
struct TypeName
{
	static const char * get()
	{
		return typeid(T).name();
	}
};

// a specialization for each type of those you want to support
// and don't like the string returned by typeid
template <>
struct TypeName<int>
{
	static const char* get()
	{
		return "int";
	}
};

// usage:
//const char * name = TypeName<MyType>::Get();

#endif
