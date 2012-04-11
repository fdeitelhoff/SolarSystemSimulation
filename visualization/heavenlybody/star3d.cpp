#include "star3d.h"

Star3d::Star3d(HeavenlyBody *heavenlyBody)
    : HeavenlyBody3d(heavenlyBody)
{
}

void Star3d::paintHeavenlyBody3d()
{
    glDisable(GL_LIGHTING);

    glColor3f(color.red(), color.green(), color.blue());

    HeavenlyBody3d::paintHeavenlyBody3d();

    glEnable(GL_LIGHTING);
}
