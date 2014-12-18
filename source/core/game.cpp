#include "game.hpp"

#include "point.hpp"
#include "emitter.hpp"
#include "library.hpp"

#include "drawing.hpp"

Game::Game() : kind(NO_GAME), paused(false), loaded(false) {
	screen_size.width = 50;
	screen_size.height = 5;
}

void Game::pause() {
	paused = true;
}

void Game::resume() {
	paused = false;
}

void Game::handle(unsigned char key, int special_key) {
	if(!paused) {
		Point position;
		Point offset;
		std::string string_key = to_string(key);
		/*if(controls.has(string_key)) {
			controls[string_key]->evaluate();
		} else {
			std::cout << " ~ free";
		}*/

		//graphics::ANIMATION_TYPE animation_type = graphics::NO_ANIMATION;
		//glutPostRedisplay();
	}
	//std::cout << std::endl;

	/*if(!paused) {
		engine::Field * field = fields[std::string("Field")];
		engine::Object * sokoban = objects[std::string("Sokoban")];
		switch(key)
		{
			case GLUT_KEY_UP:    step = engine::Point( 0,  1); break;
			case GLUT_KEY_DOWN:  step = engine::Point( 0, -1); break;
			case GLUT_KEY_LEFT:  step = engine::Point(-1,  0); break;
			case GLUT_KEY_RIGHT: step = engine::Point( 1,  0); break;
		}
		//animations["Scale"]->do_after = move_sokoban;
		//animations["Scale"]->start();
		//, animations[std::string("Scale")]
		//sokoban->move(field, step);
		//sokoban->move(field, step);
		//std::cout << "Key: " << key << std::endl;
		//glutPostRedisplay();
		printf("%i", key);
		std::cout << std::endl;
	}*/
}

void Game::print() {
	/*std::cout << "Object kinds:\n" << object_kinds << std::endl;
	std::cout << "Interactions:\n";
	for(InteractionMapIterator i = interactions.begin(); i != interactions.end(); ++i) {
		std::cout << i->first.first << " can " << i->second << " " << i->first.second << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Fields:\n" << fields << std::endl;
	std::cout << "Objects:\n" << objects << std::endl;
	std::cout << "Fields:\n" << fields << std::endl;
	std::cout << "Views:\n" << views << std::endl;
	std::cout << "Colors:\n" << colors << std::endl;
	std::cout << "Shapes:\n" << shapes << std::endl;
	std::cout << "Animations:\n" << animations << std::endl;
	std::cout << "Controls:\n" << controls << std::endl;*/
}

void Game::display() {

	draw_text(to_string(kind));

	/*for(graphics::AnimationMapping::Iterator i = animations.begin(); i != animations.end(); ++i) {
		i->second->next();
	}*/
	//graphics::write(lib::to_string(kind));
	/*glPushMatrix();
		for(ViewMapping::Iterator view = views.begin(); view != views.end(); ++view) {
			view->second->display();
		}
	glPopMatrix();*/
}

// Loads one property via mapping manager
//
/*template<typename Type>
void Game::load_attribute(Type & attribute, const YAML::Node & level, const char * key) {
	if(level[key]) {
		const YAML::Node & node = level[key];
		if(node.IsMap()) {
			for(YAML::const_iterator iterator = node.begin(); iterator != node.end(); ++iterator) {
				iterator >> attribute;
			}
		} else {
			std::cout << key << " should be a map" << std::endl;
		}
	} else {
		std::cout << "no " << key << " found" << std::endl;
	}
}*/

template<typename AttributeType>
int Game::load_attribute(AttributeType & attribute, const YAML::Node & config, const char * key) {
	std::cout << "  " << key << ": " << std::ends;
	if(config[key]) {
		try {
			attribute = config[key].as<AttributeType>();
			std::cout << "ok" << std::ends;
		} catch(YAML::TypedBadConversion<AttributeType> & exception) {
			std::cout << "wrong value" << std::endl;
			return 2;
		}
	} else {
		std::cout << "default" << std::endl;
		return 1;
	}
	std::cout << " - " << attribute << std::endl;
	return 0;
}


void Game::load_default_colors() {
/*
	colors.add( std::string( "black" ),       new graphics::Color( BLACK ) );
	colors.add( std::string( "white" ),       new graphics::Color( WHITE ) );
	colors.add( std::string( "gray" ),        new graphics::Color( GRAY ) );
	colors.add( std::string( "blue" ),        new graphics::Color( BLUE ) );
	colors.add( std::string( "yellow" ),      new graphics::Color( YELLOW ) );
	colors.add( std::string( "green" ),       new graphics::Color( GREEN ) );
	colors.add( std::string( "red" ),         new graphics::Color( RED ) );
	colors.add( std::string( "violet" ),      new graphics::Color( VIOLET ) );
	colors.add( std::string( "azure" ),       new graphics::Color( AZURE ) );
	colors.add( std::string( "orange" ),      new graphics::Color( ORANGE ) );
	colors.add( std::string( "soft_blue" ),   new graphics::Color( SOFT_BLUE ) );
	colors.add( std::string( "soft_yellow" ), new graphics::Color( SOFT_YELLOW ) );
	colors.add( std::string( "soft_green" ),  new graphics::Color( SOFT_GREEN ) );
	colors.add( std::string( "soft_red" ),    new graphics::Color( SOFT_RED ) );
	colors.add( std::string( "soft_violet" ), new graphics::Color( SOFT_VIOLET ) );
	colors.add( std::string( "light_gray" ),  new graphics::Color( LIGHT_GRAY ) );
	colors.add( std::string( "dark_violet" ), new graphics::Color( DARK_VIOLET ) );
	colors.add( std::string( "dark_gray" ),   new graphics::Color( DARK_GRAY ) );
*/
}

void Game::load_default_shapes() {
/*
	shapes.add(std::string("square"), new graphics::Square());
	shapes.add(std::string("circle"), new graphics::Circle());
	shapes.add(std::string("david"),  new graphics::David());
	shapes.add(std::string("star"),   new graphics::Star());
	shapes.add(std::string("ring"),   new graphics::Ring());
	shapes.add(std::string("retro"),  new graphics::Retro());
	shapes.add(std::string("diamond"), new graphics::NGon(4, 1));
	shapes.add(std::string("octagon"), new graphics::NGon(8, 2));
*/
}

bool Game::unload() {
/*
	fields.clear();
	views.clear();
	colors.clear();
	shapes.clear();
	object_kinds.clear();
	objects.clear();
	//animations.clear();
	//controls.clear();

	interactions.clear();
*/
	paused = false;
	loaded = false;
	return true;
}

int Game::load_attributes(const YAML::Node & level) {
	int result = 0;

	//result |= load_attribute(colors, level, "colors");
	//result |= load_attribute(shapes, level, "shapes");
	//result |= load_attribute(object_kinds, level, "object_kinds");
	//result |= load_interactions(level);
	//result |= load_attribute(interactions, level, "interactions");
	//result |= load_objects(level);

	//result |= load_attribute(fields, level, "fields");
	//result |= load_attribute(views, level, "views");
	//result |= load_attribute(controls, level, "controls");

	//load_game_options(level);

	return result;
}

// Loads all properties
//
bool Game::load(GAME_KIND game_kind, const std::string & level_path) {

	if(loaded) {
		unload();
	}

	std::cout << "Game loading:" << std::endl;

	//load_default_colors();
	//load_default_shapes();

	try {
		YAML::Node level = YAML::LoadFile(level_path.c_str());
		if(level.IsMap()) {

			std::cout << "Loading level data" << std::endl;
			/*for(YAML::const_iterator block = level.begin(); block != level.end(); ++block) {
				std::cout << block->first.as<std::string>() << std::endl;
			}
			std::cout << std::endl;*/
			load_attributes(level);

			loaded = true;

			//std::cout << "Game is loaded" << std::endl;
			//lib::stage("PLAYING");
			print();

		} else {
			std::cout << "Level file should contain mapping" << std::endl;
		}
	} catch (YAML::ParserException & exception) {
		std::cout << "syntax errors" << std::endl;
		return 4;
	} catch (YAML::BadFile) {
		std::cout << "config file does not exist or corrupted" << std::endl;
		return 5;
	}

	loaded = true;
	std::cout << "done" << std::endl;

	if(!loaded) {
		unload();
	}

	return loaded;

} // load()

// TODO: refactor it
//void Game::load_interactions(const YAML::Node & level) {
/*	const YAML::Node & interactions_node = level["interactions"];
	if(interactions_node) {
		if(interactions_node.IsMap()) {
			for(
				YAML::const_iterator
				interaction = interactions_node.begin();
				interaction != interactions_node.end();
				++interaction
			) {
				std::string first_object_kind_name = interaction->first.as<std::string>();
				//std::cout << "* " << first_object_kind_name << std::endl;
				if( object_kinds.has(first_object_kind_name) ) {
					ObjectKindPointer first_object_kind = object_kinds.get(first_object_kind_name);
					const YAML::Node& actions_node = interaction->second;
					if(actions_node.IsMap()) {
						for(
							YAML::const_iterator
							action = actions_node.begin();
							action != actions_node.end();
							++action
						) {
							std::string action_name = action->first.as<std::string>();
							INTERACTION_TYPE interaction_type = get_interaction_type(action_name);
							if(interaction_type != NO_INTERACTION) {
								const YAML::Node& second_object_kinds = action->second;
								if(second_object_kinds.IsScalar()) {
									std::string second_object_kind_name = second_object_kinds.as<std::string>();
									if(object_kinds.has(second_object_kind_name)) {
										ObjectKindPointer second_object_kind = object_kinds.get(second_object_kind_name);
										interactions[engine::PairOfKinds(first_object_kind, second_object_kind)] = interaction_type;
									} else {
										std::cout << "Can not find object kind `" << second_object_kind_name << "`" << std::endl;
									}
								}
								if(second_object_kinds.IsSequence()) {
									for(
										YAML::const_iterator
										second_object_kind_iterator = second_object_kinds.begin();
										second_object_kind_iterator != second_object_kinds.end();
										++second_object_kind_iterator
									) {
										std::string second_object_kind_name = second_object_kind_iterator->as<std::string>();
										if(object_kinds.has(second_object_kind_name)) {
											ObjectKindPointer second_object_kind = object_kinds.get(second_object_kind_name);
											interactions[engine::PairOfKinds(first_object_kind, second_object_kind)] = interaction_type;
										} else {
											std::cout << "Can not find object kind `" << second_object_kind_name << "`" << std::endl;
										}
									}
								}
							} else {
								std::cout << "No interaction" << std::endl;
							}
						}
					} else {
						std::cout << "Actions should be a map" << std::endl;
					}
				} else {
					std::cout << "Can not find object kind `" << first_object_kind_name << "`" << std::endl;
				}
			}
		} else {
			std::cout << "Interaction should be a map" << std::endl;
		}
	}*/
//}

// TODO: use specialization for mapping operator >> and put this code there
// drop this function and use load_attribute instead
void Game::load_objects(const YAML::Node & level) {

/*	const YAML::Node & objects_node = level["objects"];
	if(objects_node) {
		if(objects_node.IsMap()) {
			for(
				YAML::const_iterator
				object_kind_iterator = objects_node.begin();
				object_kind_iterator != objects_node.end();
				++object_kind_iterator
			) {
				std::string object_kind_name = object_kind_iterator->first.as<std::string>();
				if(object_kinds.has(object_kind_name)) {
					ObjectKindPointer object_kind = object_kinds.get(object_kind_name);
					const YAML::Node & object_names_node = object_kind_iterator->second;
					if(object_names_node.IsScalar()) {
						std::string object_name = object_names_node.as<std::string>();
						ObjectPointer object = objects.add(object_name);
						if(object != NULL) {
							object->kind = object_kind;
						}
						//TODO: use >> operator here
					}
					if(object_names_node.IsSequence()) {
						for(
							YAML::const_iterator
							object_iterator = object_names_node.begin();
							object_iterator != object_names_node.end();
							++object_iterator
						) {
							std::string object_name = object_iterator->as<std::string>();
							ObjectPointer object = objects.add(object_name);
							if(object != NULL) {
								object->kind = object_kind;
								//object->color
							}
						}
					}
				} else {
					std::cout << "No object kind" << std::endl;
				}
			}
		} else {
			std::cout << "Objects node should be a map" << std::endl;
		}
	}*/
}

void Game::load_game_options(const YAML::Node & level) {
/*
	if(level["game"]) {
		const YAML::Node & game_options = level["game"];
		if(game_options["screen"]) {
			game_options["screen"] >> screen_size;
		}
	}
*/
}
