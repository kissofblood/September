#ifndef RESOURCEEDITOR_H
#define RESOURCEEDITOR_H

#include <QWidget>
#include <QTreeWidgetItem>
#include <QHash>
#include <QListWidgetItem>
#include <QString>
#include <QAbstractItemView>
#include <QPushButton>
#include <QTreeWidget>
#include <functional>
#include <QFileDialog>
#include <QRegExp>
#include <QFileInfo>
#include <QList>
#include <QStringList>
#include <QMessageBox>

namespace Ui {
class ResourceEditor;
}

class ResourceEditor : public QWidget
{
    Q_OBJECT
public:
    explicit ResourceEditor(QWidget* parent = nullptr);
    ~ResourceEditor() override;

private slots:
    void createQrcOrRcc();
    void addItem();
    void addFileItem();
    void removeFile();
    void removeItem();
    void correctTextItem(QTreeWidgetItem* item);
    void showFile(QTreeWidgetItem* current, QTreeWidgetItem* previous);

private:
    Ui::ResourceEditor                                  *ui = nullptr;
    QHash<QListWidgetItem*, QList<QTreeWidgetItem*>>    m_itemQrcAndRcc_;
    QString             m_prevTextItem;
    QTreeWidgetItem     *m_currentItem = nullptr;

    void setEnableBtnItem1(bool value);
    void setEnableBtnItem2(bool value);
};

#endif // RESOURCEEDITOR_H
