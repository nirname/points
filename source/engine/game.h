#ifndef GAME_H
#define GAME_H 1

namespace engine {

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

			YAML::Node level_config = YAML::LoadFile("levels/qq.yaml");
			std::cout << (level_config["first"].as<std::string>()) << std::endl;

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
			field("Field")->size = engine::Size(10, 10);

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

		/*FieldPointer field(const char * _name) {
			field(std::string(_name));
		}*/
		FieldPointer field(std::string _name) {
			if(fields.find(_name) != fields.end()) {
				return fields[_name];
			} else {
				FieldPointer new_field = new Field;
				fields[_name] = new_field;
				return new_field;
			}
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
