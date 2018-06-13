//
// Created by NANAA on 13/06/18.
//

#ifndef INDIESTUDIO_RULECHECKERSYSTEM_HPP
#define INDIESTUDIO_RULECHECKERSYSTEM_HPP

#include <Interfaces/ISystem.hpp>
#include <GraphicalEngine.hpp>

class World;

namespace Systems {

	class RulesCheckerSystem : public ISystem {
	public:
		RulesCheckerSystem(GraphicalEngine *engine, int nbPlayers) : _nbPlayers(nbPlayers), _engine(engine) {};
		void execute(World *ref) override;

	private:
		int _nbPlayers;
		bool checkOnePlayer(World *ref);
		bool checkTwoPlayers(World *ref);
		GraphicalEngine *_engine;

	};
}

#endif //INDIESTUDIO_RULECHECKERSYSTEM_HPP
