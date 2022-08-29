#include "ExcelBase.h"
#include<ole2.h>








OptionExcel::OptionExcel()
{
    qRegisterMetaType<DataType>("DataType");
    workSheet=nullptr;
    workSheets=nullptr;
    workbook=nullptr;
    workbooks=nullptr;
    excel=nullptr;
}

OptionExcel::~OptionExcel()
{
    releaseSources();
}

void OptionExcel::init()
{

    CoInitializeEx(NULL, COINIT_MULTITHREADED);


    excel=new QAxObject("Excel.Application");
    //    if(excel->setControl("Excel.Application"))
    //    {

    //    }
    //    else
    //    {
    //        excel->setControl("ket.Application");
    //    }
    setProperty(true,true);
}



void OptionExcel::setFilePath(QString _filePath)
{
    u8 file_index=1;
    QDateTime current_time=QDateTime::currentDateTime();
    QString time_str=current_time.toString("MM-dd-hh-mm-ss");
    filePath=qApp->applicationDirPath()+"/"+time_str+_filePath+".xlsx";
    while(!check_FileHasCreate(filePath))
    {
        filePath=qApp->applicationDirPath()+"/"+time_str+_filePath+QString::number(file_index++)+".xlsx";
    }
}

void OptionExcel::setProperty(bool _isOpenExcel, bool _isSave)
{
    isOpenExcel=_isOpenExcel;
    isSave=_isSave;
    excel->setProperty("Visible",isOpenExcel);
    excel->setProperty("DisplayAlerts",isSave);

    workbooks=excel->querySubObject("WorkBooks");
}



/************************************
 *打开已有的Excel
************************************/
bool OptionExcel::openExcel()
{
//    QXlsx::Document xlsx;
//    xlsx.write("A1", "");
//    xlsx.saveAs("a.xlsx");

    filePath="E:\\QT_Project\\build-readCardsInfoTools-Desktop_Qt_5_15_2_MinGW_64_bit-Debug\\debug\\firecards.xlsx";
    QFileInfo info(filePath);
    qDebug()<<filePath;
    if (!info.exists())
    {
        qDebug()<<"excel文件不存在";
    }else
    {
        qDebug()<<"excel文件存在";
    }
    //mWorkBook = mWorkBooks->querySubObject("Open(const QString &)", info.absoluteFilePath());
    workbook=workbooks->querySubObject("Open(const QString&)",filePath);
    if(workbook)
    {
        workSheets=workbook->querySubObject("Sheets");
        workSheet=workSheets->querySubObject("Item(int)",1);
        return true;
    }
    return false;
}

void OptionExcel::createNewExcelFile()
{
    workbooks=excel->querySubObject("WorkBooks");
    workbooks->dynamicCall("Add");
    workbook=excel->querySubObject("ActiveWorkBook");
    workSheets=workbook->querySubObject("Sheets");
    workSheet=workSheets->querySubObject("Item(int)",1);
}

void OptionExcel::SaveAndClose()
{
    workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(filePath.replace('/','\\')));
    workbook->dynamicCall("Close()");
    excel->dynamicCall("Quit()");
}

void OptionExcel::releaseSources()
{
    if(workSheet) delete      workSheet;
    if(workSheets) delete      workSheets;
    if(workbook) delete      workbook;
    if(workbooks) delete    workbooks;
    if(excel) delete    excel;


    workSheet=nullptr;
    workSheets=nullptr;
    workbook=nullptr;
    workbooks=nullptr;
    excel=nullptr;
    OleUninitialize();
}

void OptionExcel::setCellValue(QString ColunmName, u32 row, QString value)
{
    ColunmName=ColunmName+QString::number(row);
    QAxObject *cell=workSheet->querySubObject("Range(QVariant, QVariant)",ColunmName);
    cell->setProperty("Value",value);
}






