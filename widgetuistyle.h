#ifndef WIDGETUISTYLE_H
#define WIDGETUISTYLE_H

#include "src/coreEditor/coreeditor.h"
#include <QWidget>
#include <QDialog>
#include <QBuffer>
#include <QString>
#include <QPushButton>
#include <QGraphicsScene>
#include <QFileDialog>
#include <QFile>
#include <QIODevice>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QBoxLayout>
#include <QGraphicsProxyWidget>
#include <QGraphicsItem>
#include <QList>
#include <QDir>
#include <QtUiTools/QUiLoader>

namespace Ui {
class WidgetUiStyle;
}

class WidgetUiStyle : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetUiStyle(QWidget* parent = nullptr);
    ~WidgetUiStyle() override;

    QBuffer* getBufferUi() const;
    QBuffer* createBufferUi();
    void setBufferUi(QBuffer* buffer);

public slots:
    void setStyleSheetWidget(const QString& style);

private slots:
    void openUI();
    void showFull();

private:
    class ShowFullWidgetUi : public QDialog
    {
    public:
        ShowFullWidgetUi(QWidget* parent = nullptr);
        ~ShowFullWidgetUi() override = default;

        void setViewWidgetUi(QBuffer* bufferUi);
        void setStyleSheetDialog(const QString& style);

    private:
        QWidget         *m_view     = nullptr;
        QPushButton     *m_close    = new QPushButton("Закрыть");
    };

    Ui::WidgetUiStyle       *ui             = nullptr;
    QGraphicsScene          *m_scene        = new QGraphicsScene(this);
    QBuffer                 *m_bufferUi     = new QBuffer(this);
    CoreEditor              *m_editor       = nullptr;
    ShowFullWidgetUi        *m_showFull     = new ShowFullWidgetUi(this);

    void createWidgetUi();
};

#endif // WIDGETUISTYLE_H
