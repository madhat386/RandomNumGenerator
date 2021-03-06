#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "singalitem.h"
#include "arrayitem.h"
#include <QDebug>
#include <QFileDialog>

/**
 * @brief MainWindow::MainWindow
 * @param parent
 * @author madhat
 * @date 2021-03-07
 */

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    srand((unsigned)time(nullptr));
    ui->setupUi(this);
    this->setFixedWidth(1000);
    this->setFixedHeight(600);
    this->setWindowTitle("随机数字(组)样本生成器");

    connect(ui->sBtnAdd, &QPushButton::clicked, [ = ]() {
        Item* item = new SingalItem(this);
        item->isArray = false;
        item->min = ui->sMin->text().toDouble();
        item->max = ui->sMax->text().toDouble();
        item->isInt = ui->sIsFloat->isChecked() ? false : true;
        item->endOfVal = ui->sIsSpace->isChecked() ? ' ' : '\n';
        if (ui->sNumOfDecimal->text() == "") {
            item->numOfDecimal = -1;
        } else {
            item->numOfDecimal = ui->sNumOfDecimal->text().toInt();
        }
        itemList.push_back(item);
        QMessageBox::information(this, "提示", "添加成功");
    });


    connect(ui->aBtnAdd, &QPushButton::clicked, [ = ]() {
        ArrayItem* item = new ArrayItem(this);
        item->isArray = true;
        item->min = ui->aMin->text().toDouble();
        item->max = ui->aMax->text().toDouble();
        item->minLen = ui->aMinLen->text().toInt();
        item->maxLen = ui->aMaxLen->text().toInt();
        item->isInt = ui->aIsFloat->isChecked() ? false : true;
        item->endOfVal = ui->aIsSpace->isChecked() ? ' ' : '\n';
        item->showAmount = ui->addAmout->checkState() == Qt::Checked;
        if (ui->aNumOfDecimal->text() == "") {
            item->numOfDecimal = -1;
        } else {
            item->numOfDecimal = ui->aNumOfDecimal->text().toInt();
        }
        itemList.push_back(item);
        QMessageBox::information(this, "提示", "添加成功");
    });


    connect(ui->btnGenerate, &QPushButton::clicked, [ = ]() {
        int amount = ui->amount->text().toInt();
        QString path = QFileDialog::getExistingDirectory(this, "选择生成文件路径", "");


        for (int i = 0; i < amount; ++i) {
            qDebug() << QString(i);
            QString savePath = path + "/" + QString::number(i + 1) + ".in";
            QFile file;
            file.setFileName(savePath);
            file.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream stream(&file);

            for(QVector<Item*>::iterator it = itemList.begin(); it != itemList.end(); ++it) {
                if (!(*it)->isArray) {
                    //处理单个随机数
                    SingalItem* temp = static_cast<SingalItem*>(*it);
                    if (temp->isInt) {
                        int val = getRandomInt(temp->min, temp->max);
                        stream << val << temp->endOfVal;
                    } else {
                        //单个浮点型随机数处理
                        QString str = getRandomDouble(temp->min, temp->max, temp->numOfDecimal);
                        stream << str << temp->endOfVal;
                    }
                } else {
                    // 随机数组处理
                    ArrayItem* temp = static_cast<ArrayItem*>(*it);
                    int len = getRandomInt(temp->minLen, temp->maxLen);
                    if (temp->showAmount) {
                        stream << len << temp->endOfVal;
                    }
                    if (temp->isInt) {
                        //处理整数数组生成
                        for (int i = 0; i < len; ++i) {
                            if(i == len - 1) {
                                stream << getRandomInt(temp->min, temp->max);
                            } else {
                                stream << getRandomInt(temp->min, temp->max) << temp->endOfVal;
                            }
                        }
                    } else {
                        //TODO 处理浮点型数组生成
                        for(int i = 0; i < len; ++i) {
                            QString str = getRandomDouble(temp->min, temp->max, temp->numOfDecimal);
                            if(i == len - 1) {
                                stream << str;
                            } else {
                                stream << str << temp->endOfVal;
                            }
                        }
                    }
                }
            }
            file.close();

        }
        QMessageBox::information(this, "提示", "生成成功");
    });

    connect(ui->btnReset, &QPushButton::clicked, [ = ]() {
        ui->sMax->setText("");
        ui->sMin->setText("");
        ui->amount->setText("5");
        ui->sIsInt->setChecked(true);
        ui->sIsNextLine->setChecked(true);
        ui->aIsInt->setChecked(true);
        ui->aIsNextLine->setChecked(true);
        ui->aMax->setText("");
        ui->aMin->setText("");
        ui->aMaxLen->setText("");
        ui->aMinLen->setText("");
        ui->addAmout->setCheckState(Qt::Checked);
        ui->sNumOfDecimal->setText("");
        ui->aNumOfDecimal->setText("");
        for(QVector<Item*>::iterator it = itemList.begin(); it != itemList.end(); ++it) {
            if ((*it) != nullptr) {
                delete *it;
                *it = nullptr;
            }
        }
        itemList.clear();
        QMessageBox::information(this, "提示", "已重置数据");
    });

}

MainWindow::~MainWindow() {
    delete ui;
}

int MainWindow::getRandomInt(int min, int max) {
    int val = min + (rand() % ((max - min) + 1));
    return val;
}

QString MainWindow::getRandomDouble(double min, double max, int len) {
    //根据最小值和最大值，随机生成小数
    double val = min + (double)(rand()) / RAND_MAX * (max - min);
    if (len == -1) {
        return QString::number(val, 'f');
    }
    return QString::number(val, 'f', len);
}
