#ifndef __SCHEME_PRE
#define __SCHEME_PRE

#include <string>
#include <vector>
#include <iosfwd>

class SchemeUnit
{
    private:
        bool inComment;
        enum MultilineCommentStatus { Neutral, CommentStart, CommentEnd };
        void stripSemiColon(std::string& line);
        MultilineCommentStatus processMultilineComment( std::string& line);
    public:
        SchemeUnit();
        SchemeUnit(std::istream& schemeStream);
        std::vector<std::string> lines;
        void preprocess(std::istream& schemeStream);
};
//dsf
#endif
