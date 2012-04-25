#include "heavenlybody3d.h"

HeavenlyBody3d::HeavenlyBody3d(HeavenlyBody *heavenlyBody)
{
    name = heavenlyBody->getName();

    color = GLColorRGBA(heavenlyBody->getColor().redF(),
                        heavenlyBody->getColor().greenF(),
                        heavenlyBody->getColor().blueF(),
                        heavenlyBody->getColor().alphaF());

    radius = GLdouble((heavenlyBody->getDiameter() / 2.0) / 3000.0);

    x = 0;
    y = 0;
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

double HeavenlyBody3d::getRadius()
{
    return radius;
}

GLVector HeavenlyBody3d::getCenter()
{
    return heavenlyBodyCenter;
}

QString HeavenlyBody3d::getName()
{
    return name;
}

double HeavenlyBody3d::calculateDistance(HeavenlyBody3d *heavenlyBody3d)
{
    double x = pow(heavenlyBody3d->getCenter().x() - getCenter().x(), 2);
    double y = pow(heavenlyBody3d->getCenter().y() - getCenter().y(), 2);
    double z = pow(heavenlyBody3d->getCenter().z() - getCenter().z(), 2);

    return sqrt(x + y + z);
}
