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
public:
    explicit SeptemberEditor(QWidget* parent = nullptr);
    ~SeptemberEditor() override;

private slots:
    void closeOrOpenListFile();

private:
    Ui::SeptemberEditor         *ui = nullptr;
};

#endif // SEPTEMBEREDITOR_H
