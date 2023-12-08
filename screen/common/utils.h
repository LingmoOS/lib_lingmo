/*
 * Copyright 2013  Daniel Vrátil <dvratil@redhat.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 * by the membership of KDE e.V.), which shall act as a proxy
 * defined in Section 14 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef KSCREEN_KCM_UTILS_H
#define KSCREEN_KCM_UTILS_H

/*
    SPDX-FileCopyrightText: 2013 Daniel Vrátil <dvratil@redhat.com>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#pragma once

#include <QSize>
#include <QString>

#include <kscreen/output.h>
#include <kscreen/types.h>

namespace Utils
{
QString outputName(const KScreen::Output *output, bool shouldShowSerialNumber = false, bool shouldShowConnector = false);
QString outputName(const KScreen::OutputPtr &output, bool shouldShowSerialNumber = false, bool shouldShowConnector = false);

QString sizeToString(const QSize &size);
}

