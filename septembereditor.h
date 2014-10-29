#ifndef SEPTEMBEREDITOR_H
#define SEPTEMBEREDITOR_H

#include <QMainWindow>


#include <QtWidgets>

namespace Ui {
class SeptemberEditor;
}

class SeptemberEditor : public QMainWindow
{
    Q_OBJECT

    struct ClickedButton
    {
        bool searchAndReplace = false;
        bool widget = false;
        bool UI = false;
    };
public:
    explicit SeptemberEditor(QWidget* parent = nullptr);
    ~SeptemberEditor() override;

private slots:
    void closeOrOpenListFile();
    void closeOrOpenWidgetSearchAndReplace();
    void closeOrOpenWidgetWidget();
    void closeOrOpenWidgetUI();

private:
    Ui::SeptemberEditor         *ui = nullptr;
    ClickedButton m_clickedButton;
};

#endif // SEPTEMBEREDITOR_H
