/****************************************************************************
**
** qutIM instant messenger
**
** Copyright (C) 2011 Evgeniy Degtyarev <degtep@gmail.com>
**
*****************************************************************************
**
** $QUTIM_BEGIN_LICENSE$
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
** See the GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see http://www.gnu.org/licenses/.
** $QUTIM_END_LICENSE$
**
****************************************************************************/

#ifndef MAEMO5SETTINGSPLUGIN_H
#define MAEMO5SETTINGSPLUGIN_H

#include <qutim/plugin.h>
#include <qutim/settingslayer.h>
#include "maemo5settings.h"

using namespace qutim_sdk_0_3;

class Maemo5SettingsPlugin : public Plugin
{
	Q_OBJECT
public:
	explicit Maemo5SettingsPlugin();
	virtual void init();
	virtual bool load();
	virtual bool unload();
	GeneralSettingsItem<Maemo5Settings> *m_item;
};

#endif // MAEMO5SETTINGSPLUGIN_H
