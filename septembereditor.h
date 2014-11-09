#ifndef SEPTEMBEREDITOR_H
#define SEPTEMBEREDITOR_H

#include <QMainWindow>
#include <QString>
#include <QWidget>
#include <QKeySequence>
#include <QPushButton>

#include <QtWidgets>

namespace Ui {
class SeptemberEditor;
}

class SeptemberEditor : public QMainWindow
{
    Q_OBJECT
public:
    explicit SeptemberEditor(QWidget* parent = nullptr);
    ~SeptemberEditor() override;

    QString styleSheet() const;

signals:
    void updateStyleSheet(const QString& text);

private slots:
    void closeOrOpenListFile();
    void closeOrOpenWidgetSearchAndReplace();
    void closeOrOpenWidgetWidget();
    void closeOrOpenWidgetUI();

private:
    struct ClickedButton
    {
        bool searchAndReplace = false;
        bool widget = false;
        bool widgetUI = false;
    };
    Ui::SeptemberEditor         *ui = nullptr;
    ClickedButton               m_clickedButton;
};

#endif // SEPTEMBEREDITOR_H
