#pragma once
#include <box2d/box2d.h>
#include "Arco.h"
#include "Jugador.h"
#include "Pelota.h"
#include "Hielo.h"
#include "Bomba.h"
#include "Aumentador.h"
//cada vez que hay una colision entre dos objetos se llama a esta clase.
class MyContactListener: public b2ContactListener
{
private:
	Pelota* _pelota;
	Arco* _arco1;
	Arco* _arco2;
	Jugador* _jugador1;
	Jugador* _jugador2;
	Hielo* _hielo;
	Bomba* _bomba;
	Aumentador* _aum;

	Arco* arcA_aux;
	Arco* arcB_aux;
	Pelota* pelota_aux;
	Jugador* jug1_aux;
	Jugador* jug2_aux;
	Hielo* hielo_aux;
	Bomba* bomba_aux;
	Aumentador* aum_aux;

	bool* esGolA;
	bool* esGolB;
	bool* hieloJug1;
	bool* hieloJug2;
	bool* bombaJug1;
	bool* bombaJug2;
	bool* aumJug1;
	bool* aumJug2;

	sf::Clock* _clock;
	sf::Clock* _hieloClock1;
	sf::Clock* _hieloClock2;
	sf::Clock* _bombaClock1;
	sf::Clock* _bombaClocK2;
	sf::Clock* _aumClock1;
	sf::Clock* _aumClock2;

public:

	MyContactListener() {}
	MyContactListener(Pelota &pel, Arco &arc1, Arco &arc2, Jugador &jug1, Jugador &jug2, bool &golA, bool &golB, sf::Clock& clock, Hielo& hielo, sf::Clock& hieloClock1, sf::Clock& hieloClock2, bool &hieloJ1, bool &hieloJ2, Bomba &bomba, sf::Clock& bombaClock1, sf::Clock& bombaClock2, bool &bombaJ1, bool &bombaJ2, Aumentador &aumentador, sf::Clock &aumClock1, sf::Clock &aumClock2, bool &aumJ1, bool &aumJ2);
	void createContact(Pelota& pel, Arco& arc1, Arco& arc2, Jugador& jug1, Jugador& jug2, bool& golA, bool& golB, sf::Clock& clock, Hielo& hielo, sf::Clock& hieloClock1, sf::Clock& hieloClock2, bool& hieloJ1, bool& hieloJ2, Bomba& bomba, sf::Clock& bombaClock1, sf::Clock& bombaClock2, bool& bombaJ1, bool& bombaJ2, Aumentador& aumentador, sf::Clock& aumClock1, sf::Clock& aumClock2, bool& aumJ1, bool& aumJ2);
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact * contact);
	//void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);

	//void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
	
};


