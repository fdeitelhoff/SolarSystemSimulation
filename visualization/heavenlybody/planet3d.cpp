#include "planet3d.h"

Planet3d::Planet3d(SolarSystemHeavenlyBody *solarSystemHeavenlyBody, const float keplerConstant)
    : HeavenlyBody3d(solarSystemHeavenlyBody->getHeavenlyBody())
{
    a = solarSystemHeavenlyBody->getSemimajorAxis();
    epsilon = solarSystemHeavenlyBody->getNumericExcentricity();

    setKeplerConstant(keplerConstant);

    orbit3d = new Orbit3d(color);

    init();
    setOrbitVisisble(true);
}

Planet3d::~Planet3d()
{
    delete orbit3d;
}

void Planet3d::setKeplerConstant(const float keplerConstant)
{
    circumstanceTime = sqrt(keplerConstant * pow(a * ((sqrt(1 - epsilon) + 1) / 2), 3));
}

void Planet3d::init()
{
    const float PI = M_PI; // 3.14159265358979323846 3.1415926535f;

    b = a * sqrt(1 - epsilon * epsilon );
    e = epsilon * a;

    // Umfang der Ellipse nach Ramanujan
    float lambda = ( a - b ) / ( a + b );
    float circumstance = ( a + b ) * PI * ( 1 + 3 * lambda * lambda / ( 10 + sqrt( 4 - 3 * lambda * lambda )));

    // Durchschnittsgeschwindigkeit bestimmen
    average_speed = circumstance / circumstanceTime;
    qDebug() << "Durchschnittsgeschwindigkeit: " << average_speed;

    // Mittlere Winkelgeschwindigkeit
    float omega_m = 2 * PI / circumstanceTime;

    // Geschwindigkeit im Aphel
    float speed_aphel = omega_m * a * sqrt(( a - e ) / ( a + e ));
    qDebug() << "Geschwindigkeit Aphel: " << speed_aphel;

    // Geschwindigkeit im Perihel
    float speed_perihel = omega_m * a * sqrt(( a + e ) / ( a - e ));
    qDebug() << "Geschwindigkeit Perihel: " << speed_perihel;
    qDebug() << "\n";

    phi = 0.0;

    // My = Gravitationskonstante * Masse
    my = speed_aphel * speed_aphel / ( 2 / ( a + e ) - 1 / a );
}

void Planet3d::paintHeavenlyBody3d()
{
    glPushMatrix();

    const float PI = 3.1415926535f; //M_PI; // 3.14159265358979323846

    float x = cos(phi) * a + e;
    float y = sin(phi) * b;

    // Betrag des Vektors vom Brennpunk zum Planeten
    float r = sqrt( x * x + y * y);

    // Momentangeschwindigkeit des Planeten nach der Vis-Viva-Gleichung
    float instantaneous_velocity = sqrt( my * ( 2 / r - 1 / a ));
    qDebug() << "Phi: " << phi * 360 / ( 2 * PI );
    qDebug() << "x = " << x << "    y = " << y << "    r = " << r << "   my = " << my;
    qDebug() << "Momentangeschwindigkeit: " << instantaneous_velocity;

    glRotatef(45.0, 0.0, 0.0, 1.0);
    glTranslated(x , y, 0.0);

    // Mit einem Dreisatz den zu ueberschreitenden Winkel bestimmen:
    // alpha / øalpha ~ v / øv
    float orbit_points_count = circumstanceTime;
    float average_angle = 2 * PI / orbit_points_count;
    float alpha = average_angle * instantaneous_velocity / average_speed;

    phi += alpha;
    if (phi > 2 * PI)
        phi = 0;

    HeavenlyBody3d::paintHeavenlyBody3d();

    glPopMatrix();

    if (isOrbitVisisble())
    {
        orbit3d->paintOrbit3d(a, b, e);
    }
}
