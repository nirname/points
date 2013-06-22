#ifndef GAME_H
#define GAME_H 1

namespace engine {

	/*void check_node(YAML::Node * _node, const char _option[]) {
		std::cout << _option << ": ";
		if((*_node)[_option]) {
			std::cout << "true" << std::endl;
		} else {
			std::cout << "no" << std::endl;
		}
	}*/

	// Describes current game
	struct Game {

		logic::GAME_KIND game_kind;
		LevelListIterator current_level;
		//engine::Screen screen;
		bool paused;

		LevelList    levels;

		FieldMap     fields;
		ViewMap      views;
		ColorMap     colors; // !!! use opengl palette
		ShapeMap     shapes;
		ObjectMap    objects;

		graphics::AnimationMap animations;

		InteractionMap interactions;
		// Use unordered hash instead
		//PointMap points;

		Game(logic::GAME_KIND _game_kind):
			game_kind(_game_kind), paused(false)
		{
			current_level = levels.begin();
		}

		//~Game();
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
			for(graphics::AnimationMap::iterator i = animations.begin(); i != animations.end(); ++i) {
				delete i->second;
			}

		}

		bool load() {

		/*if(config["lastLogin"])
		std::cout << "Last logged in: " << config["lastLogin"].as<DateTime>() << "\n";

		const std::string username = config["username"].as<std::string>();
		const std::string password = config["password"].as<std::string>();
		login(username, password);
		config["lastLogin"] = getCurrentDateTime();

		std::ofstream fout("config.yaml");
		fout << config;*/

			//std::ifstream level_data("levels/level_1.yaml");
			//YAML::Parser parser(level_data);

			/*std::string buffer;
			while(std::getline(level_data, buffer)) {
				std::cout << buffer << std::endl;
			}
			level_data.close();*/

			/*YAML::Node level_config = YAML::LoadFile("levels/level_1.yaml");

			if(level_config.IsMap()) {
				check_node(&level_config, "kinds");
				check_node(&level_config, "objects");
				check_node(&level_config, "interactions");
				check_node(&level_config, "fields");
				check_node(&level_config, "views");
			} else {
				std::cout << "Config shoul contains mapping" << std::endl;
			}*/

			//std::cout << (level_config["first"].as<std::string>()) << std::endl;

			/*YAML::Node node;
			while(parser.GetNextDocument(node)) {
			}*/

			/*DIR *dir;
			struct dirent *ent;
			if ((dir = opendir ("c:\\src\\")) != NULL) {
				// print all the files and directories within directory
				while ((ent = readdir (dir)) != NULL) {
					printf ("%s\n", ent->d_name);
				}
				closedir(dir);
			} else {
				// could not open directory
				perror("");
				return EXIT_FAILURE;
			}*/

			colors[std::string("Violet")] = new graphics::Color(VIOLET);
			colors[std::string("Blue")] = new graphics::Color(BLUE);
			colors[std::string("Green")] = new graphics::Color(GREEN);

			//graphics::Animation * animation = new graphics::Animation(graphics::SCALE_ANIMATION, graphics::DECREASE);
			//animation->do_after = move_up;
			//std::cout << "* progress: " << animation->progress << std::endl;
			//animations["Scale"] = animation;
			// move this logic to Level class
			//game.add_field("Field", 10, 10);
			//game.add_view("View", "Field");
			//std::cout << (engine::Point(0, 0) < engine::Point(0, 1)) << std::endl;
			//game.fields[std::string("Field")] = new engine::Field(10, 10);
			fields["Field"] = new Field();
			fields["Field"]->size = engine::Size(10, 10);

			views["View"] = new engine::View(fields[std::string("Field")]);
			views["View"]->size     = engine::Size(12, 12);
			views["View"]->offset   = engine::Point(-1, -1);
			views["View"]->position = engine::Point(3, 3);

			//const char * shape_names [2] = ["a", "b"];
			//engine::Object aaa();
			//engine::Object bbb(aaa);

			/*shapes[std::string("Square")] = new graphics::Square();
			shapes[std::string("Circle")] = new graphics::Circle();
			shapes[std::string("David")] = new graphics::David();/**/
			graphics::Shape * sokoban_shape =  new graphics::Star();
			shapes[std::string("SokobanShape")] = sokoban_shape;
			shapes[std::string("Ring")] = new graphics::Ring();

			engine::Object * box;
			box = new engine::Object();
			box->color = colors[std::string("Green")];
			box->kind = "Box";
			objects[std::string("Box1")] = box;
			box = new engine::Object();
			box->color = colors[std::string("Green")];
			box->kind = "Box";
			objects[std::string("Box2")] = box;
			engine::Object * heavy = new engine::Object();
			heavy->color = colors[std::string("Blue")];
			heavy->kind = "Heavy";
			objects[std::string("Heavy")] = heavy;
			//game.objects[std::string("Box2")] = new engine::Object();
			/*game.objects[std::string("Box1")]->type = std::string("Box");
			game.objects[std::string("Box2")]->type = std::string("Box");*/

			engine::Object * sokoban = new engine::Object();
			sokoban->shape = sokoban_shape;
			sokoban->color = colors[std::string("Violet")];
			sokoban->kind = "Sokoban";
			//sokoban->animations.push_back(animation);
			objects[std::string("Sokoban")] = sokoban;

			fields[std::string("Field")]->data.add(objects[std::string("Sokoban")], engine::Point(1, 1));

			interactions[engine::PairOfKinds(std::string("Sokoban"), std::string("Box"))] = engine::PUSH_INTERACTION;
			interactions[engine::PairOfKinds(std::string("Sokoban"), std::string("Heavy"))] = engine::PUSH_INTERACTION;
			interactions[engine::PairOfKinds(std::string("Heavy"), std::string("Box"))] = engine::PUSH_INTERACTION;

			fields[std::string("Field")]->data.add(objects[std::string("Box1")], engine::Point(5, 5));
			fields[std::string("Field")]->data.add(objects[std::string("Box2")], engine::Point(6, 5));
			fields[std::string("Field")]->data.add(objects[std::string("Heavy")], engine::Point(4, 3));

			//game.points[ engine::Placement(game.objects[std::string("Sokoban")], game.fields[std::string("Field")]) ] = new engine::Point(1, 1);
			//game.points[ engine::Placement(game.objects[std::string("Box1")], game.fields[std::string("Field")]) ] = new engine::Point(2, 2);
			//game.points[ engine::Placement(game.objects[std::string("Box2")], game.fields[std::string("Field")]) ] = new engine::Point(3, 3);

			/*for(engine::PointMap::iterator i = game.points.begin(); i != game.points.end(); ++i) {
				std::cout << *(i->first.object) << " at " << *(i->first.field) << " : ";
				if(i->second != NULL) {
					std::cout << *(i->second) << std::endl;
				} else {
					std::cout << "no position" << std::endl;
				}
			}
			std::cout << std::ends;*/

			//std::count << (&(game.points[ engine::Placement(game.objects[std::string("Sokoban")], game.fields[std::string("Field")]) ]) == NULL);

			if(current_level == levels.begin()) ++current_level;
			if(current_level != levels.end()) {
				current_level->load();
			} else {
				// game is over
			}
		}

		#define GET_COMPONENT(_Type, _component)\
		_Type##Pointer get_##_component(std::string _name) {\
			_Type##Pointer result = NULL;\
			if(_component##s.find(_name) != _component##s.end()) {\
				result = _component##s[_name];\
			}\
			return result;\
		}

		#define ADD_COMPONENT(_Type, _component)\
		_Type##Pointer add_##_component(std::string _name) {\
			_Type##Pointer result = NULL;\
			if(_get_##_component != NULL) {\
				result = new _Type();\
				_component##s[_name] = result;\
			}\
			return result;\
		}

		GET_COMPONENT(Field,  field);
		GET_COMPONENT(View,   view);
		GET_COMPONENT(Object, object);

		GET_COMPONENT(graphics::Color, color);
		GET_COMPONENT(graphics::Shape, shape);

		/*FieldPointer get_field(std::string _name) {
			FieldPointer result = NULL;
			if(fields.find(_name) != fields.end()) {
				result = fields[_name];
			}
			return result;
		}*/

		/*FieldPointer add_field(std::string _name) {
			FieldPointer result = NULL;
			if(get_field(_name) != NULL) {
				result = new Field();
				fields[_name] = result;
			}
			return result;
		}*/

		void remove_field(std::string _name) {
			FieldPointer field = get_field(_name);
			if(field != NULL) {
				delete field;
			}
			fields.erase(_name);
		}


		/*FieldPointer field(const char * _name) {
			field(std::string(_name));
		}*/

		/**FieldPointer field(std::string _name) {
			if(fields.find(_name) != fields.end()) {
				return fields[_name];
			} else {
				FieldPointer new_field = new Field;
				fields[_name] = new_field;
				return new_field;
			}
		}*/
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

//< KeyType, _ResultType >

		/*template<typename ResultType> ResultType get(std::string _name, typename Mapping<ResultType>::Pointer _component) {
			ResultType result;
			if(_component != NULL) { // make fetch
				if(_component->find(_name) != _component->end()) {
					result = (*_component)[_name];
				}
			}
			return result;
		}*/

		/*FieldPointer get_field(std::string _name) {
			return get<FieldPointer>(_name, &fields);
		}*/

		/*FieldPointer add_field(std::string _name) { }*/

		// make this one private
		//std::map<KeyType, ResultType> *
		//(typename Mapping<ResultType>::Pointer)
		/*template<typename ResultType> struct Component {
			typedef typename Mapping<ResultType>::Pointer ResultTypeMappingPointer;
			template<ResultType> static ResultTypeMappingPointer get() {
				// throw an exception here!!! unknown component!
				return NULL;
			}
		};*/

		/*template<typename ResultType> std::map<KeyType, ResultType> * component_by_type() {
			// throw an exception here!!! unknown component!
			return NULL;
		}

		template<typename ResultType> ResultType get(std::string _name) {
			//typename Mapping<ResultType>::Pointer component = Component<ResultType>::get();
			typename Mapping<ResultType>::Pointer component = component_by_type<ResultType>();
			ResultType result;
			if(component != NULL && component->find(_name) != component->end()) {
				result = (*component)[_name];
			}
			return result;
		}*/

		/*template<typename ResultType> ResultType add(std::string _name) {
			typename Mapping<ResultType>::Pointer component = component_by_type<ResultType>();
		}*/

	};

	/*template<> FieldMapPointer Game::Component<FieldMapPointer>::get() {
		return & fields;
	}*/

	/*template<> FieldMapPointer Game::component_by_type () {
		return & fields;
	}
	template<> ViewMapPointer Game::component_by_type () {
		return & views;
	}
	template<> ObjectMapPointer Game::component_by_type () {
		return & objects;
	}
	template<> ColorMapPointer Game::component_by_type () {
		return & colors;
	}
	template<> ShapeMapPointer Game::component_by_type () {
		return & shapes;
	}*/

	/*#
	define _FIELD_COMPONENT_ACCESSOR(TYPE) 1
	*/

}


#endif
