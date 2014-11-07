#ifndef WIDGETUISTYLE_H
#define WIDGETUISTYLE_H

#include "septembereditor.h"
#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QBuffer>
#include <QtUiTools/QUiLoader>
#include <QList>
#include <QGraphicsItem>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QString>

#include <QtWidgets>

namespace Ui {
class WidgetUiStyle;
}

class WidgetUiStyle : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetUiStyle(QWidget* parent = nullptr);
    ~WidgetUiStyle() override;

private slots:
    void openUI();
    void showFull();
    void setStyleSheetWidget(const QString& style);

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
    QGraphicsScene          *m_sceneView    = nullptr;
    QBuffer                 *m_bufferUi     = nullptr;
    SeptemberEditor         *m_editor       = nullptr;
    ShowFullWidgetUi        *m_showFull     = new ShowFullWidgetUi(this);
};

#endif // WIDGETUISTYLE_H
