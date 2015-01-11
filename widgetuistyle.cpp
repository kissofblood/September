#include "widgetuistyle.h"
#include "ui_widgetuistyle.h"

WidgetUiStyle::WidgetUiStyle(QWidget* parent) : QWidget(parent),
    ui(new Ui::WidgetUiStyle)
{
    ui->setupUi(this);
    ui->view->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->view->setScene(m_scene);

    this->connect(ui->btnOpen,      &QPushButton::clicked, this, &WidgetUiStyle::openUI);
    this->connect(ui->btnShowFull,  &QPushButton::clicked, this, &WidgetUiStyle::showFull);
}

WidgetUiStyle::~WidgetUiStyle()
{ delete ui; }

QBuffer* WidgetUiStyle::getBufferUi() const
{ return m_bufferUi; }

QBuffer* WidgetUiStyle::createBufferUi()
{
    m_bufferUi = new QBuffer(this);
    return m_bufferUi;
}

void WidgetUiStyle::setBufferUi(QBuffer* buffer)
{
    m_bufferUi = buffer;
    m_scene->clear();
    if(m_bufferUi->isOpen())
    {
        m_bufferUi->seek(0);
        createWidgetUi();
    }
}

void WidgetUiStyle::openUI()
{
    QString path = QFileDialog::getOpenFileName(this, "Open file", QDir::home().absolutePath(), "*.ui");
    if(path.length() == 0)
        return;

    QFile file(path);
    if(file.open(QIODevice::ReadOnly))
    {
        m_bufferUi->close();
        m_scene->clear();

        m_bufferUi->setData(file.readAll());
        m_bufferUi->open(QIODevice::ReadOnly);
        createWidgetUi();
    }
    file.close();
}

void WidgetUiStyle::showFull()
{
    if(!m_bufferUi->isOpen())
        return;

    m_editor = this->parent()->parent()->findChild<CoreEditor*>();
    m_bufferUi->seek(0);
    m_showFull->setViewWidgetUi(m_bufferUi);
    m_showFull->setStyleSheetDialog(m_editor->document()->toPlainText());
    m_showFull->showMaximized();
}

void WidgetUiStyle::createWidgetUi()
{
    m_editor = this->parent()->parent()->findChild<CoreEditor*>();
    QWidget* widget = QUiLoader().load(m_bufferUi);
    widget->resize(this->size());
    m_scene->setSceneRect(0, 0, widget->width(), widget->height());
    widget->setStyleSheet(m_editor->document()->toPlainText());
    m_scene->addWidget(widget);
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
