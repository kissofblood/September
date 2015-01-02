#ifndef MESSAGESAVEFILEBOX_H
#define MESSAGESAVEFILEBOX_H

#include "src/coreEditor/coreeditor.h"
#include <QDialog>
#include <QWidget>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QPushButton>
#include <QTableWidget>
#include <functional>
#include <QTableWidgetItem>
#include <QFileInfo>
#include <QList>
#include <QPair>

namespace Ui {
class MessageSaveFileBox;
}

class MessageSaveFileBox : public QDialog
{
    Q_OBJECT
public:
    explicit MessageSaveFileBox(QWidget* parent = nullptr);
    ~MessageSaveFileBox() override;

    void appendChangeFile(const QList<QPair<QFileInfo, CoreEditor*>>& list);

signals:
    void clickedSaveFile(const QList<QPair<QFileInfo, CoreEditor*>>& list);
    void clickedReject();

private slots:
    void selectAll();
    void enableBtnSave();
    void saveFile();

private:
    Ui::MessageSaveFileBox  *ui = nullptr;
    QList<CoreEditor*>      m_item_;
};

#endif // MESSAGESAVEFILEBOX_H
