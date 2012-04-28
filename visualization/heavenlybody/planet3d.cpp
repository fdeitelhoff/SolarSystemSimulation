#include "planet3d.h"

Planet3d::Planet3d(SolarSystemHeavenlyBody *solarSystemHeavenlyBody, const float keplerConstant)
    : HeavenlyBody3d(solarSystemHeavenlyBody->getHeavenlyBody())
{
    orbitAngle = solarSystemHeavenlyBody->getAngle();
    orbitalPlaneAngle = solarSystemHeavenlyBody->getOrbitalPlaneAngle();
    a = solarSystemHeavenlyBody->getSemimajorAxis();
    epsilon = solarSystemHeavenlyBody->getNumericExcentricity();

    setKeplerConstant(keplerConstant);

    init();    
}

Planet3d::~Planet3d()
{
    delete orbit3d;
}

void Planet3d::setKeplerConstant(const float keplerConstant)
{
    circumstanceTime = sqrt(keplerConstant * pow(a , 3));
}

void Planet3d::init()
{
    b = a * sqrt(1 - epsilon * epsilon );
    e = epsilon * a;

    // Periphery of the ellipse according to Ramanujan
    float lambda = ( a - b ) / ( a + b );
    float circumstance = ( a + b ) * M_PI * ( 1 + 3 * lambda * lambda / ( 10 + sqrt( 4 - 3 * lambda * lambda )));

    // Average speed of the planet
    averageSpeed = circumstance / circumstanceTime;

    // Average angular speed
    float omegaM = 2 * M_PI / circumstanceTime;

    // Speed in Aphelion
    float speedAphelion = omegaM * a * sqrt(( a - e ) / ( a + e ));

    // Speed in Perihelion
    float speedPerihelion = omegaM * a * sqrt(( a + e ) / ( a - e ));

    // mu = gravitation constant * mass
    float muA = speedAphelion * speedAphelion * (a + e) * a / ( a - e );
    float muP = speedPerihelion * speedPerihelion * (a - e) * a / ( a + e );
    mu = ( muA + muP ) / 2;

    orbit3d = new Orbit3d(orbitAngle, orbitalPlaneAngle, color, a, b, e);

    phi = 0.0;
    pointsCounter = 0;
}

void Planet3d::calculateHeavenlyBody3d()
{
    x = cos(phi) * a + e;
    y = sin(phi) * b;

    // Absolute value of the planet position vector
    float r = sqrt( x * x + y * y);

    // 	Instantaneous velocity of the planet according to the Vis-Viva-Equatation
    float instantaneousVelocity = sqrt( mu * ( 2 / r - 1 / a ));

    // Take a rule of three to calculate the transgrassing angle:
    // alpha / øalpha ~ v / øv
    float orbitPointsCount = circumstanceTime;
    double averageAngle = 2 * M_PI / orbitPointsCount;
    double alpha = averageAngle * instantaneousVelocity / averageSpeed;

    phi += alpha;
    if (pointsCounter == (int) orbitPointsCount / 2 + 2)
    {
        phi = M_PI;
    }
    if (pointsCounter > orbitPointsCount + 2)
    {
        phi = 0;
        pointsCounter = 0;
    }
    pointsCounter++;
}

void Planet3d::paintHeavenlyBody3d()
{
    glPushMatrix();

    glRotatef(orbitalPlaneAngle, 1.0, 0.0, 0.0);
    glRotatef(orbitAngle, 0.0, 0.0, 1.0);

    glTranslatef(x, y, 0);

    HeavenlyBody3d::paintHeavenlyBody3d();

    float matrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix);

    heavenlyBodyCenter = GLVector(matrix[12]/matrix[15], matrix[13]/matrix[15], matrix[14]/matrix[15]);

    glPopMatrix();

    if (isOrbitVisisble())
    {
        orbit3d->paintOrbit3d();
    }
}
