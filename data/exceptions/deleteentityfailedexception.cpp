/*
    Copyright (C) 2012 by
    Fabian Deitelhoff (FH@FabianDeitelhoff.de) and
    Christof Geisler (christof.geisler@stud.fh-swf.de)

    This file is part of the project SolarSystemSimulation.

    SolarSystemSimulation is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SolarSystemSimulation is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SolarSystemSimulation.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "deleteentityfailedexception.h"

/*!
 \brief Constructor with error message only.

 \param message Error message of the Object
*/
DeleteEntityFailedException::DeleteEntityFailedException(QString message)
{
    this->message = message;
    sqlError = "";
}

/*!
 \brief Constructor for the exception with error message and SQL-error.

 \param message Error message of the Object
 \param sqlError SQL Error of the Object
*/
DeleteEntityFailedException::DeleteEntityFailedException(QString message, QString sqlError)
{
    this->message = message;
    this->sqlError = sqlError;
}

/*!
 \brief Getter for message

 \return const QString
*/
const QString DeleteEntityFailedException::getMessage() const throw()
{
    return message;
}

/*!
 \brief Getter for sqlError

 \return const QString
*/
const QString DeleteEntityFailedException::getSqlError() const throw()
{
    return sqlError;
}
