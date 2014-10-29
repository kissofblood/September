#ifndef WIDGETUISTYLE_H
#define WIDGETUISTYLE_H

#include <QWidget>

namespace Ui {
class WidgetUiStyle;
}

class WidgetUiStyle : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetUiStyle(QWidget* parent = nullptr);
    ~WidgetUiStyle() override;

private:
    Ui::WidgetUiStyle       *ui = nullptr;
};

#endif // WIDGETUISTYLE_H
