#include "game.hpp"
#include "point.hpp"
#include "library.hpp"
//#include "game/load.h"

Game::Game():
	kind(NO_GAME), paused(false), loaded(false)
{}

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
