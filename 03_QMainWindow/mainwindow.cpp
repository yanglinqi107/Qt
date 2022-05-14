#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QPushButton>
#include <QLabel>
#include <QDockWidget>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //重置窗口大小
    resize(600, 400);
    setWindowTitle("这是setWindowTitle");

    //1、菜单栏创建，最多只有一个
    QMenuBar *bar = menuBar();
    setMenuBar(bar);

    //创建菜单
    QMenu *fileMenu = bar->addMenu("文件");
    QMenu *editMenu = bar->addMenu("编辑");

    //创建菜单项
    QAction *newAction =  fileMenu->addAction("新建");
    //添加分隔线
    fileMenu->addSeparator();
    QAction *openAction = fileMenu->addAction("打开");

    //2、工具栏，可以有多个
    QToolBar *toolBar = new QToolBar(this);
    addToolBar(Qt::LeftToolBarArea, toolBar);

    //设置移动（总开关）
    toolBar->setMovable(false);
    //设置停靠范围
    toolBar->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea);
    //设置浮动
    toolBar->setFloatable(false);

    //工具栏中设置内容
    toolBar->addAction(newAction);
    toolBar->addSeparator();    //分隔线
    toolBar->addAction(openAction);
    //工具栏中添加控件
    QPushButton *btn = new QPushButton("aa", this);
    toolBar->addWidget(btn);    //添加按钮

    //3、状态栏
    QStatusBar *stBar = statusBar();
    //设置到窗口中
    setStatusBar(stBar);
    //添加标签控件
    QLabel * label = new QLabel("提示信息", this);
    stBar->addWidget(label);    //添加标签
    QLabel * label2 = new QLabel("最右边", this);
    stBar->addPermanentWidget(label2);  //添加标签在最右边

    //4、铆接部件 浮动窗口 可以多个
    QDockWidget *dockWidget = new QDockWidget("浮动", this);
    //设置到窗口中
    addDockWidget(Qt::BottomDockWidgetArea, dockWidget);
    //设置后期停靠区域，只允许上下
    dockWidget->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);

    //5、设置中心部件，只能一个
    QTextEdit *textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}
