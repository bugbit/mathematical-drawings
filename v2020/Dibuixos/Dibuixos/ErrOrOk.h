#ifndef __ERROROK_H__

#define	__ERROROK_H__

#include <string>

#define	__OK__	NULL

typedef std::string *ErrOrOk;

inline ErrOrOk ThrowError(const char *str)
{
	return new std::string(str);
}

inline ErrOrOk ThrowError(std::string *str)
{
	return str;
}

inline bool IsOk(ErrOrOk e)
{
	return e == __OK__;
}

#endif // !__ERROROK_H__

