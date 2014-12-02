#include "widgetuistyle.h"
#include "ui_widgetuistyle.h"

WidgetUiStyle::WidgetUiStyle(QWidget* parent) : QWidget(parent),
    ui(new Ui::WidgetUiStyle),
    m_editor(parent->parent()->findChild<CoreEditor*>())
{
    ui->setupUi(this);

    this->connect(ui->btnOpen,      &QPushButton::clicked, this, &WidgetUiStyle::openUI);
    this->connect(ui->btnShowFull,  &QPushButton::clicked, this, &WidgetUiStyle::showFull);
    this->connect(m_editor, &CoreEditor::updateStyleSheet, this, &WidgetUiStyle::setStyleSheetWidget);
}

WidgetUiStyle::~WidgetUiStyle()
{ delete ui; }

void WidgetUiStyle::openUI()
{
    QString path = QFileDialog::getOpenFileName(this, "Open file", QString("/home/september"), "*.ui");
    if(path.length() == 0)
        return;

    QFile file(path);
    if(file.open(QIODevice::ReadOnly))
    {
        if(m_sceneView != nullptr)
        {
            m_bufferUi->close();
            m_bufferUi->deleteLater();
            m_sceneView->deleteLater();
        }
        m_bufferUi = new QBuffer(this);
        m_bufferUi->setData(file.readAll());
        m_bufferUi->open(QIODevice::ReadOnly);

        QWidget* widget = QUiLoader().load(m_bufferUi);
        widget->setStyleSheet(m_editor->document()->toPlainText());
        m_sceneView = new QGraphicsScene(0, 0, widget->width(), widget->height());
        ui->view->setScene(m_sceneView);
        m_sceneView->addWidget(widget);
    }
    file.close();
}

void WidgetUiStyle::showFull()
{
    if(m_bufferUi == nullptr)
        return;
    m_bufferUi->seek(0);
    m_showFull->setViewWidgetUi(m_bufferUi);
    m_showFull->setStyleSheetDialog(m_editor->document()->toPlainText());
    m_showFull->showMaximized();
}

void WidgetUiStyle::setStyleSheetWidget(const QString& style)
{
    QList<QGraphicsItem*> list = ui->view->items();
    if(!list.empty())
    {
        QGraphicsProxyWidget* wgt = qgraphicsitem_cast<QGraphicsProxyWidget*>(list.front());
        wgt->widget()->setStyleSheet(style);
    }
    m_showFull->setStyleSheetDialog(style);
}

WidgetUiStyle::ShowFullWidgetUi::ShowFullWidgetUi(QWidget* parent) : QDialog(parent)
{
    QVBoxLayout* box = new QVBoxLayout;
    box->addWidget(m_close);
    this->setLayout(box);

    this->connect(m_close, &QPushButton::clicked, this, &ShowFullWidgetUi::close);
}

void WidgetUiStyle::ShowFullWidgetUi::setViewWidgetUi(QBuffer* bufferUi)
{
    QBoxLayout* l = qobject_cast<QBoxLayout*>(this->layout());
    if(m_view != nullptr)
    {
        l->removeWidget(m_view);
        m_view->deleteLater();
        m_view = nullptr;
    }

    m_view = new QWidget;
    l->insertWidget(0, m_view);

    QHBoxLayout* box = new QHBoxLayout;
    box->addWidget(QUiLoader().load(bufferUi));
    m_view->setLayout(box);
}

void WidgetUiStyle::ShowFullWidgetUi::setStyleSheetDialog(const QString& style)
{
    if(m_view != nullptr)
        m_view->setStyleSheet(style);
}
