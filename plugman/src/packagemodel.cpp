/****************************************************************************
 *
 *  This file is part of qutIM
 *
 *  Copyright (c) 2011 by Nigmatullin Ruslan <euroelessar@gmail.com>
 *
 ***************************************************************************
 *                                                                         *
 *   This file is part of free software; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************
 ****************************************************************************/

#include "packagemodel.h"
#include <qutim/debug.h>

using namespace qutim_sdk_0_3;

PackageModel::PackageModel(PackageEngine *engine)
    : QAbstractListModel(engine), m_engine(engine), m_mode(Attica::Provider::Newest)
{
	m_pageSize = 20;
	m_pagesCount = 0;
	m_requestId = -1;
	connect(engine, SIGNAL(contentsReceived(PackageEntry::List,qint64)),
	        SLOT(onContentsReceived(PackageEntry::List,qint64)));
	connect(engine, SIGNAL(previewLoaded(QString,QPixmap)),
	        SLOT(onPreviewLoaded(QString,QPixmap)));
	if (m_engine->isInitialized()) {
		requestNextPage();
	} else {
		connect(engine, SIGNAL(engineInitialized()), SLOT(requestNextPage()));
	}
}

void PackageModel::setFilter(const QString &filter)
{
	if (m_filter == filter)
		return;
	beginResetModel();
	m_filter = filter;
	m_pagesCount = 0;
	m_indexes.clear();
	m_contents.clear();
	endResetModel();
	if (m_engine->isInitialized())
		requestNextPage();
}

void PackageModel::setSortMode(Attica::Provider::SortMode mode)
{
	if (m_mode == mode)
		return;
	beginResetModel();
	m_mode = mode;
	m_pagesCount = 0;
	m_indexes.clear();
	m_contents.clear();
	endResetModel();
	if (m_engine->isInitialized())
		requestNextPage();
}

int PackageModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
	return m_contents.size();
}

QVariant PackageModel::data(const QModelIndex &index, int role) const
{
	if (index.row() < 0 || index.row() >= m_contents.size())
		return QVariant();
	const PackageEntry &entry = m_contents.at(index.row());
	switch (role) {
	case Qt::DecorationRole:
		return m_images.value(entry.id());
	case Qt::DisplayRole:
		return entry.content().name();
	case Qt::UserRole:
		if (m_requestId == -1 && index.row() == m_contents.size() - 1)
			const_cast<PackageModel*>(this)->requestNextPage();
		return qVariantFromValue(entry);
	default:
		return QVariant();
	}
}

void PackageModel::onContentsReceived(const PackageEntry::List &list, qint64 id)
{
	if (m_requestId != id)
		return;
	debug() << "Contents received" << list.size();
	m_requestId = -1;
	beginInsertRows(QModelIndex(), m_contents.size(), m_contents.size() + list.size() - 1);
	for (int i = 0; i < list.size(); ++i) {
		const PackageEntry &entry = list.at(i);
		m_indexes.insert(entry.id(), m_contents.size());
		m_contents.append(entry);
		if (!m_images.contains(entry.id())) {
			debug() << "Request preview" << entry.content().name();
			m_engine->loadPreview(entry);
		}
	}
	endInsertRows();
	++m_pagesCount;
}

void PackageModel::onPreviewLoaded(const QString &id, const QPixmap &preview)
{
	m_images[id] = preview;
	int index = m_indexes.value(id, -1);
	if (index != -1) {
		QModelIndex modelIndex = QAbstractListModel::index(index);
		emit dataChanged(modelIndex, modelIndex);
	}
}

void PackageModel::requestNextPage()
{
	m_requestId = m_engine->requestContents(m_filter, m_mode, m_pagesCount, m_pageSize);
}
