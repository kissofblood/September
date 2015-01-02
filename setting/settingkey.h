#ifndef SETTINGKEY_H
#define SETTINGKEY_H

#include "settingapp.h"
#include <QDialog>
#include <QWidget>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QHash>
#include <QVector>
#include <QPair>
#include <QStringList>
#include <QAbstractItemView>
#include <QComboBox>
#include <functional>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QHeaderView>
#include <QCloseEvent>
#include <QKeyEvent>

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
    void readScheme();
    void addValue(const QString& group, const QString& name);
    void addKey();
    bool containsKey(const QString& group, const QString& name);
    void writeDefaultKey(const QString& group, const QString& name, const QString& key = QString());
    QString readKey(const QString& group, const QString& name);

signals:
    void settingKeyOK();

private slots:
    void visibleGrpScheme();
    void hideGroupRow(const QString& text);
    void searchRow(const QString& text);
    void showBoxKey(int row);
    void deleteScheme();
    void selectScheme(const QString& text);
    void writeSetting();
    void clearContainer();
    void setDefaultScheme();

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

    class BoxScheme : public QDialog
    {
    public:
        explicit BoxScheme(SettingKey* parent = nullptr);
        ~BoxScheme() override = default;

        void showBoxScheme();

    private:
        SettingKey      *m_settingKey   = nullptr;
        QPushButton     *m_btnOk        = new QPushButton("OK");
        QPushButton     *m_btnCancel    = new QPushButton("Отмена");
        QLineEdit       *m_edit         = new QLineEdit;

        void newScheme();
    };

    static SettingKey               *m_singleton;
    SettingApp                      *m_settingApp   = SettingApp::instance();
    Ui::SettingKey                  *ui             = nullptr;
    BoxKey                          *m_boxKey       = new BoxKey(this);
    BoxScheme                       *m_boxScheme    = new BoxScheme(this);
    QHash<QString, QVector<int>>    m_groupRow_;
    QHash<QString, QVector<QPair<QString, QString>>> m_scheme_;
    QStringList m_removeScheme_;

    QString checkingItemKey(const QString& text);
    void addNameScheme(const QString& scheme);
    void addItemTable(const QString& group, const QString& name, const QString& key);
    void closeEvent(QCloseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // SETTINGKEY_H
