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
                    TopInfo info;
                    info.absValue = tokenTxt.toInt(&ok);
                    info.relValue = 0;
                    row.push_back(info);
                    if (false == ok)
                    {
                        return RetCode::RET_CODE_BAD_CONTENT;
                    }
                }
            }
            _topArray.push_back(row);
        }
    }
    return RetCode::RET_CODE_SUCCESS;
}

void SurfaceData::FlushSurface()
{
    _rowCount = 0;
    _columnCount = 0;
    _topArray.clear();
}

RetCode SurfaceData::getTopInfo(const size_t rowIndex, const size_t columnIndex, TopInfo& value)
{
    if (rowIndex >= _topArray.size())
    {
        return RetCode::RET_CODE_ROW_INDEX_OVERFLOW;
    }

    TopRow row = _topArray.at(rowIndex);
    if (columnIndex >= row.size())
    {
        return RetCode::RET_CODE_COLUMN_INDEX_OVERFLOW;
    }

    value = row.at(columnIndex);
    return RetCode::RET_CODE_SUCCESS;
}

void SurfaceData::setTopRelValue(const size_t rowIndex, const size_t columnIndex, const TopRelValue value)
{
    _topArray.at(rowIndex).at(columnIndex).relValue = value;
}

RetCode SurfaceData::getTopAbsValue(const size_t rowIndex, const size_t columnIndex, TopAbsValue& value)
{
    value = _topArray.at(rowIndex).at(columnIndex).absValue;
    return RetCode::RET_CODE_SUCCESS;
}

RetCode SurfaceData::getTopRelValue(const size_t rowIndex, const size_t columnIndex, TopRelValue& value)
{
    value = _topArray.at(rowIndex).at(columnIndex).relValue;
    return RetCode::RET_CODE_SUCCESS;
}

void SurfaceData::setTopColor(const size_t rowIndex, const size_t columnIndex, const TopColor value)
{
//    memcpy((void*)_topArray.at(rowIndex).at(columnIndex).topColor, (void*)value, sizeof(value)*3);
    _topArray.at(rowIndex).at(columnIndex).topColor[0] = value[0];
    _topArray.at(rowIndex).at(columnIndex).topColor[0] = value[1];
    _topArray.at(rowIndex).at(columnIndex).topColor[0] = value[2];
}
