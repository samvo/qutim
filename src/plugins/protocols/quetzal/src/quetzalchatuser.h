/****************************************************************************
**
** qutIM - instant messenger
**
** Copyright © 2011 Ruslan Nigmatullin <euroelessar@yandex.ru>
**
*****************************************************************************
**
** $QUTIM_BEGIN_LICENSE$
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
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

#ifndef QUETZALCHATUSER_H
#define QUETZALCHATUSER_H

#include <purple.h>
#include <qutim/buddy.h>

using namespace qutim_sdk_0_3;
class QuetzalChat;

class QuetzalChatUser : public Buddy
{
Q_OBJECT
public:
	explicit QuetzalChatUser(PurpleConvChatBuddy *user, QuetzalChat *chat);
	void fixId(PurpleConvChatBuddy *user);
	PurpleConvChatBuddy *purple() { return m_user; }

	virtual QString id() const { return m_id; }
	virtual QString title() const { return m_name.isEmpty() ? m_id : m_name; }
	virtual bool sendMessage(const Message &message);
	virtual Status status() const;

	void update();
	void rename(const QString &name);
private:
	PurpleConversation *m_conv;
	PurpleConvChatBuddy *m_user;
	QString m_id;
	QString m_name;
};

#endif // QUETZALCHATUSER_H

