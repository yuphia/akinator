#ifndef ERR_H
#define ERR_H 1

enum Errors
{
    NO_ERROR,
    UNREC_ERROR,
    NULL_POINTER,
    ALLOC_ERROR,
    FILE_OPEN_ERROR,
    FILE_DEAD,
    STRCHR_ERROR,
    DESCR_UNSEEKABLE,
    FPRINTF_ERROR,
    FFLUSH_ERROR,
    BAD_ARG,
    GETLINE_REALLOC_ERROR,
    STREAM_BLOCKED, //EAGAIN
    STREAM_INVALID, //EBADF
    SIGNAL_INTERRUPT, //EINTR
    MEM_ERROR, //ENOMEM
    INT_CAST_ERROR //ERANGE
};

#define passErr() if (tempErr != NO_ERROR)\
                        return tempErr

#define checkNullptr(pointer) if (pointer == nullptr)\
                                return NULL_POINTER;

#define checkFile(stream) if (stream == nullptr)\
                                return FILE_DEAD;

#endif