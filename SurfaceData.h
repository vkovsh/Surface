#pragma once

#include <vector>

#include <QByteArray>

#include "RetCode.h"

class SurfaceData
{

private:
    using TopValue = int;
    using TopRow = std::vector<TopValue>;
    using TopArray = std::vector<TopRow>;

public:
    explicit SurfaceData();
    ~SurfaceData();

public:
    size_t rowCount() const { return _rowCount; }
    size_t columnCount() const { return _columnCount; }
    RetCode getTopValue(const size_t rowIndex, const size_t columnIndex, TopValue& value);

public:
    RetCode ReadSurface(const char* filename);
    void FlushSurface();

private:
    TopArray _topArray;
    size_t _rowCount = 0;
    size_t _columnCount = 0;
};
