#ifndef SETTINGFONTANDCOLOR_H
#define SETTINGFONTANDCOLOR_H

#include "setting/settingapp.h"
#include <QWidget>
#include <QColor>
#include <QFont>
#include <QPair>
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QHash>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QPalette>
#include <QComboBox>
#include <functional>
#include <QColorDialog>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

namespace Ui {
class SettingFontAndColor;
}

class SettingFontAndColor : public QWidget
{
    Q_OBJECT
public:
    explicit SettingFontAndColor(QWidget* parent = nullptr);
    ~SettingFontAndColor() override;

    void writeBackgroundColor(const QColor& color);
    void writeCurrentLineColor(const QColor& color);
    void writeSearchTextColor(const QColor& color);
    void writeFontText(const QFont& font);
    void writeOtherQss(const QColor& color, QFont::Weight weight);
    void writePropertiesQss(const QColor& color, QFont::Weight weight);
    void writePseudoQss(const QColor& color, QFont::Weight weight);
    void writeSubQss(const QColor& color, QFont::Weight weight);
    void writeWidgetQss(const QColor& color, QFont::Weight weight);
    void writeCommentQss(const QColor& color, QFont::Weight weight);
    void writeNumberQss(const QColor& color, QFont::Weight weight);
    QColor backgroundColor();
    QColor currentLineColor();
    QColor searchTextColor();
    QFont fontText();
    void readSettingColor();
    void readSettingQss();
    void writeSetting();
    void addScheme();
    void readKey();
    QPair<QColor, QFont::Weight> otherQss();
    QPair<QColor, QFont::Weight> propertiesQss();
    QPair<QColor, QFont::Weight> pseudoQss();
    QPair<QColor, QFont::Weight> subQss();
    QPair<QColor, QFont::Weight> widgetQss();
    QPair<QColor, QFont::Weight> commentQss();
    QPair<QColor, QFont::Weight> numberQss();
    void clearContainer();

private slots:
    void amendColorEdit();
    void deleteScheme();
    void changeWeight();
    void selectScheme(const QString& scheme);

private:
    class BoxScheme : public QDialog
    {
    public:
        explicit BoxScheme(SettingFontAndColor* parent = nullptr);
        ~BoxScheme() override = default;

        void showBoxScheme();

    private:
        SettingFontAndColor     *m_setting              = nullptr;
        QPushButton             *m_btnOk                = new QPushButton("OK");
        QPushButton             *m_btnCancel            = new QPushButton("Отмена");
        QLineEdit               *m_edit                 = new QLineEdit;

        void newScheme();
    };

    struct FontAndColor
    {
        QColor background;
        QColor currentLine;
        QColor searchText;
        QFont fontText;
        QPair<QColor, QFont::Weight> qssOther;
        QPair<QColor, QFont::Weight> qssProperties;
        QPair<QColor, QFont::Weight> qssPseudo;
        QPair<QColor, QFont::Weight> qssSub;
        QPair<QColor, QFont::Weight> qssWidget;
        QPair<QColor, QFont::Weight> qssComment;
        QPair<QColor, QFont::Weight> qssNumber;
    };

    Ui::SettingFontAndColor         *ui             = nullptr;
    SettingApp                      *m_settingApp   = SettingApp::instance();
    BoxScheme                       *m_boxScheme    = new BoxScheme(this);
    QHash<QString, FontAndColor>    m_scheme_;
    QStringList                     m_removeScheme_;

    void addNameScheme(const QString& scheme);
};

#endif // SETTINGFONTANDCOLOR_H
