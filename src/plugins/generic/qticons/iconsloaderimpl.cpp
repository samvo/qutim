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

#include "iconsloaderimpl.h"
#include <qutim/systeminfo.h>
#include <qutim/debug.h>
#include <QCoreApplication>
#include <QImageWriter>
#include <QBuffer>
#include <QDirIterator>
#include <qqml.h>

#define QUTIM_DEFAULT_THEME "qutim-default"

namespace Core
{

IconLoaderImpl::IconLoaderImpl()
{
	QStringList themeSearchPaths = QIcon::themeSearchPaths();
	themeSearchPaths << QCoreApplication::applicationDirPath() + QStringLiteral("/icons");
	themeSearchPaths << (SystemInfo::getPath(SystemInfo::ShareDir) + QStringLiteral("/icons"));
	themeSearchPaths << (SystemInfo::getPath(SystemInfo::SystemShareDir) + QStringLiteral("/icons"));
	QIcon::setThemeSearchPaths(themeSearchPaths);

	m_defaultTheme = QIcon::themeName();

	qDebug() << "theme search paths" << themeSearchPaths;

	qDebug() << "current theme name" << m_defaultTheme;

	Config conf;
	conf.beginGroup("qticons");
	m_defaultEnabled = conf.value("qutim-default", true);

	m_defaultEnabled.onChange(this, [this] (bool enabled) {
		if(enabled)
			QIcon::setThemeName(QStringLiteral(QUTIM_DEFAULT_THEME));
		else
			QIcon::setThemeName(m_defaultTheme);
	});

#if defined(Q_OS_MAC) || defined(Q_OS_WIN)
	QIcon::setThemeName(QStringLiteral(QUTIM_DEFAULT_THEME));
#else
	SettingsItem *settings = new QmlSettingsItem(
				QStringLiteral("qticons"),
				Settings::General,
				QIcon(),
				QT_TRANSLATE_NOOP("Xdg Icon Loader", "Xdg Icon Loader"));
	Settings::registerItem(settings);

	if(m_defaultEnabled)
		QIcon::setThemeName(QStringLiteral(QUTIM_DEFAULT_THEME));
#endif
}

IconLoaderImpl::~IconLoaderImpl()
{
}

//QStringList getAllPossibleNamesFromFreedesktopName(const QString &iconName) {
//	QStringList splitted = iconName.split(QLatin1Char('-'));
//	if(splitted.length() == 1)
//		return QStringList() << iconName + ".*";

//	QStringList ret;
//	QString it;
//	while(!splitted.isEmpty()) {
//		if(it.isEmpty())
//			it += splitted.takeFirst();
//		else {
//			it += "-" + splitted.takeFirst();
//		}
//		ret << it + ".*"; // asterisk for file searching
//	}
//	std::reverse(ret.begin(), ret.end());
//	return ret;
//}

QIcon IconLoaderImpl::doLoadIcon(const QString &name)
{
	if(name.isEmpty() || m_missingIcons.contains(name))
		return QIcon();

	if(!QIcon::fromTheme(name).isNull())
		return QIcon::fromTheme(name);
	else {
		qWarning() << "icon" << name << "not found. See log for list of all missing icons";
		m_missingIcons.insert(name);

		return QIcon();
	}
}

QMovie *IconLoaderImpl::doLoadMovie(const QString &name)
{
	Q_UNUSED(name);
	return 0;
}

QString IconLoaderImpl::doIconPath(const QString &name, uint iconSize)
{
	QIcon icon = doLoadIcon(name);

	QByteArray data;
	QBuffer buffer(&data);
	buffer.open(QBuffer::WriteOnly);

	QPixmap pixmap = icon.pixmap(iconSize);
	QImage image = pixmap.toImage();

	QImageWriter writer(&buffer, "png");
	writer.write(image);

	buffer.close();

	return QStringLiteral("data:image/png;base64,") + QString::fromLatin1(data.toBase64());
}

QString IconLoaderImpl::doMoviePath(const QString &name, uint iconSize)
{
	Q_UNUSED(name);
	Q_UNUSED(iconSize);
	return QString();
}

}

