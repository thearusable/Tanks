#ifndef ARUS_H
#define ARUS_H
#pragma once

namespace arus {
	enum class Direction {
		none,
		up,
		down,
		left,
		right,
	};
	enum class Textures {
		//map
		empty = 0,
		ice,
		grass,

		brick,
		steel,

		water,
		eagle,

		player11,
		player12,
		player21,
		player22,
		tankDestroy,
		spawn,
		enemyFast,
		enemyHeavy,
		enemyNormal,
		enemyRandom,
		tankMenu,
		logo,
		cursor,
		bullet,
		sBullet,
		bulletDestroy,
		flag,
		tankIcon,
		//
		swim,
		shield,
		//
		arrows,
		tanks,
		PTS,
		//
		granadePU,
		shieldPU,
		lifePU,
		pistolPU,
		swimPU,
		speedPU,
	};
	enum class Font {
		DisposableDroid,
	};
	enum class PowerUp {
		none = 6,
		granade = 0,
		shield = 1,
		life = 2,
		pistol = 3,
		swim = 4,
		speed = 5,
	};
	enum class bulletType {
		normal = 0,
		super = 1,
	};
	enum class EnemyType {
		random,
		normal,
		heavy,
		fast,
	};
	enum class STATE {
		STATE_PATROL = 0,
		STATE_ATAK = 1,
	};
	enum class EVENT_ID {
		ID_WIDAC_GRACZA = 101,
	};
}

#endif