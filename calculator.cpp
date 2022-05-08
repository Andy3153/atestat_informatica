#include "calculator.h"
#include "./ui_calculator.h"

double calcVal = 0.0;
double mrVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;
bool mrTrigger = false;
bool mpTrigger = false;
bool mmTrigger = false;

Calculator::Calculator(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];

    for(int i=0; i<10; ++i)
    {
        QString butName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    connect(ui->ButtonPlus, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->ButtonMinus, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->ButtonMultiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->ButtonDivide, SIGNAL(released()), this, SLOT(MathButtonPressed()));

    connect(ui->ButtonEquals, SIGNAL(released()), this, SLOT(EqualButtonPressed()));
    connect(ui->ButtonChSign, SIGNAL(released()), this, SLOT(ChSignPressed()));
    connect(ui->ButtonClear, SIGNAL(released()), this, SLOT(ClearButtonPressed()));
//    connect(ui->ButtonBksp, SIGNAL(released()), this, SLOT(ButtonBkspPressed()));
    connect(ui->ButtonMemResult, SIGNAL(released()), this, SLOT(MemResultButtonPressed()));
    connect(ui->ButtonMemClear, SIGNAL(released()), this, SLOT(MemClearButtonPressed()));
    connect(ui->ButtonMemPlus, SIGNAL(released()), this, SLOT(MemButtonPressed()));
    connect(ui->ButtonMemMinus, SIGNAL(released()), this, SLOT(MemButtonPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}

// Actiunea pentru apasarea cifrelor
void Calculator::NumPressed()
{
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();

    if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0))
        ui->Display->setText(butVal);
    else
    {
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16)); //scrie numarul in exponenti daca trece de 16 cifre
    }
}

// Actiunea pentru apasarea semnelor
void Calculator::MathButtonPressed()
{
    //reseteaza valorile semnelor
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;

    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();

    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();

    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0)
        divTrigger = true;
    else if(QString::compare(butVal, "*", Qt::CaseInsensitive) == 0)
        multTrigger = true;
    else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0)
        addTrigger = true;
    else if(QString::compare(butVal, "-", Qt::CaseInsensitive) == 0)
        subTrigger = true;

    ui->Display->setText(""); //sterge ecran dupa apasarea semnului
}

// Actiunea pentru apasarea egalului
void Calculator::EqualButtonPressed()
{
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();

    //calcularea solutiei
    if(addTrigger || subTrigger || multTrigger || divTrigger)
    {
        if(addTrigger) solution = calcVal + dblDisplayVal;
        else if(subTrigger) solution = calcVal - dblDisplayVal;
        else if(multTrigger) solution = calcVal * dblDisplayVal;
        else if(divTrigger) solution = calcVal / dblDisplayVal;
    }
    ui->Display->setText(QString::number(solution)); //afisare rezultat
}

// Actiunea pentru schimbarea semnului
void Calculator::ChSignPressed()
{
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    double dblDisplayValSign = -1 * dblDisplayVal;
    ui->Display->setText(QString::number(dblDisplayValSign)); //arata schimbarea semnului pe ecran
}

// Actiunea pentru apasarea de clear
void Calculator::ClearButtonPressed()
{
    ui->Display->setText(QString::number(0.0));
}

// Actiunea pentru apasarea butoanelor de memorie
void Calculator::MemButtonPressed()
{
    //reseteaza valorile butoanelor
    mpTrigger = false;
    mmTrigger = false;

//    mrVal = 0.0;

    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();

    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();

    if(QString::compare(butVal, "M+", Qt::CaseInsensitive) == 0)
        mpTrigger = true;
    else if(QString::compare(butVal, "M-", Qt::CaseInsensitive) == 0)
        mmTrigger = true;

    if(mpTrigger || mmTrigger)
    {
        if(mpTrigger) mrVal = mrVal + dblDisplayVal;
        else if(mmTrigger) mrVal = mrVal - dblDisplayVal;
    }

}

// Actiunea pentru apasarea rezultatului de memorie
void Calculator::MemResultButtonPressed()
{
    ui->Display->setText(QString::number(mrVal)); //afisare rezultat
    mrVal = 0.0;
}

void Calculator::MemClearButtonPressed()
{
    mrVal = 0.0;
}
