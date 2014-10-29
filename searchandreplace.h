#ifndef SEARCHANDREPLACE_H
#define SEARCHANDREPLACE_H

#include <QWidget>

namespace Ui {
class SearchAndReplace;
}

class SearchAndReplace : public QWidget
{
    Q_OBJECT
public:
    explicit SearchAndReplace(QWidget* parent = nullptr);
    ~SearchAndReplace() override;

private:
    Ui::SearchAndReplace    *ui = nullptr;
};

#endif // SEARCHANDREPLACE_H
