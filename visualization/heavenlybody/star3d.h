#ifndef STAR3D_H
#define STAR3D_H

#include "visualization/heavenlybody/heavenlybody3d.h"
#include "model/heavenlybody/heavenlybody.h"

class Star3d : public HeavenlyBody3d
{
public:
    Star3d(HeavenlyBody *heavenlyBody);
};

#endif // STAR3D_H
