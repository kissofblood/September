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
#include <QDir>
#include <QProcess>
#include <QPair>
#include <QResource>
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

signals:
    void removeRcc();
    void pathResource(const QStringList& list);

private slots:
    void createQrcOrRcc();
    void openQrcOrRcc();
    void addItem();
    void addImgItem();
    void removeFile();
    void removeItem();
    void showImg(QTreeWidgetItem* item);
    void selectFile(QListWidgetItem* item);
    void selectItem();
    void changeTextPrefix(const QString& text);
    void changeTextAlias(const QString& text);
    void registerFile();

private:
    Ui::ResourceEditor      *ui = nullptr;
    QHash<QListWidgetItem*, QPair<QList<QTreeWidgetItem*>, QResource*>> m_itemQrcAndRcc_;
    QString             m_prevTextItem;
    QTreeWidgetItem     *m_currentItem  = nullptr;
    QProcess            *m_process      = new QProcess(this);
    const QString       m_pathHome      = QDir::homePath();

    void setEnableBtn(bool value);
    void setEnableWgt(bool value);
    void parserPathImg(QTreeWidgetItem* treeItem, QListWidgetItem* listItem, const QString& pathImg);
};

#endif // RESOURCEEDITOR_H
