#ifndef DECLARATIONS_H
#define DECLARATIONS_H 1


// make types.h without namespace
typedef unsigned int positive;
typedef std::string KeyType;

//template<typename> class Mapping
template<typename ValueType> struct Mapping {
	typedef std::map<KeyType, ValueType> Type;
	typedef Type * Pointer;
};

//typename std::map Mapping;
/*template<typename T>
struct At
{
	typedef typename A<T, true> Type;
};

template<typename T>
struct Af
{
	typedef typename A<T, false> Type;
};

Af<int>::Type foo;
At<float>::Type bar;*/


namespace lib {
	//template <typename Type> class List;
}

namespace image {
	void redisplay(int);
}

namespace graphics {
	void square();
	struct Color;
	struct Shape;

	typedef Color * ColorPointer;
	typedef Shape * ShapePointer;

	struct Animation;
	typedef Animation * AnimationPointer;
	typedef std::map< KeyType, AnimationPointer > AnimationMap;
	typedef AnimationMap::iterator AnimationMapIterator;
}

namespace engine {

	struct Screen;
	struct Level;
	struct Game;
	struct Field;
	struct View;
	struct Object;
	struct Point;
	struct Size;

	typedef Field  * FieldPointer;
	typedef View   * ViewPointer;
	typedef Object * ObjectPointer;
	typedef Point  * PointPointer;

	typedef std::string ObjectKindType;

	typedef Mapping< FieldPointer  > FieldMetaMapping;
	typedef Mapping< ViewPointer   > ViewMetaMapping;
	typedef Mapping< ObjectPointer > ObjectMetaMapping;
	typedef Mapping< graphics::ColorPointer > ColorMetaMapping;
	typedef Mapping< graphics::ShapePointer > ShapeMetaMapping;

	typedef typename  FieldMetaMapping::Type  FieldMap;
	typedef typename   ViewMetaMapping::Type   ViewMap;
	typedef typename ObjectMetaMapping::Type ObjectMap;
	typedef typename  ColorMetaMapping::Type  ColorMap;
	typedef typename  ShapeMetaMapping::Type  ShapeMap;

	typedef typename  FieldMetaMapping::Pointer  FieldMapPointer;
	typedef typename   ViewMetaMapping::Pointer   ViewMapPointer;
	typedef typename ObjectMetaMapping::Pointer ObjectMapPointer;
	typedef typename  ColorMetaMapping::Pointer  ColorMapPointer;
	typedef typename  ShapeMetaMapping::Pointer  ShapeMapPointer;

	/*typedef Mapping< graphics::ColorPointer >::Type ColorMap;
	typedef Mapping< graphics::ShapePointer >::Type ShapeMap;*/

	typedef std::map< Object *, Point > ObjectInformation;
	typedef std::map< Point, Object * > PointInformation;

	typedef ObjectInformation::iterator ObjectInformationIterator;
	typedef PointInformation::iterator PointInformationIterator;

	enum INTERACTION_TYPE {
		PUSH_INTERACTION,
		PULL_INTERACTION,
		DESTROY_INTERACTION,
		CREATE_INTERACTION
	};

	typedef std::pair< ObjectKindType, ObjectKindType > PairOfKinds;
	typedef std::map< PairOfKinds, INTERACTION_TYPE > InteractionMap;
	typedef InteractionMap::iterator InteractionMapIterator;

	typedef std::list <Level> LevelList;
	typedef LevelList::iterator LevelListIterator;

}

extern engine::Screen screen;
extern engine::Game game;

#endif
