#ifndef GAME_H
#define GAME_H 1

namespace engine {



	// Describes current game
	struct Game {

		logic::GAME_KIND game_kind;
		//engine::Screen screen;
		bool paused;

		FieldMap  fields;
		ViewMap   views;
		ColorMap  colors; // !!! use opengl palette
		ShapeMap  shapes;
		ObjectMap objects;

		InteractionMap interactions;
		// Use unordered hash instead
		//PointMap points;

		Game(logic::GAME_KIND _game_kind):
			game_kind(_game_kind), paused(false)
		{}

		~Game(){
			for(FieldMap::iterator i = fields.begin(); i != fields.end(); ++i) {
				delete i->second;
			}
			for(ViewMap::iterator i = views.begin(); i != views.end(); ++i) {
				delete i->second;
			}
			for(ColorMap::iterator i = colors.begin(); i != colors.end(); ++i) {
				delete i->second;
			}
			for(ShapeMap::iterator i = shapes.begin(); i != shapes.end(); ++i) {
				delete i->second;
			}
			for(ObjectMap::iterator i = objects.begin(); i != objects.end(); ++i) {
				delete i->second;
			}
			/*for(PointMap::iterator i = points.begin(); i != points.end(); ++i) {
				delete i->second;
			}*/
		}

		/*FieldPointer add_field(const char * _name, int _width = 1, int _height = 1) {
			std::string field_name(_name);
			FieldPointer field;
			if(fields[field_name] != NULL) {
				field = fields[field_name];
				std::cout << "Field \"" << _name << "\" already exists" << std::endl;
			} else {
				field = new engine::Field(_width, _height);
				fields[field_name] = field;
			}
			return field;
		}*/

	};

}

#endif
