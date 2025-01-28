https://www.zhihu.com/collection/975967345

#### 环境
开发环境  cpp编译器 Qt库 QtCreator(本身不带编译功能 使用 visual studio的 cl)
第一个Qt窗口
Qt官方案例 
#####    1. 打开并运行.pro项目: 

#####    2. QtTextEdit 文本框 C:\Qt\Qt5.14.2\Examples\Qt-5.14.2\widgets\tutorials\gettingStarted\gsQt\part1
```cpp
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTextEdit textEdit;
    textEdit.show();

    return app.exec();
}
```
```pro
QT += widgets
SOURCES = main.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/tutorials/gettingStarted/gsQt/part1
INSTALLS += target

```

#####    3. QWidget 窗口: C:\Qt\Qt5.14.2\Examples\Qt-5.14.2\widgets\tutorials\widgets\toplevel
```cpp
//! [main program]
#include <QtWidgets>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
//! [create, resize and show]
    QWidget window;
    window.resize(320, 240);
    window.show();
//! [create, resize and show]
    window.setWindowTitle(
        QApplication::translate("toplevel", "Top-level widget"));
    return app.exec();
}
//! [main program]
```
```pro
QT += widgets

SOURCES = main.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/tutorials/widgets/toplevel
INSTALLS += target
```
        设置窗口标题 setWindowTitle
        显示窗口 show
        改变窗口大小 resize
#####    4. QHBoxLayout 水平布局器(Qt对象的声明周期): C:\Qt\Qt5.14.2\Examples\Qt-5.14.2\widgets\tutorials\widgets\windowlayout
```cpp
//! [main program]
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;
//! [create, lay out widgets and show]
    QLabel *label = new QLabel(QApplication::translate("windowlayout", "Name:"));
    QLineEdit *lineEdit = new QLineEdit();

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(label);
    layout->addWidget(lineEdit);
    window.setLayout(layout);
//! [create, lay out widgets and show]
    window.setWindowTitle(
        QApplication::translate("windowlayout", "Window layout"));
    window.show();
    return app.exec();
}
//! [main program]
```
```pro
QT += widgets

SOURCES = main.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/tutorials/widgets/windowlayout
INSTALLS += target
```
        文本标签 QLabel
        行输入框 QLineEdit
        添加子窗口 addWidget
        设置布局器 setLayout
#####    5. QVBoxLayout 垂直布局其 (connect 与 信号槽): C:\Qt\Qt5.14.2\Examples\Qt-5.14.2\widgets\tutorials\gettingStarted\gsQt\part2
```cpp
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTextEdit *textEdit = new QTextEdit;
    QPushButton *quitButton = new QPushButton("&Quit");

    QObject::connect(quitButton, &QPushButton::clicked,
                     qApp, &QApplication::quit);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(textEdit);
    layout->addWidget(quitButton);

    QWidget window;
    window.setLayout(layout);

    window.show();

    return app.exec();
}
```
```pro
QT += widgets
SOURCES = main.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/tutorials/gettingStarted/gsQt/part2
INSTALLS += target

```
        文本框
        按钮
#####   6. 自定义窗口类(继承QWidget) 自定义信号槽: C:\Qt\Qt5.14.2\Examples\Qt-5.14.2\widgets\tutorials\gettingStarted\gsQt\part3
```cpp
#include <QtWidgets>

class Notepad : public QWidget
{
    Q_OBJECT

public:
    Notepad();

private slots:
    void quit();

private:
    QTextEdit *textEdit;
    QPushButton *quitButton;

};

Notepad::Notepad()
{
    textEdit = new QTextEdit;
    quitButton = new QPushButton(tr("Quit"));

    connect(quitButton, &QPushButton::clicked,
            this, &Notepad::quit);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(textEdit);
    layout->addWidget(quitButton);

    setLayout(layout);

    setWindowTitle(tr("Notepad"));
}

void Notepad::quit()
{
    QMessageBox messageBox;
    messageBox.setWindowTitle(tr("Notepad"));
    messageBox.setText(tr("Do you really want to quit?"));
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    messageBox.setDefaultButton(QMessageBox::No);
    if (messageBox.exec() == QMessageBox::Yes)
        qApp->quit();
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Notepad notepad;
    notepad.show();

    return app.exec();
}

#include "main.moc"
```
```pro
QT += widgets
SOURCES = main.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/tutorials/gettingStarted/gsQt/part3
INSTALLS += target
```

        声明
        槽函数声明
        对话框
#####   7.QMainWindow 窗口与菜单栏: C:\Qt\Qt5.14.2\Examples\Qt-5.14.2\widgets\tutorials\gettingStarted\gsQt\part4
```cpp
#include <QtWidgets>

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    Notepad();

private slots:
    void load();
    void save();

private:
    QTextEdit *textEdit;

    QAction *loadAction;
    QAction *saveAction;
    QAction *exitAction;

    QMenu *fileMenu;
};

Notepad::Notepad()
{
    loadAction = new QAction(tr("&Load"), this);
    saveAction = new QAction(tr("&Save"), this);
    exitAction = new QAction(tr("E&xit"), this);

    connect(loadAction, &QAction::triggered,
            this, &Notepad::load);
    connect(saveAction, &QAction::triggered,
            this, &Notepad::save);
    connect(exitAction, &QAction::triggered,
            qApp, &QApplication::quit);

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(loadAction);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    textEdit = new QTextEdit;
    setCentralWidget(textEdit);

    setWindowTitle(tr("Notepad"));
}

void Notepad::load()
{

}

void Notepad::save()
{

}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Notepad notepad;
    notepad.show();

    return app.exec();
};

#include "main.moc"
```
```pro
QT += widgets
SOURCES = main.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/tutorials/gettingStarted/gsQt/part4
INSTALLS += target
```
        中央窗口
        菜单栏
        添加菜单
        菜单项
        添加菜单向
        菜单项点击事件
#####   8.QFileDialog 文件浏览 与QFile QTextStream 文件读写: C:\Qt\Qt5.14.2\Examples\Qt-5.14.2\widgets\tutorials\gettingStarted\gsQt\part5
```cpp
#include <QtWidgets>

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    Notepad();

private slots:
    void open();
    void save();

private:
    QTextEdit *textEdit;

    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;

    QMenu *fileMenu;
};

Notepad::Notepad()
{
    openAction = new QAction(tr("&Load"), this);
    saveAction = new QAction(tr("&Save"), this);
    exitAction = new QAction(tr("E&xit"), this);

    connect(openAction, &QAction::triggered,
            this, &Notepad::open);
    connect(saveAction, &QAction::triggered,
            this, &Notepad::save);
    connect(exitAction, &QAction::triggered,
            qApp, &QApplication::quit);

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    textEdit = new QTextEdit;
    setCentralWidget(textEdit);

    setWindowTitle(tr("Notepad"));
}

void Notepad::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
        tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QTextStream in(&file);
        textEdit->setText(in.readAll());
        file.close();
    }
}

void Notepad::save()
{

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",
        tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            // error message
        } else {
            QTextStream stream(&file);
            stream << textEdit->toPlainText();
            stream.flush();
            file.close();
        }
    }
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Notepad notepad;
    notepad.show();

    return app.exec();
}

#include "main.moc"


```
```pro
QT += widgets
requires(qtConfig(filedialog))
SOURCES = main.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/tutorials/gettingStarted/gsQt/part5
INSTALLS += target
```
        文件对象
        读打开
        写打开
        关闭文件
        文本流对象
        读全部文件
        写全部文件
        刷数据到文件中

#### Qt打开现有CMake工程
QtCreator是靠浏览打开一个本机的CMakeLists.txt文件来开始识别和使用一个CMake工程的。
只需要用QtCreator打开根目录下的那个CMakeLists.txt文件即可打开整个完整的工程。

#### 基础类
QString 常用操作
```cpp
#include <QString>
#include <QDebug>

int main(int argc, char *argv[])
{
    int i = 1;
    int age = 18;
    QString name("jerry");
    // 格式化
    QString status = QString("i %1, age %2, name %3").arg(i).arg(age).arg(name);
    qDebug() << status;

    double weight = 65.230;
    // float 格式化
    auto str = QString::number(weight, 'f', 2);//两位小数
    qDebug() << str;

    bool success = true;
    // bool 格式化
    qDebug() << QString::number(success);

    return 0;
}
```

#### Qt窗口坐标 QScreenSize/
Qt 窗口坐标与鼠标坐标
Qt 实时显示鼠标坐标与屏幕分辨率
 Qtcreator中创建cmake项目, clion的toolchain配置中选定 Qt mingw64 导入qt相关包，加载cmakelists文件导入项目即可即可

#### Qt事件基础 QtKeyEscape/ QtMouseMoveEvent/ qmake(.pro)
鼠标事件
键盘事件
窗口绘制
项目1 Qt贪吃蛇 QSnake(cmakelists)
定时事件 Qtimer make(cmakelists)
项目2 计算圆周率Π (蒙特卡洛) MonteCarlo(cmakelists)

#### 图片显示 CxxBMP/ (cmakelists)
QPixmap 

#### 颜色 QPaintRGB/
Qt 验证 RGB 格式 QPaintRGB(cmakelist err: undefined to "__imp__ZN11QMainWindow11qt_metacastEPKc" 需要导入msvc)

#### 项目 ChessQt/ (cmakelists 嵌套完整项目 )
项目3 中国象棋Qt实现
     vscode 搜索功能 (基于文本单词搜索)
     计算器 (基于表达式求值)
     

#### 常见错误
Unable to create a debugging engine
the c++ compiler is not able to ocmpte a simple test
err MSB1009: 项目不存在

#### 打包 exe
```cmd
cd build && windeployqt.exe --release --dir "C:\MyApp" "C:\path\to\your\app\release\myapp.exe"
```