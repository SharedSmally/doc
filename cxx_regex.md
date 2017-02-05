## [c++ regex](http://www.cplusplus.com/reference/regex/)
- [regex_match](http://www.cplusplus.com/reference/regex/regex_match/):  whether the entire target sequence matches the regular expression rgx
   bool regex_match (target, regex, flags)
- [regex_search](http://www.cplusplus.com/reference/regex/regex_search/):  whether some sub-sequence in the target sequence (the subject) matches the regular expression regex (the pattern)
   bool regex_search (subject, regex, flags)
- [regex_replace](http://www.cplusplus.com/reference/regex/regex_replace/): Makes a copy of the target sequence (the subject) with all matches of the regular expression rgx (the pattern) replaced by fmt (the replacement)
   string regex_replace (subject, regex, fmt, flags);
   For frmat
   - $n	n-th backreference  (greater than 0, and of two digits at most)
   - $&	A copy of the entire match
   - $`	The prefix (i.e., the part of the target sequence that precedes the match).
   - $´	The suffix (i.e., the part of the target sequence that follows the match).
   - $$	A single $ character.
 
 ### [regex](http://www.cplusplus.com/reference/regex/basic_regex/)
    See [ECMAScript] (http://www.cplusplus.com/reference/regex/ECMAScript/) for regex.
    
 ### [match_results](http://www.cplusplus.com/reference/regex/match_results/) :
 - cmatch: match_results for string literals (class )
 - wcmatch: match_results for wide string literals (class )
 - [smatch](http://www.cplusplus.com/reference/regex/smatch/): match_results for string objects (class )
 - wsmatch: match_results for wide string objects (class )

### [sub_match](http://www.cplusplus.com/reference/regex/sub_match/):
  - csub_match:  sub_match for string literals (class )
  - wcsub_match: sub_match for wide string literals (class )
  - ssub_match:  sub_match for strings (class )
  - wssub_match: sub_match for wide strings (class )
