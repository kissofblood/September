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
#include <QListWidget>
#include <QLineEdit>
#include <QFile>
#include <QIODevice>
#include <QXmlStreamWriter>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomNode>

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
    void openQrcOrRcc();
    void addItem();
    void addImgItem();
    void removeFile();
    void removeItem();
    void showImg(QTreeWidgetItem* current, QTreeWidgetItem* previous);
    void selectFile(QListWidgetItem* item);
    void selectItem();
    void changeTextPrefix(const QString& text);
    void changeTextAlias(const QString& text);
    void registerFile();

private:
    Ui::ResourceEditor      *ui = nullptr;
    QHash<QListWidgetItem*, QList<QTreeWidgetItem*>> m_itemQrcAndRcc_;
    QString m_prevTextItem;
    QTreeWidgetItem* m_currentItem = nullptr;

    void setEnableBtn(bool value);
    void setEnableWgt(bool value);
};

#endif // RESOURCEEDITOR_H
