#include "MyContactListener.h"
#include <iostream>

MyContactListener::MyContactListener(Pelota& pel, Arco& arc1, Arco& arc2, Jugador& jug1, Jugador& jug2, bool& golA, bool& golB, sf::Clock& clock, Hielo& hielo, sf::Clock& hieloClock1, sf::Clock& hieloClock2, bool& hieloJ1, bool& hieloJ2, Bomba& bomba, sf::Clock& bombaClock1, sf::Clock& bombaClock2, bool& bombaJ1, bool& bombaJ2, Aumentador& aumentador, sf::Clock& aumClock1, sf::Clock& aumClock2, bool& aumJ1, bool& aumJ2)
{
    _pelota = &pel;
    _arco1 = &arc1;
    _arco2 = &arc2;
    _jugador1 = &jug1;
    _jugador2 = &jug2;
    _hielo = &hielo;
    _bomba = &bomba;
    _aum = &aumentador;

    arcA_aux = nullptr;
    arcB_aux = nullptr;
    pelota_aux = nullptr;
    jug1_aux = nullptr;
    jug2_aux = nullptr;
    hielo_aux = nullptr;
    bomba_aux = nullptr;
    aum_aux = nullptr;

    _clock = &clock;
    _hieloClock1 = &hieloClock1;
    _hieloClock2 = &hieloClock2;
    _bombaClock1 = &bombaClock1;
    _bombaClocK2 = &bombaClock2;
    _aumClock1 = &aumClock1;
    _aumClock2 = &aumClock2;

    esGolA = &golA;
    esGolB = &golB;
    hieloJug1 = &hieloJ1;
    hieloJug2 = &hieloJ2;
    bombaJug1 = &bombaJ1;
    bombaJug2 = &bombaJ2;
    aumJug1 = &aumJ1;
    aumJug2 = &aumJ2;

}

void MyContactListener::createContact(Pelota& pel, Arco& arc1, Arco& arc2, Jugador& jug1, Jugador& jug2, bool& golA, bool& golB, sf::Clock& clock, Hielo& hielo, sf::Clock& hieloClock1, sf::Clock& hieloClock2, bool& hieloJ1, bool& hieloJ2, Bomba& bomba, sf::Clock& bombaClock1, sf::Clock& bombaClock2, bool& bombaJ1, bool& bombaJ2, Aumentador& aumentador, sf::Clock& aumClock1, sf::Clock& aumClock2, bool& aumJ1, bool& aumJ2)
{
    _pelota = &pel;
    _arco1 = &arc1;
    _arco2 = &arc2;
    _jugador1 = &jug1;
    _jugador2 = &jug2;
    _hielo = &hielo;
    _bomba = &bomba;
    _aum = &aumentador;

    arcA_aux = nullptr;
    arcB_aux = nullptr;
    pelota_aux = nullptr;
    jug1_aux = nullptr;
    jug2_aux = nullptr;
    hielo_aux = nullptr;
    bomba_aux = nullptr;
    aum_aux = nullptr;

    _clock = &clock;
    _hieloClock1 = &hieloClock1;
    _hieloClock2 = &hieloClock2;
    _bombaClock1 = &bombaClock1;
    _bombaClocK2 = &bombaClock2;
    _aumClock1 = &aumClock1;
    _aumClock2 = &aumClock2;

    esGolA = &golA;
    esGolB = &golB;
    hieloJug1 = &hieloJ1;
    hieloJug2 = &hieloJ2;
    bombaJug1 = &bombaJ1;
    bombaJug2 = &bombaJ2;
    aumJug1 = &aumJ1;
    aumJug2 = &aumJ2;
}


void MyContactListener::BeginContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    b2Body* bodyA = fixtureA->GetBody();
    b2Body* bodyB = fixtureB->GetBody();
           
    arcA_aux = nullptr;
    arcB_aux = nullptr;
    pelota_aux = nullptr;
    jug1_aux = nullptr;
    jug2_aux = nullptr;
    hielo_aux = nullptr;
    bomba_aux = nullptr;
    aum_aux = nullptr;

    if (_arco1 == reinterpret_cast<Arco*>(bodyA->GetUserData().pointer)) {
        arcA_aux = reinterpret_cast<Arco*>(bodyA->GetUserData().pointer);
    }

    if (_arco2 == reinterpret_cast<Arco*>(bodyA->GetUserData().pointer)) {
        arcB_aux = reinterpret_cast<Arco*>(bodyA->GetUserData().pointer);
    }
    if (_pelota == reinterpret_cast<Pelota*>(bodyA->GetUserData().pointer)) {
        pelota_aux = reinterpret_cast<Pelota*>(bodyA->GetUserData().pointer);
    }
    if (_jugador1 == reinterpret_cast<Jugador*>(bodyA->GetUserData().pointer)) {
        jug1_aux = reinterpret_cast<Jugador*>(bodyA->GetUserData().pointer);
    }
    if (_jugador2 == reinterpret_cast<Jugador*>(bodyA->GetUserData().pointer)) {
        jug2_aux = reinterpret_cast<Jugador*>(bodyA->GetUserData().pointer);
    }
    if (_hielo == reinterpret_cast<Hielo*>(bodyA->GetUserData().pointer)) {
        hielo_aux = reinterpret_cast<Hielo*>(bodyA->GetUserData().pointer);
    }
    if (_bomba == reinterpret_cast<Bomba*>(bodyA->GetUserData().pointer)) {
        bomba_aux = reinterpret_cast<Bomba*>(bodyA->GetUserData().pointer);
    }
    if (_aum == reinterpret_cast<Aumentador*>(bodyA->GetUserData().pointer)) {
        aum_aux = reinterpret_cast<Aumentador*>(bodyA->GetUserData().pointer);
    }
    

    if (_arco1 == reinterpret_cast<Arco*>(bodyB->GetUserData().pointer)) {
        arcA_aux = reinterpret_cast<Arco*>(bodyB->GetUserData().pointer);
    }
    if (_arco2 == reinterpret_cast<Arco*>(bodyB->GetUserData().pointer)) {
        arcB_aux = reinterpret_cast<Arco*>(bodyB->GetUserData().pointer);
    }
    if (_pelota == reinterpret_cast<Pelota*>(bodyB->GetUserData().pointer)) {
        pelota_aux = reinterpret_cast<Pelota*>(bodyB->GetUserData().pointer);
    }
    if (_jugador1 == reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer)) {
        jug1_aux = reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer);
    }
    if (_jugador2 == reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer)) {
        jug2_aux = reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer);
    }
    if (_hielo == reinterpret_cast<Hielo*>(bodyB->GetUserData().pointer)) {
        hielo_aux = reinterpret_cast<Hielo*>(bodyB->GetUserData().pointer);
    }
    if (_bomba == reinterpret_cast<Bomba*>(bodyB->GetUserData().pointer)) {
        bomba_aux = reinterpret_cast<Bomba*>(bodyB->GetUserData().pointer);
    }
    if (_aum == reinterpret_cast<Aumentador*>(bodyB->GetUserData().pointer)) {
        aum_aux = reinterpret_cast<Aumentador*>(bodyB->GetUserData().pointer);
    }
 
    
    if (arcA_aux!=nullptr && pelota_aux!=nullptr) {
        *esGolA = true;
        if (*esGolB == true) {
            *esGolA = false;
        }
        _clock->restart();
    }

    if (arcB_aux != nullptr && pelota_aux != nullptr) {
        *esGolB = true;
        if (*esGolA == true) {
            *esGolB = false;
        }
        _clock->restart();
    }

    if (jug1_aux != nullptr && pelota_aux != nullptr && _jugador1->isKicking()==true) {
        if (_pelota->getBody()->GetPosition().x >_jugador1->getBody()->GetPosition().x) {
            b2Vec2 impulso = PixelToWorld(sf::Vector2f(80, 100));
            _pelota->getBody()->ApplyLinearImpulseToCenter(impulso, true);
        } 
    }
    if (jug2_aux != nullptr && pelota_aux != nullptr && _jugador2->isKicking() == true) {
        if (_pelota->getBody()->GetPosition().x < _jugador2->getBody()->GetPosition().x) {
            b2Vec2 impulso = PixelToWorld(sf::Vector2f(-80, 100));
            _pelota->getBody()->ApplyLinearImpulseToCenter(impulso, true);
        }
    }
    
    if (jug1_aux != nullptr && jug2_aux != nullptr)
    {
        fixtureA->SetFriction(0.0f);
        fixtureB->SetFriction(0.0f);               
    }

        if (hielo_aux != nullptr && jug1_aux != nullptr){
           *hieloJug1 = true;
           _hieloClock1->restart();
        }

        if (hielo_aux != nullptr && jug2_aux != nullptr) {
            *hieloJug2 = true;
            _hieloClock2->restart();
        }        

        if (bomba_aux != nullptr && jug1_aux != nullptr) {
            *bombaJug1 = true;
            _bombaClock1->restart();
        }
        if (bomba_aux != nullptr && jug2_aux != nullptr) {
            *bombaJug2 = true;
            _bombaClocK2->restart();
        }

        if (aum_aux != nullptr && jug1_aux != nullptr) {
            *aumJug1 = true;
            _aumClock1->restart();
        }

        if (aum_aux != nullptr && jug2_aux != nullptr) {
            *aumJug2 = true;
            _aumClock2->restart();
        }

}


void MyContactListener::EndContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    b2Body* bodyA = fixtureA->GetBody();
    b2Body* bodyB = fixtureB->GetBody();

    arcA_aux = nullptr;
    arcB_aux = nullptr;
    pelota_aux = nullptr;
    jug1_aux = nullptr;
    jug2_aux = nullptr;

    if (_arco1 == reinterpret_cast<Arco*>(bodyA->GetUserData().pointer)) {
        arcA_aux = reinterpret_cast<Arco*>(bodyA->GetUserData().pointer);
    }
    if (_arco2 == reinterpret_cast<Arco*>(bodyA->GetUserData().pointer)) {
        arcB_aux = reinterpret_cast<Arco*>(bodyA->GetUserData().pointer);
    }
    if (_pelota == reinterpret_cast<Pelota*>(bodyA->GetUserData().pointer)) {
        pelota_aux = reinterpret_cast<Pelota*>(bodyA->GetUserData().pointer);
    }
    if (_jugador1 == reinterpret_cast<Jugador*>(bodyA->GetUserData().pointer)) {
        jug1_aux = reinterpret_cast<Jugador*>(bodyA->GetUserData().pointer);
    }
    if (_jugador2 == reinterpret_cast<Jugador*>(bodyA->GetUserData().pointer)) {
        jug2_aux = reinterpret_cast<Jugador*>(bodyA->GetUserData().pointer);
    }


    if (_arco1 == reinterpret_cast<Arco*>(bodyB->GetUserData().pointer)) {
        arcA_aux = reinterpret_cast<Arco*>(bodyB->GetUserData().pointer);
    }
    if (_arco2 == reinterpret_cast<Arco*>(bodyB->GetUserData().pointer)) {
        arcB_aux = reinterpret_cast<Arco*>(bodyB->GetUserData().pointer);
    }
    if (_pelota == reinterpret_cast<Pelota*>(bodyB->GetUserData().pointer)) {
        pelota_aux = reinterpret_cast<Pelota*>(bodyB->GetUserData().pointer);
    }
    if (_jugador1 == reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer)) {
        jug1_aux = reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer);
    }
    if (_jugador2 == reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer)) {
        jug2_aux = reinterpret_cast<Jugador*>(bodyB->GetUserData().pointer);
    }
   
    if (jug1_aux != nullptr && jug2_aux != nullptr)
    {
        fixtureA->SetFriction(1.0f);
        fixtureB->SetFriction(1.0f);
       
    }

}

    
  
