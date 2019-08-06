#include <fcntl.h>
#include <unistd.h>

#include <QList>
#include <iostream>

#include "SurfaceData.h"

SurfaceData::SurfaceData()
{}

SurfaceData::~SurfaceData()
{}

RetCode SurfaceData::ReadSurface(const char* filename)
{
    constexpr size_t BUFF_SIZE = 4096;
    char BUFF[BUFF_SIZE + 1];
    memset(BUFF, 0, BUFF_SIZE + 1);
    const int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        return RetCode::RET_CODE_BAD_FD;
    }

    ssize_t byte_count;
    QByteArray dataRaw;
    while ((byte_count = read(fd, BUFF, BUFF_SIZE)) != 0)
    {
        BUFF[byte_count] = '\0';
        dataRaw += BUFF;
    }

    if (close(fd) == -1)
    {
        return RetCode::RET_CODE_BAD_FD;
    }

    QList<QByteArray> rowsTxt = dataRaw.split('\n');
    {
        if (rowsTxt[rowsTxt.size() - 1] == "")
        {
            rowsTxt.pop_back();
        }
        _rowCount = static_cast<size_t>(rowsTxt.size());
        for (const QByteArray& rowTxt : rowsTxt)
        {
            TopRow row = TopRow();
            const QList<QByteArray> tokensTxt = rowTxt.split(' ');
            if (_columnCount == 0)
            {
                _columnCount = static_cast<size_t>(tokensTxt.size()) - 1;
            }
            else if (static_cast<size_t>(tokensTxt.size()) - 1 != _columnCount)
            {
                return RetCode::RET_CODE_BAD_CONTENT;
            }
            for (const QByteArray& tokenTxt : tokensTxt)
            {
                if (tokenTxt != "")
                {
                    bool ok;
                    row.push_back(tokenTxt.toInt(&ok));
                    if (false == ok)
                    {
                        return RetCode::RET_CODE_BAD_CONTENT;
                    }
                }
            }
            _topArray.push_back(row);
        }
    }

//    for (const TopRow& row : _topArray)
//    {
//        for (const TopValue& top : row)
//        {
//            printf("%d ", top);
//        }
//        std::cout << "\n";
//    }
    return RetCode::RET_CODE_SUCCESS;
}

void SurfaceData::FlushSurface()
{
    _rowCount = 0;
    _columnCount = 0;
    _topArray.clear();
}

RetCode SurfaceData::getTopValue(const size_t rowIndex, const size_t columnIndex, SurfaceData::TopValue& value)
{
    if (rowIndex >= _topArray.size())
        return RetCode::RET_CODE_ROW_INDEX_OVERFLOW;

    TopRow row = _topArray.at(rowIndex);
    if (columnIndex >= row.size())
        return RetCode::RET_CODE_COLUMN_INDEX_OVERFLOW;

    value = row.at(columnIndex);
    return RetCode::RET_CODE_SUCCESS;
}

void SurfaceData::setTopValue(const size_t rowIndex, const size_t columnIndex, const TopValue value)
{
    _topArray.at(rowIndex).at(columnIndex) = value;
}

