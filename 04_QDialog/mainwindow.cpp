#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QColorDialog>
#include <QFileDialog>
#include <QFontDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //点击新建按钮，弹出一个对话框Dialog  //triggered：动作触发
    connect(ui->actionNew, &QAction::triggered, [=](){
        //对话框 分类
        //模态对话框（不可以对其它窗口操作） 非模态对话框（可以对其它窗口操作）

        //模态对话框  阻塞
//        QDialog dlg(this);
//        dlg.resize(200, 100);  //默认的对话框窗体很小，输出栏会报错
//        dlg.exec(); //因为这个函数，阻塞，所以该栈上的内存没被释放

        //非模态对话框
        //要用指针类型动态分配在堆区，不然的话对话框会在lambda表达式结束后消失 QDialog dlg2(this);不行
//        QDialog *dlg2 = new QDialog(this);
//        dlg2->resize(200, 100);
//        dlg2->show();
//        dlg2->setAttribute(Qt::WA_DeleteOnClose);//设置对话框在点击关闭按钮时释放堆区对象


        //消息对话框
        //错误对话框
        //QMessageBox::critical(this, "critical", "错误");
        //信息对话框
        //QMessageBox::information(this, "info", "信息");
        //提问对话框       参数1 父亲  参数2 标题  参数3 提示内容          参数4 按键类型    参数5 默认关联回车按键
//        if(QMessageBox::Save == QMessageBox::question(this, "ques", "提问", QMessageBox::Save | QMessageBox::Cancel, QMessageBox::Cancel)) {
//            qDebug() << "已保存";
//        }
        //警示对话框
        //QMessageBox::warning(this, "Warning", "警告");

        //其他标准对话框
        //颜色对话框
        //QColor color = QColorDialog::getColor(QColor(255, 0, 0));
        //qDebug() << "r = " << color.red() << " g = " << color.green() << " b = " << color.blue() << endl;

        //文件对话框
        //QString str = QFileDialog::getOpenFileName(this, "打开文件", "D:\\MLZ107\\Desktop", "(*.txt)");
        //qDebug() << str << endl;

        //字体对话框
        bool flag;
        QFont font = QFontDialog::getFont(&flag, QFont("仿宋", 14));
        qDebug() << "字体：" << font.family() << " 字号：" << font.pointSize() << " 是否加粗：" << font.bold() << " 是否倾斜：" << font.italic();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
