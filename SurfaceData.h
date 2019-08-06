#pragma once

#include <vector>

#include <QByteArray>

#include "RetCode.h"

class SurfaceData
{

public:
    using TopValue = double;
    using TopRow = std::vector<TopValue>;
    using TopArray = std::vector<TopRow>;

public:
    explicit SurfaceData();
    ~SurfaceData();

public:
    size_t rowCount() const { return _rowCount; }
    size_t columnCount() const { return _columnCount; }
    RetCode getTopValue(const size_t rowIndex, const size_t columnIndex, TopValue& value);
    void setTopValue(const size_t rowIndex, const size_t columnIndex, const TopValue value);
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
