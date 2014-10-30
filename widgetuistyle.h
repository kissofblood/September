#ifndef WIDGETUISTYLE_H
#define WIDGETUISTYLE_H

#include <QWidget>


#include <QtWidgets>
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

    private:
        QWidget         *m_view     = new QWidget;
        QPushButton     *m_close    = new QPushButton("Закрыть");
    };

    Ui::WidgetUiStyle       *ui             = nullptr;
    QGraphicsScene          *m_sceneView    = nullptr;
    QBuffer                 *m_bufferUi     = nullptr;
    ShowFullWidgetUi        *m_showFull     = new ShowFullWidgetUi(this);
};

#endif // WIDGETUISTYLE_H
