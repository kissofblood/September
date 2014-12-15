#ifndef SETTINGKEY_H
#define SETTINGKEY_H

#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QVector>
#include <QHash>
#include <QString>
#include <QTableWidgetItem>
#include <QComboBox>
#include <QLineEdit>
#include <functional>

#include <QtWidgets>

namespace Ui {
class SettingKey;
}

class SettingKey : public QDialog
{
    Q_OBJECT
private:
    explicit SettingKey(QWidget* parent = nullptr);
    ~SettingKey() override;

public:
    static SettingKey* instance(QWidget* parent = nullptr);
    void addItem(const QString& group, const QString& name, const QString& key = QString());

private slots:
    void visibleGrpScheme();
    void hideGroupRow(const QString& text);
    void searchRow(const QString& text);
    void showBoxKey(int row);

private:
    class BoxKey : public QDialog
    {
    public:
        explicit BoxKey(SettingKey* parent = nullptr);
        ~BoxKey() override = default;

        void setTextMessage(const QString& text, int row);

    private:
        SettingKey      *m_settingKey   = nullptr;
        QLabel          *m_lblPressKey  = new QLabel;
        QLabel          *m_lblMessage   = new QLabel;
        QPushButton     *m_button       = new QPushButton("Нет");
        QPushButton     *m_cancel       = new QPushButton("Отмена");
        QString         m_keyText;
        int             m_row;

        void funButton();
        void keyPressEvent(QKeyEvent* event) override;
    };

    static SettingKey               *m_singleton;
    Ui::SettingKey                  *ui         = nullptr;
    BoxKey                          *m_boxKey   = new BoxKey(this);
    QHash<QString, QVector<int>>    m_groupRow_;

    QString checkingItemKey(const QString& text);
};

#endif // SETTINGKEY_H
