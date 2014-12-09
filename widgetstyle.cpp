#include "widgetstyle.h"
#include "ui_widgetstyle.h"

WidgetStyle::WidgetStyle(QWidget* parent) : QWidget(parent),
    ui(new Ui::WidgetStyle)
{
    ui->setupUi(this);
    for(auto& str : Common::keyWordsFromFile("listOfStylableWidgets"))
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
    ui->view->setScene(m_scene);

    this->connect(ui->lineEdit,     &QLineEdit::textChanged,    this, &WidgetStyle::filterListWidget);
    this->connect(ui->btnAddWidget, &QPushButton::clicked,      this, &WidgetStyle::selectWidget);
    this->connect(ui->btnWidgetRemove, &QPushButton::clicked,   this, &WidgetStyle::deleteWidget);
    this->connect(ui->btnClear,     &QPushButton::clicked,      this, &WidgetStyle::clearScene);
}

WidgetStyle::~WidgetStyle()
{ delete ui; }

void WidgetStyle::setFocusLineEdit()
{ ui->lineEdit->setFocus(); }

QGraphicsScene* WidgetStyle::getScene() const
{ return m_scene; }

QGraphicsScene* WidgetStyle::createScene()
{
    m_scene = new WidgetScene(0, 0, 5000, 5000, this);
    return m_scene;
}

void WidgetStyle::setScene(QGraphicsScene* scene)
{
    m_scene = reinterpret_cast<WidgetScene*>(scene);
    ui->view->setScene(m_scene);
    m_deleteGraphicsWgt_.clear();
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
    m_editor = this->parent()->parent()->findChild<CoreEditor*>();
    QListWidgetItem* item = ui->listWidget->currentItem();
    if(item == nullptr)
        return;
    QWidget* widget = createWidget(item->text());
    QPointF visibleTopLeft = ui->view->mapToScene(ui->view->viewport()->geometry()).boundingRect().topLeft();
    GraphicsWidget* wgt = new GraphicsWidget(widget, visibleTopLeft);
    wgt->setStyleSheet(m_editor->document()->toPlainText());
    m_scene->addItem(wgt);
    m_scene->addItemWidget(wgt);
}

void WidgetStyle::deleteWidget()
{
    for(GraphicsWidget* wgt : m_deleteGraphicsWgt_)
    {
        m_scene->removeItem(wgt);
        delete m_scene->removeWidget(wgt);
    }
    m_deleteGraphicsWgt_.clear();
}

void WidgetStyle::clearScene()
{
    m_scene->clear();
    m_scene->clearWidget();
    m_deleteGraphicsWgt_.clear();
}

void WidgetStyle::setStyleSheetWidget(const QString& style)
{
    if(style.isEmpty())
        return;
    for(GraphicsWidget* wgt : m_scene->getItemWidget())
        wgt->setStyleSheet(style);
}

QWidget* WidgetStyle::createWidget(const QString& name)
{
    if(name == "CheckBox")
    {
        QCheckBox* box = new QCheckBox("CheckBox");
        box->setObjectName("CheckBox");
        return setLayoutWidget({ box }, { 100, 30 });
    }
    else if(name == "ComboBox")
    {
        QComboBox* box = new QComboBox;
        box->addItem("Item1");
        box->addItem("Item3");
        box->addItem("Item3");
        box->setObjectName("ComboBox");
        return setLayoutWidget({ box }, { 70, 30 });
    }
    else if(name == "DateEdit")
    {
        QDateEdit* date = new QDateEdit;
        date->setObjectName("DateEdit");
        return setLayoutWidget({ date }, { 110, 40 });
    }
    else if(name == "DateTimeEdit")
    {
        QDateTimeEdit* date = new QDateTimeEdit;
        date->setObjectName("DateTimeEdit");
        return setLayoutWidget({ date }, { 160, 30 });
    }
    else if(name == "Dialog")
    {
        QDialog* dialog = new QDialog;
        dialog->setObjectName("Dialog");
        return setLayoutWidget({ dialog }, { 160, 110 });
    }
    else if(name == "DockWidget") //?
    {
        QDockWidget* widget = new QDockWidget;
        widget->setObjectName("DockWidget");
        widget->resize(61, 22);
        return widget;
    }
    else if(name == "DoubleSpinBox")
    {
        QDoubleSpinBox* box = new QDoubleSpinBox;
        box->setObjectName("DoubleSpinBox");
        return setLayoutWidget({ box }, { 90, 40 });
    }
    else if(name == "Frame") //??
    {
        QFrame* frame = new QFrame;
        frame->setObjectName("Frame");
        frame->resize(150, 100);
        return frame;
    }
    else if(name == "GroupBox")
    {
        QGroupBox* box = new QGroupBox("GroupBox");
        box->setObjectName("GroupBox");
        return setLayoutWidget({ box }, { 160, 110 });
    }
    else if(name == "Label")
    {
        QLabel* label = new QLabel("Label");
        label->setObjectName("Label");
        return setLayoutWidget({ label }, { 40, 20});
    }
    else if(name == "LineEdit")
    {
        QLineEdit* line = new QLineEdit;
        line->setObjectName("LineEdit");
        return setLayoutWidget({ line }, { 30, 30 });
    }
    else if(name == "ListView") //??
    {
        QListView* view = new QListView;
        view->setObjectName("ListView");
        view->resize(71, 71);
        return view;
    }
    else if(name == "ListWidget")
    {
        QListWidget* list = new QListWidget;
        list->setObjectName("ListWidget");
        for(int i = 0; i < 20; i++)
            list->addItem(QString("Item %1").arg(i));
        return setLayoutWidget({ list }, { 80, 80 });
    }
    else if(name == "MainWindow")
    {
        QMainWindow* window = new QMainWindow;
        window->setObjectName("MainWindow");
        return setLayoutWidget({ window }, { 160, 110 });
    }
    else if(name == "Menu")
    {
        QMenu* parentMenu = new QMenu;
        parentMenu->setObjectName("Menu");
        parentMenu->addMenu("Menu1");
        QMenu* menu1 = parentMenu->addMenu("Menu2");
        menu1->addMenu("Menu1");
        menu1->addMenu("Menu2");
        parentMenu->addSeparator();
        parentMenu->addMenu("Menu3");
        return setLayoutWidget({ parentMenu }, { 160, 110 });
    }
    else if(name == "MenuBar")
    {
        QMenuBar* bar = new QMenuBar;
        bar->setObjectName("QMenuBar");
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
        return setLayoutWidget({ bar }, { 280, 60 });
    }
    else if(name == "ProgressBar")
    {
        QProgressBar* bar = new QProgressBar;
        bar->setObjectName("ProgressBar");
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
        return setLayoutWidget({ bar }, { 110, 30 });
    }
    else if(name == "PushButton")
    {
        QPushButton* button = new QPushButton("PushButton");
        button->setObjectName("PushButton");
        return setLayoutWidget({ button }, { 125, 30 });
    }
    else if(name == "RadioButton")
    {
        QRadioButton* button = new QRadioButton("RadioButton");
        button->setObjectName("RadioButton");
        return setLayoutWidget({ button }, { 125, 30 });
    }
    else if(name == "ScrollBar")
    {
        QScrollBar* barH = new QScrollBar(Qt::Horizontal);
        QScrollBar* barV = new QScrollBar(Qt::Vertical);
        barH->setObjectName("ScrollBarH");
        barV->setObjectName("ScrollBarV");
        return setLayoutWidget({ barH, barV }, { 200, 100 });
    }
    else if(name == "Slider")
    {
        QSlider* sliderH = new QSlider(Qt::Horizontal);
        QSlider* sliderV = new QSlider(Qt::Vertical);
        sliderH->setObjectName("SliderH");
        sliderV->setObjectName("SliderV");
        return setLayoutWidget({ sliderH, sliderV }, { 200, 100 });
    }
    else if(name == "SpinBox")
    {
        QSpinBox* spinBox = new QSpinBox;
        spinBox->setObjectName("SpinBox");
        return setLayoutWidget({ spinBox }, { 60, 35 });
    }
    else if(name == "Splitter")
    {
        QSplitter* splitterV = new QSplitter(Qt::Vertical);
        QSplitter* splitterH = new QSplitter(Qt::Horizontal);
        splitterV->setObjectName("SplitterV");
        splitterH->setObjectName("SplitterH");
        splitterV->addWidget(new QPushButton("PushButton1"));
        splitterV->addWidget(new QPushButton("PushButton2"));
        splitterH->addWidget(splitterV);
        splitterH->addWidget(new QPushButton("PushButton3"));
        return setLayoutWidget({ splitterH }, { 250, 110 });
    }
    else if(name == "TabWidget")
    {
        QTabWidget* tab = new QTabWidget;
        tab->addTab(new QWidget, "Widget1");
        tab->addTab(new QWidget, "Widget2");
        tab->addTab(new QWidget, "Widget3");
        tab->setObjectName("TabWidget");
        return setLayoutWidget({ tab }, { 210, 110 });
    }
    else if(name == "TableView") //?
    {
        QTableView* view = new QTableView;
        view->setObjectName("TableView");
        view->resize(200, 100);
        return view;
    }
    else if(name == "TableWidget")
    {
        const int n = 100;
        QStringList list = { "one", "two", "three" };
        QTableWidget* table = new QTableWidget(n, n);
        table->setObjectName("TableWidget");
        table->setHorizontalHeaderLabels(list);
        table->setVerticalHeaderLabels(list);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                table->setItem(i, j, new QTableWidgetItem(QString("%1, %2").arg(i).arg(j)));
        return setLayoutWidget({ table }, { 210, 110 });
    }
    else if(name == "TextEdit")
    {
        QTextEdit* text = new QTextEdit;
        text->setObjectName("TextEdit");
        return setLayoutWidget({ text }, { 80, 80 });
    }
    else if(name == "TimeEdit")
    {
        QTimeEdit* time = new QTimeEdit;
        time->setObjectName("TimeEdit");
        return setLayoutWidget({ time }, { 80, 80 });
    }
    else if(name == "ToolButton")
    {
        QToolButton* button = new QToolButton;
        button->setText("ToolButton");
        button->setObjectName("ToolButton");
        return setLayoutWidget({ button }, { 95, 25 });
    }
    else if(name == "ToolBox")
    {
        QToolBox* box = new QToolBox;
        box->addItem(new QWidget, "Widget1");
        box->addItem(new QWidget, "Widget2");
        box->addItem(new QWidget, "Widget3");
        box->setObjectName("ToolBox");
        return setLayoutWidget({ box }, { 110, 180 });
    }
    else if(name == "TreeView") //?
    {
        QTreeView* tree = new QTreeView;
        tree->setObjectName("TreeView");
        tree->resize(200, 100);
        return tree;
    }
    else if(name == "TreeWidget")
    {
        QTreeWidget* tree = new QTreeWidget;
        tree->setObjectName("TreeWidget");
        tree->setHeaderLabels({ "Folders", "Used Space" });
        QTreeWidgetItem* item = new QTreeWidgetItem(tree);
        item->setText(0, "Local Disk");
        for(int i = 1; i < 20; i++)
        {
            QTreeWidgetItem* dir = new QTreeWidgetItem(item);
            dir->setText(0, "Directory" + QString::number(i));
            dir->setText(1, QString::number(i) + "MB");
        }
        tree->setItemExpanded(item, true);
        return setLayoutWidget({ tree }, { 210, 110 });
    }
    else if(name == "Widget")
    {
        QWidget* widget = new QWidget;
        widget->setObjectName("Widget");
        return setLayoutWidget({ widget }, { 210, 110 });
    }
    return nullptr;
}

QWidget* WidgetStyle::setLayoutWidget(const QVector<QWidget*>& vecWgt, const QSize& size)
{
    QWidget* parentWgt = new QWidget;
    parentWgt->resize(size);

    QHBoxLayout* box = new QHBoxLayout;
    for(QWidget* wgt : vecWgt)
        box->addWidget(wgt);
    box->setMargin(2);
    parentWgt->setLayout(box);
    return parentWgt;
}

void WidgetStyle::distinguishRect(const QRectF& rect)
{
    m_deleteGraphicsWgt_.clear();
    for(GraphicsWidget* wgt : m_scene->getItemWidget())
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
    for(GraphicsWidget* wgt : m_scene->getItemWidget())
        if(wgt->contains(point))
            return true;
    return false;
}

WidgetStyle::WidgetScene::WidgetScene(qreal x, qreal y, qreal widht, qreal height, WidgetStyle* parent) : QGraphicsScene(x, y, widht, height, parent)
  , m_wgtStyle(parent)
{ }

void WidgetStyle::WidgetScene::addItemWidget(GraphicsWidget* wgt)
{ m_graphicsWgt_.push_back(wgt); }

QList<GraphicsWidget*> WidgetStyle::WidgetScene::getItemWidget() const
{ return m_graphicsWgt_; }

GraphicsWidget* WidgetStyle::WidgetScene::removeWidget(GraphicsWidget* wgt)
{
    auto iter = qFind(m_graphicsWgt_.begin(), m_graphicsWgt_.end(), wgt);
    if(iter == m_graphicsWgt_.end())
        return nullptr;
    m_graphicsWgt_.erase(iter);
    return *iter;
}

void WidgetStyle::WidgetScene::clearWidget()
{ m_graphicsWgt_.clear(); }

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
            rect.setBottomLeft(m_topLeftRect);
            rect.setTopRight(point);
        }
        else if(point.x() <= m_topLeftRect.x() && point.y() >= m_topLeftRect.y())
        {
            rect.setTopRight(m_topLeftRect);
            rect.setBottomLeft(point);
        }
        else if(point.x() <= m_topLeftRect.x() && point.y() <= m_topLeftRect.y())
        {
            rect.setBottomRight(m_topLeftRect);
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
