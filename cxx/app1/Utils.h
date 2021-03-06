#ifndef Utils_h
#define Utils_h

#include <algorithm>

//https://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string
/*
// trim from left
inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

// trim from right
inline std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

// trim from left & right
inline std::string& trim(std::string& s, const char* t = " \t\n\r\f\v")
{
    return ltrim(rtrim(s, t), t);
}

// copying versions
inline std::string ltrim_copy(std::string s, const char* t = " \t\n\r\f\v")
{
    return ltrim(s, t);
}

inline std::string rtrim_copy(std::string s, const char* t = " \t\n\r\f\v")
{
    return rtrim(s, t);
}

inline std::string trim_copy(std::string s, const char* t = " \t\n\r\f\v")
{
    return trim(s, t);
}
*/
inline std::string & ltrim(std::string & str)
{
  auto it2 =  std::find_if( str.begin() , str.end() ,
		  [](char ch){ return !std::isspace<char>(ch , std::locale::classic() ) ; } );
  str.erase( str.begin() , it2);
  return str;
}

inline std::string & rtrim(std::string & str)
{
  auto it1 =  std::find_if( str.rbegin() , str.rend() ,
		  [](char ch){ return !std::isspace<char>(ch , std::locale::classic() ) ; } );
  str.erase( it1.base() , str.end() );
  return str;
}

inline std::string & trim(std::string & str)
{
   return ltrim(rtrim(str));
}

inline std::string trim_copy(std::string const & str)
{
   auto s = str;
   return ltrim(rtrim(s));
}

inline std::string & group_name(std::string & str) // [ group_name ]
{
	auto it1 =  std::find_if( str.begin() , str.end() ,
			  [](char ch){ return ch != '[' ; } );
	str.erase( str.begin() , it1);

	auto it2 =  std::find_if( str.rbegin() , str.rend() ,
			  [](char ch){ return ch != ']' ; } );
	str.erase( it2.base() , str.end() );

	return trim(str);
}

inline void split(const std::string & str)
{
	std::string token, mystring("scott>=tiger");
	while(token != mystring){
		token = mystring.substr(0,mystring.find_first_of(">="));
		mystring = mystring.substr(mystring.find_first_of(">=") + 1);
		printf("%s ",token.c_str());
	}
}

#endif
