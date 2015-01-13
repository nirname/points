#include "game.hpp"

#include "point.hpp"
#include "emitter.hpp"
#include "library.hpp"

#include "drawing.hpp"

#include "convert.hpp"
#include "emitter.hpp"
#include "yaml_adapter.hpp"
#include "functionals.hpp"

Game::Game(): kind(NO_GAME), paused(false), loaded(false) {
	screen_size.width = 10;
	screen_size.height = 10;
}

int Game::width() {
	return screen_size.width;
}

int Game::height() {
	return screen_size.height;
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
	std::cout << "Game:" << std::endl;
	/*std::cout << "Object kinds:\n" << object_kinds << std::endl;
	std::cout << "Interactions:\n";
	for(InteractionMapIterator i = interactions.begin(); i != interactions.end(); ++i) {
		std::cout << i->first.first << " can " << i->second << " " << i->first.second << std::endl;
	}
	std::cout << std::endl;*/

	std::cout << "  fields: " << fields << std::endl;
	/*std::cout << "  views: " << views << std::endl;
	std::cout << "  object kinds: " << object_kinds << std::endl;
	std::cout << "  objects: " << objects << std::endl;
	std::cout << "  colors: " << colors << std::endl;
	std::cout << "  shapes: " << shapes << std::endl;*/
	//std::cout << "  animations:\n" << animations << std::endl;
	//std::cout << "  controls:\n" << controls << std::endl;
}

void Game::display() {
	//draw_text(to_string(kind));
	/*for(graphics::AnimationMapping::Iterator i = animations.begin(); i != animations.end(); ++i) {
		i->second->next();
	}*/
	//graphics::write(lib::to_string(kind));
	glPushMatrix();
		for(ViewManager::Iterator view = views.begin(); view != views.end(); ++view) {
			view->second->display();
		}
	glPopMatrix();
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
	std::cout << "Game unloading: " << std::ends;

	fields.clear();
	views.clear();
	colors.clear();
	shapes.clear();
	object_kinds.clear();
	objects.clear();
	//animations.clear();
	//controls.clear();

	//interactions.clear();

	paused = false;
	loaded = false;

	std::cout << "done" << std::endl;
	return true;
}

int Game::load_defaults() {
	//load_default_colors();
	//load_default_shapes();
	return 0;
}

int Game::load_game_options(const YAML::Node & level) {
	int result = 0;
	if(level["game"]) {
		const YAML::Node & game_options = level["game"];
		if(game_options.IsMap() && game_options["screen"]) {
			result |= load_yaml_option(screen_size, game_options, "screen");
			//result |= load_yaml_option(kind, level, "game_kind");
		} else {
			result |= 1;
		}
	}
	return result;
}

int Game::load_attributes(const YAML::Node & level) {
	int result = 0;

	result |= load_game_options(level);

	result |= load_yaml_option(fields, level, "fields");
	result |= load_yaml_option(views, level, "views");
	result |= load_yaml_option(object_kinds, level, "object_kinds");
	result |= load_yaml_option(objects, level, "objects");
	result |= load_yaml_option(colors, level, "colors");
	//result |= load_yaml_option(shapes, level, "shapes");
	//result |= load_yaml_option(object_kinds, level, "object_kinds");
	//result |= load_objects(level);
	//result |= load_yaml_option(controls, level, "controls");

	return result;
}

// Loads all properties
//
bool Game::load(GAME_KIND game_kind, const std::string & level_path) {

	std::cout << "Loading game:" << std::endl;

	if(loaded) {
		// ask whether you want to stop current game
		unload();
	}

	if (
		load_defaults() == 0 &&
		load_yaml_file(level_path, bind<const YAML::Node &>(this, &Game::load_attributes)) == 0
	) {
		loaded = true;
		std::cout << "done" << std::endl;
		print();
	} else {
		unload();
		std::cout << "failed" << std::endl;
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
