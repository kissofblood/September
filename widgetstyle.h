#ifndef WIDGETSTYLE_H
#define WIDGETSTYLE_H

#include <QWidget>

namespace Ui {
class WidgetStyle;
}

class WidgetStyle : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetStyle(QWidget* parent = nullptr);
    ~WidgetStyle() override;

private:
    Ui::WidgetStyle     *ui = nullptr;
};

#endif // WIDGETSTYLE_H
