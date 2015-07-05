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

#ifndef FILETRANSFERDIALOG_H
#define FILETRANSFERDIALOG_H

#include <QDialog>
#include <QFileInfo>
#include <QAbstractItemModel>
#include <qutim/filetransfer.h>

class QToolButton;

namespace Ui {
	class FileTransferDialog;
}

namespace Core
{
using namespace qutim_sdk_0_3;
class SimpleFileTransfer;
class FileTransferJobModel;

class ActionWidget : public QWidget
{
	Q_OBJECT
public:
	ActionWidget(FileTransferJob *job, QWidget *parent = 0);
private slots:
	void onStateChanged(qutim_sdk_0_3::FileTransferJob::State);
private:
	QToolButton *m_stopButton;
};

class FileTransferDialog : public QDialog
{
	Q_OBJECT
public:
	FileTransferDialog(FileTransferJobModel *model);
	~FileTransferDialog();
	void setModel(FileTransferJobModel *model);
	int currentJob();
protected:
	void changeEvent(QEvent *e);
private:
	void createActionWidget(int row);
	FileTransferJob *getSelectedJob();
	void openPath(const QString &file);
private slots:
	void rowsInserted(const QModelIndex &parent, int start, int end);
	void rowsRemoved(const QModelIndex &parent, int start, int end);
	void onRemoveFinishedJobs();
	void customContextMenuRequested(const QPoint &pos);
	void onRemoveJob();
	void onStopJob();
	void onOpenFileAction(const QModelIndex &index);
	void onOpenFileAction();
	void onOpenDirAction();
private:
	Ui::FileTransferDialog *ui;
	QList<ActionWidget*> m_actionWidgets;
	FileTransferJobModel *m_model;
	QAction *m_removeAction;
	QAction *m_stopAction;
	QAction *m_openFileAction;
	QAction *m_openDirAction;
};

}

#endif // FILETRANSFERDIALOG_H

