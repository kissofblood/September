#ifndef FONTPAGE_H
#define FONTPAGE_H

#include <QWidget>
#include <QFontDialog>

#include <QtWidgets>

class FontPage : public QFontDialog
{
    Q_OBJECT
public:
    explicit FontPage(QWidget* parent = nullptr);
    ~FontPage() override = default;

signals:

public slots:
};

#endif // FONTPAGE_H
