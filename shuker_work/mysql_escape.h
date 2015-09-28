#include <stdlib.h>
#include <string>
using namespace std;

/*
  Escape string with backslashes (\)

  SYNOPSIS
    mysql_escape_string_linux()
    to                  Buffer for escaped string
    from                The string to escape
    length              The length of the string to escape

  DESCRIPTION
    This escapes the contents of a string by adding backslashes before special
    characters, and turning others into specific escape sequences, such as
    turning newlines into \n and null bytes into \0.

  NOTE
    To maintain compatibility with the old C API, to_length may be 0 to mean
    "big enough"

  RETURN VALUES
    (size_t) -1 The escaped string did not fit in the to buffer
    #           The length of the escaped string
*/

size_t mysql_escape_string_linux(char *to, const char *from, size_t length)
{
  const char *to_start= to;
  const char *end, *to_end=to_start + 2*length;
  bool overflow= false;

  for (end= from + length; from < end; from++)
  {
    char escape= 0;
    switch (*from) {
    case 0:				/* Must be escaped for 'mysql' */
      escape= '0';
      break;
    case '\n':				/* Must be escaped for logs */
      escape= 'n';
      break;
    case '\r':
      escape= 'r';
      break;
    case '\\':
      escape= '\\';
      break;
    case '\'':
      escape= '\'';
      break;
    case '"':				/* Better safe than sorry */
      escape= '"';
      break;
    case '\032':			/* This gives problems on Win32 */
      escape= 'Z';
      break;
    }
    if (escape)
    {
      if (to + 2 > to_end)
      {
        overflow= true;
        break;
      }
      *to++= '\\';
      *to++= escape;
    }
    else
    {
      if (to + 1 > to_end)
      {
        overflow= true;
        break;
      }
      *to++= *from;
    }
  }
  *to= 0;
  return overflow ? (size_t) -1 : (size_t) (to - to_start);
};



string& EscapeString(string &str)
{
	char* pszTempBuf = new char[str.length()*2+1];
	mysql_escape_string_linux(pszTempBuf, str.c_str(), str.length()) ;
	str = pszTempBuf;
	delete[] pszTempBuf;
	return str;
};

string EscapeString2(string str)
{
	char* pszTempBuf = new char[str.length()*2+1];
	mysql_escape_string_linux(pszTempBuf, str.c_str(), str.length()) ;
	str = pszTempBuf;
	delete[] pszTempBuf;
	return str;
};

