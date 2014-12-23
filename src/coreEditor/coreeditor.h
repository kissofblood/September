#ifndef COREEDITOR_H
#define COREEDITOR_H

#include "src/common.h"
#include "highlighter.h"
#include "observercodeqss.h"
#include "setting/settingseptember.h"
#include <QWidget>
#include <QPlainTextEdit>
#include <QSize>
#include <QRect>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QColor>
#include <QList>
#include <QTextEdit>
#include <QTextFormat>
#include <QPainter>
#include <QTextBlock>
#include <QString>
#include <functional>
#include <QCompleter>
#include <QStringList>
#include <QPalette>
#include <QTextCursor>
#include <QFont>
#include <string>
#include <QTextDocument>
#include <tuple>

#include <QtWidgets>

class CoreEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit CoreEditor(QWidget* parent = nullptr);
    ~CoreEditor() override = default;

    void setOtherTextColor(const QColor& color);
    void setFormatOther(const QTextCharFormat& charFormat);
    void setFormatProperties(const QTextCharFormat& charFormat);
    void setFormatPseudo(const QTextCharFormat& charFormat);
    void setFormatWidgets(const QTextCharFormat& charFormat);
    void setFormatSub(const QTextCharFormat& charFormat);
    void setFormatComment(const QTextCharFormat& charFormat);
    void setFormatNumber(const QTextCharFormat& charFormat);
    void checkingCodeQss();
    void appendText(const QString& text);
    void selectTextSearch(const QTextCursor& cursor, const QTextCharFormat& format);
    void replaceSelectTextSearch(const QTextCursor& cursor, const QTextCharFormat& formatNew, const QTextCharFormat& formatOld);
    void clearSelectTextSearch();

signals:
    void updateStyleSheet(const QString& text);

public slots:
    void zoomDocIn();
    void zoomDocOut();
    void setVisibleLineNimberArea(bool value);

private slots:
    void updateLineNumberAreaWidth();
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect& rect, int dy);
    void insertCompletion(const QString& text);
    void insertOrRemove(int block);
    void readColor();

private:
    class LineNumberArea : public QWidget
    {
    public:
        explicit LineNumberArea(CoreEditor* parent = nullptr);
        ~LineNumberArea() override = default;

        QSize sizeHint() const override;

    private:
        CoreEditor      *m_editor = nullptr;

        void paintEvent(QPaintEvent* event) override;
    };

    LineNumberArea      *m_lineNumberArea       = new LineNumberArea(this);
    QCompleter          *m_completer            = new QCompleter(this);
    SettingSeptember    *m_settingSeptember     = SettingSeptember::instance();
    Highlighter         *m_highlighter          = nullptr;
    ObserverCodeQss     *m_observerCode         = nullptr;
    QColor              m_lineColor;
    QColor              m_otherTextColor;
    QVector<bool>       m_blockNumberError_;
    bool                m_visibleLineNumberAre  = true;
    int                 m_zoomDocument          = 12;
    QColor              m_backgroundDoc         = { Qt::black };
    QMultiHash<int, std::tuple<QTextCursor, QTextCharFormat, bool>> m_selectTextSearch_;

    int lineNumberAreaWidth();
    void lineNumberAreaPaintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
};

#endif // COREEDITOR_H