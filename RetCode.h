#pragma once

class RetCode
{
public:
    enum ERetCode
    {
        RET_CODE_SUCCESS = 0,
        RET_CODE_BAD_FD = 1,
        RET_CODE_BAD_CONTENT = 2,
        RET_CODE_ROW_INDEX_OVERFLOW = 3,
        RET_CODE_COLUMN_INDEX_OVERFLOW = 4,
        RET_CODE_ERR = 5,
    };

public:
    RetCode(ERetCode retcode = RET_CODE_SUCCESS): _retcode(retcode) {}
    ~RetCode() {}
    ERetCode getCode() const { return _retcode; }
    RetCode(const RetCode& cpy) { _retcode = cpy.getCode(); }
    int toInt() { return static_cast<int>(_retcode); }

public:
    RetCode& operator=(const RetCode& cpy)
    {
        _retcode = cpy.getCode();
        return *this;
    }
private:
    ERetCode _retcode = RET_CODE_ERR;
};
