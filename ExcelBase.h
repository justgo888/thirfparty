#ifndef EXCELBASE_H
#define EXCELBASE_H

#include "qt_windows.h"
#include <windows.h>
#include "common_head_files/common_header_files.h"
#include "common_head_files/QT_CommonHeadFiles.h"


enum    DataType
{
    FIRED_CARD_TYPE,
    READ_CARDS,
};
Q_DECLARE_METATYPE(DataType);


class OptionExcel
{
public:
    QString     filePath;

    bool        isOpenExcel;
    bool        isSave;

    u8          writeColumnNum;
    u32         writeRowNum;

    QAxObject   *excel;
    QAxObject   *workbooks;//当前工作簿
    QAxObject   *workbook;//打开指定工作簿
    QAxObject   *workSheets;//sheets
    QAxObject   *workSheet;//sheet


    OptionExcel();
    ~OptionExcel();
    void        init();
    void        setFilePath(QString _filePath);
    void        setProperty(bool _isOpenExcel,bool _isSave);
    bool        openExcel();
    void        createNewExcelFile();
    void        SaveAndClose();
    void        releaseSources();
    void        setCellValue(QString ColunmName,u32 row,QString value);
};












#endif // EXCELBASE_H
