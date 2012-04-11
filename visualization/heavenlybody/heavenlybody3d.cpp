#include "heavenlybody3d.h"

HeavenlyBody3d::HeavenlyBody3d(HeavenlyBody *heavenlyBody)
{
    color = GLColorRGBA(heavenlyBody->getColor().redF(),
                        heavenlyBody->getColor().greenF(),
                        heavenlyBody->getColor().blueF(),
                        heavenlyBody->getColor().alphaF());

    radius = GLdouble((heavenlyBody->getDiameter() / 2.0) / 3000.0);
}

void HeavenlyBody3d::paintHeavenlyBody3d()
{
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color.fv());
    glMateriali(GL_FRONT, GL_SHININESS, 100);

    glutSolidSphere(radius, 32, 32);
}

void HeavenlyBody3d::calculateHeavenlyBody3d()
{ }

void HeavenlyBody3d::setOrbitVisisble(bool orbitVisisble)
{
    this->orbitVisisble = orbitVisisble;
}

bool HeavenlyBody3d::isOrbitVisisble()
{
    return orbitVisisble;
}
