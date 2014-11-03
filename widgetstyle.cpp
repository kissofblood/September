#include "widgetstyle.h"
#include "ui_widgetstyle.h"

WidgetStyle::WidgetStyle(QWidget* parent) : QWidget(parent),
    ui(new Ui::WidgetStyle)
{
    ui->setupUi(this);
    for(auto& str : KeyWords::widget)
        if(str != "QAbstractScrollArea" && str != "QColumnView" && str != "QDialogButtonBox"
           && str != "QHeaderView" && str != "QMessageBox" && str != "QSizeGrip"
            && str != "QStatusBar" && str != "QTabBar" && str != "QToolBar"
             && str != "QToolTip")
        {
            QString key = str;
            key.remove(0, 1);
            ui->listWidget->addItem(key);
        }

    ui->view->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    this->connect(ui->lineEdit,     &QLineEdit::textChanged,    this, &WidgetStyle::filterListWidget);
    this->connect(ui->btnAddWidget, &QPushButton::clicked,      this, &WidgetStyle::selectWidget);
    this->connect(ui->btnWidgetRemove, &QPushButton::clicked,   this, &WidgetStyle::deleteWidget);
    this->connect(ui->btnClear,     &QPushButton::clicked,      this, &WidgetStyle::clearScene);
}

WidgetStyle::~WidgetStyle()
{
    delete ui;
}

void WidgetStyle::filterListWidget()
{
    QString text = ui->lineEdit->text();
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        if(ui->listWidget->item(i)->text().contains(text, Qt::CaseInsensitive))
            ui->listWidget->item(i)->setHidden(false);
        else
            ui->listWidget->item(i)->setHidden(true);
    }
}

void WidgetStyle::selectWidget()
{
    QListWidgetItem* item = ui->listWidget->currentItem();
    if(item == nullptr)
        return;
    QWidget* widget = createWidget(item->text());
    if(m_scene == nullptr)
    {
        m_scene = new WidgetScene(0, 0, 5000, 5000, this);
        ui->view->setScene(m_scene);
    }
    m_graphicsWgt_.push_back(new GraphicsWidget(widget));
    m_scene->addItem(m_graphicsWgt_.back());
}

void WidgetStyle::deleteWidget()
{
    for(GraphicsWidget* wgt : m_deleteGraphicsWgt_)
    {
        m_scene->removeItem(wgt);
        m_graphicsWgt_.erase(qFind(m_graphicsWgt_.begin(), m_graphicsWgt_.end(), wgt));
        delete wgt;
    }
    m_deleteGraphicsWgt_.clear();
}

void WidgetStyle::clearScene()
{
    m_scene->deleteLater();
    m_scene = nullptr;
    m_graphicsWgt_.clear();
}

QWidget* WidgetStyle::createWidget(const QString& name)
{
    if(name == "CheckBox")
    {
        QCheckBox* box = new QCheckBox("CheckBox");
        box->resize(97, 24);
        return box;
    }
    else if(name == "ComboBox")
    {
        QComboBox* box = new QComboBox;
        box->addItem("Item1");
        box->addItem("Item3");
        box->addItem("Item3");
        box->resize(78, 26);
        return box;
    }
    else if(name == "DateEdit")
    {
        QDateEdit* date = new QDateEdit;
        date->resize(105, 30);
        return date;
    }
    else if(name == "DateTimeEdit")
    {
        QDateTimeEdit* date = new QDateTimeEdit;
        date->resize(155, 27);
        return date;
    }
    else if(name == "Dialog")
    {
        QDialog* dialog = new QDialog;
        dialog->resize(150, 100);
        return dialog;
    }
    else if(name == "DockWidget")
    {
        QDockWidget* widget = new QDockWidget;
        widget->resize(61, 22);
        return widget;
    }
    else if(name == "DoubleSpinBox")
    {
        QDoubleSpinBox* box = new QDoubleSpinBox;
        box->resize(80, 38);
        return box;
    }
    else if(name == "Frame") //??
    {
        QFrame* frame = new QFrame;
        frame->resize(150, 100);
        return frame;
    }
    else if(name == "GroupBox")
    {
        QGroupBox* box = new QGroupBox("GroupBox");
        box->resize(150, 100);
        return box;
    }
    else if(name == "Label")
    {
        QLabel* label = new QLabel("Label");
        label->resize(37, 18);
        return label;
    }
    else if(name == "LineEdit")
    {
        QLineEdit* line = new QLineEdit;
        line->resize(27, 26);
        return line;
    }
    else if(name == "ListView") //??
    {
        QListView* view = new QListView;
        view->resize(71, 71);
        return view;
    }
    else if(name == "ListWidget") //??
    {
        QListWidget* widget = new QListWidget;
        widget->resize(71, 71);
        return widget;
    }
    else if(name == "MainWindow")
    {
        QMainWindow* window = new QMainWindow;
        window->resize(150, 100);
        return window;
    }
    else if(name == "Menu") //??
    {
        QMenu* menu = new QMenu;
        menu->addMenu("Menu1");
        menu->addMenu("Menu2");
        menu->addSeparator();
        menu->addMenu("Menu3");
        menu->resize(150, 100);
        return menu;
    }
    else if(name == "MenuBar")
    {
        QMenuBar* bar = new QMenuBar;
        QMenu* menu1 = bar->addMenu("MenuBar1");
        menu1->addMenu("Menu1");
        menu1->addSeparator();
        menu1->addMenu("Menu2");
        QMenu* menu2 = bar->addMenu("MenuBar2");
        menu2->addMenu("Menu1");
        menu2->addSeparator();
        menu2->addMenu("Menu2");
        QMenu* menu3 = bar->addMenu("MenuBar3");
        menu3->addMenu("Menu1");
        menu3->addSeparator();
        menu3->addMenu("Menu2");
        bar->resize(270, 50);
        return bar;
    }
    else if(name == "ProgressBar")
    {
        QProgressBar* bar = new QProgressBar;
        bar->resize(100, 20);
        bar->setRange(0, 100);
        bar->setValue(0);

        QTimer* timer = new QTimer(bar);
        this->connect(timer, &QTimer::timeout, this, [bar]()
        {
            if(bar->value() == 100)
                bar->setValue(0);
            else
                bar->setValue(bar->value() + 1);
        });
        timer->start(100);
        return bar;
    }
    else if(name == "PushButton")
    {
        QPushButton* button = new QPushButton("PushButton");
        button->resize(91, 26);
        return button;
    }
    else if(name == "RadioButton")
    {
        QRadioButton* button = new QRadioButton("RadioButton");
        button->resize(112, 24);
        return button;
    }
    else if(name == "ScrollBar")
    {
        QScrollBar* barH = new QScrollBar(Qt::Horizontal);
        QScrollBar* barV = new QScrollBar(Qt::Vertical);
        QHBoxLayout* box = new QHBoxLayout;
        box->addWidget(barH);
        box->addWidget(barV);

        QWidget* widget = new QWidget;
        widget->resize(200, 100);
        widget->setLayout(box);
        return widget;
    }
    else if(name == "Slider")
    {
        QSlider* sliderH = new QSlider(Qt::Horizontal);
        QSlider* sliderV = new QSlider(Qt::Vertical);
        QHBoxLayout* box = new QHBoxLayout;
        box->addWidget(sliderH);
        box->addWidget(sliderV);

        QWidget* widget = new QWidget;
        widget->resize(200, 100);
        widget->setLayout(box);
        return widget;
    }
    else if(name == "SpinBox")
    {
        QSpinBox* box = new QSpinBox;
        box->resize(51, 27);
        return box;
    }
    else if(name == "Splitter") // ?
    {
        QSplitter* splitter = new QSplitter(Qt::Vertical);
        splitter->addWidget(new QPushButton("PushButton1"));
        splitter->addWidget(new QPushButton("PushButton2"));
        splitter->resize(200, 100);
        return splitter;
    }
    else if(name == "TabWidget")
    {
        QTabWidget* tab = new QTabWidget;
        tab->addTab(new QWidget, "Widget1");
        tab->addTab(new QWidget, "Widget2");
        tab->resize(200, 100);
        return tab;
    }
    else if(name == "TableView") //?
    {
        QTableView* view = new QTableView;
        view->resize(200, 100);
        return view;
    }
    else if(name == "TableWidget") //?
    {
        QTableWidget* widget = new QTableWidget;
        widget->resize(200, 100);
        return widget;
    }
    else if(name == "TextEdit")
    {
        QTextEdit* text = new QTextEdit;
        text->resize(71, 71);
        return text;
    }
    else if(name == "TimeEdit")
    {
        QTimeEdit* time = new QTimeEdit;
        time->resize(74, 26);
        return time;
    }
    else if(name == "ToolButton")
    {
        QToolButton* button = new QToolButton;
        button->setText("ToolButton");
        button->resize(92, 25);
        return button;
    }
    else if(name == "ToolBox")
    {
        QToolBox* box = new QToolBox;
        box->addItem(new QWidget, "Widget1");
        box->addItem(new QWidget, "Widget2");
        box->addItem(new QWidget, "Widget3");
        box->resize(100, 170);
        return box;
    }
    else if(name == "TreeView")
    {
        QTreeView* tree = new QTreeView;
        tree->resize(200, 100);
        return tree;
    }
    else if(name == "TreeWidget")
    {
        QTreeWidget* tree = new QTreeWidget;
        tree->resize(200, 100);
        return tree;
    }
    else if(name == "Widget")
    {
        QWidget* widget = new QWidget;
        widget->resize(200, 100);
        return widget;
    }
    return nullptr;
}

void WidgetStyle::distinguishRect(const QRectF& rect)
{
    m_deleteGraphicsWgt_.clear();
    for(GraphicsWidget* wgt : m_graphicsWgt_)
    {
        if(rect.intersects(wgt->boundingRectToScene()))
        {
            wgt->selectWidget(true);
            m_deleteGraphicsWgt_.push_back(wgt);
        }
        else
        {
            auto iter = qFind(m_deleteGraphicsWgt_.begin(), m_deleteGraphicsWgt_.end(), wgt);
            if(iter != m_deleteGraphicsWgt_.end())
                m_deleteGraphicsWgt_.erase(iter);
            wgt->selectWidget(false);
        }
    }
}

bool WidgetStyle::containsWidget(const QPointF& point)
{
    for(GraphicsWidget* wgt : m_graphicsWgt_)
        if(wgt->contains(point))
            return true;
    return false;
}

WidgetStyle::WidgetScene::WidgetScene(qreal x, qreal y, qreal widht, qreal height, QObject* parent) : QGraphicsScene(x, y, widht, height, parent)
    , m_wgtStyle(qobject_cast<WidgetStyle*>(parent))
{ }

void WidgetStyle::WidgetScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        QPointF point = event->scenePos();
        if(m_wgtStyle->containsWidget(point))
            m_mouseButton = Qt::NoButton;
        else
        {
            m_rectItem = this->addRect(point.x(), point.y(), 0, 0);
            m_rectItem->setPen(QPen(QColor(103, 157, 205)));
            m_rectItem->setBrush(QBrush(QColor(200, 218, 231, 100)));
            m_topLeftRect = event->scenePos();
            m_mouseButton = Qt::LeftButton;
            m_wgtStyle->distinguishRect(m_rectItem->rect());
        }
    }
    else
        m_mouseButton = Qt::NoButton;
    QGraphicsScene::mousePressEvent(event);
}

void WidgetStyle::WidgetScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if(m_mouseButton == Qt::LeftButton)
    {
        QRectF rect = m_rectItem->rect();
        QPointF point = event->scenePos();

        if(point.x() >= m_topLeftRect.x() && point.y() >= m_topLeftRect.y())
        {
            rect.setTopLeft(m_topLeftRect);
            rect.setBottomRight(point);
        }
        else if(point.x() >= m_topLeftRect.x() && point.y() <= m_topLeftRect.y())
        {
            rect.setTopLeft(m_topLeftRect);
            rect.setTopRight(point);
        }
        else if(point.x() <= m_topLeftRect.x() && point.y() >= m_topLeftRect.y())
        {
            rect.setTopLeft(m_topLeftRect);
            rect.setBottomLeft(point);
        }
        else if(point.x() <= m_topLeftRect.x() && point.y() <= m_topLeftRect.y())
        {
            rect.setTopLeft(m_topLeftRect);
            rect.setTopLeft(point);
        }
        m_rectItem->setRect(rect);
        m_wgtStyle->distinguishRect(rect);
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void WidgetStyle::WidgetScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if(m_mouseButton != Qt::NoButton)
    {
        m_mouseButton = Qt::NoButton;
        this->removeItem(m_rectItem);
        delete m_rectItem;
        m_rectItem = nullptr;
    }

    QGraphicsScene::mouseReleaseEvent(event);
}
