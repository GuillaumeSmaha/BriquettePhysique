#include "GestSnapShoot.h"

template<> GestSnapShoot * ClassRootSingleton<GestSnapShoot>::_instance = NULL;


GestSnapShoot::GestSnapShoot() : ClassRootSingleton<GestSnapShoot>()
{
    this->currentSnapShoot = -1;
}


GestSnapShoot::~GestSnapShoot()
{

}


void GestSnapShoot::addModification(SnapShoot * snapShoot)
{
    this->lstSnapShoot.push_back(snapShoot);
}

void GestSnapShoot::addModification(ObjBriquette * briquette)
{
}

void GestSnapShoot::undo()
{
}

void GestSnapShoot::undo(int numberModification)
{
}

void GestSnapShoot::undoAll()
{
}

void GestSnapShoot::redo()
{
}

void GestSnapShoot::redo(int numberModification)
{
}

void GestSnapShoot::redoAll()
{
}
