#include "planet3d.h"

Planet3d::Planet3d(SolarSystemHeavenlyBody *solarSystemHeavenlyBody, const float keplerConstant)
    : HeavenlyBody3d(solarSystemHeavenlyBody->getHeavenlyBody())
{
    orbitAngle = solarSystemHeavenlyBody->getAngle();
    a = solarSystemHeavenlyBody->getSemimajorAxis();
    epsilon = solarSystemHeavenlyBody->getNumericExcentricity();

    setKeplerConstant(keplerConstant);

    orbit3d = new Orbit3d(orbitAngle, color);

    init();
    setOrbitVisisble(true);
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

    // Umfang der Ellipse nach Ramanujan
    float lambda = ( a - b ) / ( a + b );
    float circumstance = ( a + b ) * M_PI * ( 1 + 3 * lambda * lambda / ( 10 + sqrt( 4 - 3 * lambda * lambda )));

    // Durchschnittsgeschwindigkeit bestimmen
    averageSpeed = circumstance / circumstanceTime;

    // Mittlere Winkelgeschwindigkeit
    float omega_m = 2 * M_PI / circumstanceTime;

    // Geschwindigkeit im Aphel
    float speed_aphel = omega_m * a * sqrt(( a - e ) / ( a + e ));

    // Geschwindigkeit im Perihel
    float speed_perihel = omega_m * a * sqrt(( a + e ) / ( a - e ));

    phi = 0.0;
    pointsCounter = 0;

    // My = Gravitationskonstante * Masse
    float my_a = speed_aphel * speed_aphel * (a + e) * a / ( a - e );
    float my_p = speed_perihel * speed_perihel * (a - e) * a / ( a + e );
    my = ( my_a + my_p ) / 2;
    qDebug() << my_a << "     " << my_p << "     " << my << "     ";
}

void Planet3d::calculateHeavenlyBody3d()
{
    x = cos(phi) * a + e;
    y = sin(phi) * b;

    // Betrag des Vektors vom Brennpunk zum Planeten
    float r = sqrt( x * x + y * y);

    // Momentangeschwindigkeit des Planeten nach der Vis-Viva-Gleichung
    float instantaneousVelocity = sqrt( my * ( 2 / r - 1 / a ));

    // Mit einem Dreisatz den zu ueberschreitenden Winkel bestimmen:
    // alpha / øalpha ~ v / øv
    float orbitPointsCount = circumstanceTime;
    double averageAngle = 2 * M_PI / orbitPointsCount;
    double alpha = averageAngle * instantaneousVelocity / averageSpeed;

    phi += alpha;
    if ( pointsCounter == (int) orbitPointsCount / 2)
    {
        phi = M_PI;
    }
    if ( pointsCounter > orbitPointsCount)
    {
        phi = 0;
        pointsCounter = 0;
    }
    pointsCounter++;
}

void Planet3d::paintHeavenlyBody3d()
{
    glPushMatrix();

    glRotatef(orbitAngle, 0.0, 0.0, 1.0);
    glTranslated(x , y, 0.0);

    HeavenlyBody3d::paintHeavenlyBody3d();

    glPopMatrix();

    if (isOrbitVisisble())
    {
        orbit3d->paintOrbit3d(a, b, e);
    }
}
