#pragma once

#include <vector>

#include <QByteArray>

#include "RetCode.h"

class SurfaceData
{

public:
    using TopAbsValue = double;
    using TopRelValue = double;
    using TopColor = float[3];
    struct TopInfo
    {
        TopAbsValue absValue;
        TopRelValue relValue;
        TopColor topColor;
    };

    using TopRow = std::vector<TopInfo>;
    using TopArray = std::vector<TopRow>;

public:
    explicit SurfaceData();
    ~SurfaceData();

public:
    size_t rowCount() const { return _rowCount; }
    size_t columnCount() const { return _columnCount; }
    RetCode getTopInfo(const size_t rowIndex, const size_t columnIndex, TopInfo& value);
    RetCode getTopRelValue(const size_t rowIndex, const size_t columnIndex, TopRelValue& value);
    RetCode getTopAbsValue(const size_t rowIndex, const size_t columnIndex, TopAbsValue& value);
    void setTopRelValue(const size_t rowIndex, const size_t columnIndex, const TopRelValue value);
    void setTopColor(const size_t rowIndex, const size_t columnIndex, const TopColor value);
public:
    RetCode ReadSurface(const char* filename);
    void FlushSurface();

public:
    const TopArray& getData() const { return _topArray; }
public:
    const TopRow& operator [](const int& index) const { return _topArray.at(index); }
private:
    TopArray _topArray;
    size_t _rowCount = 0;
    size_t _columnCount = 0;
};
