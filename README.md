Solar System Simulation
=============
This project is an simple simulation of an user created solar system.

The user is able to create stars and planets and combine them to simple (one star) solar systems.

Simulation
-------------
The simulation is based upon the three Kepler's laws of planetary motion and not yet include the Newton's laws of gravity.

Technical stuff
-------------
Until now the project is created with the Qt-Creator and can be compiled with Qt 4.8.1. The OpenGL and freeglut libraries are also included for Win32.

The database connection can be established with ODBC or an native driver. Until now it is developed with a PostgreSQL database.

The connection has to be changed directly in code. See the class _PostgreSQLDatabase_.  