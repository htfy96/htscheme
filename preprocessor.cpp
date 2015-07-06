#include <istream>
#include <string>
#include <cstddef>
#include "preprocessor.hpp"

SchemeUnit::SchemeUnit(std::istream& schemeStream)
{
    preprocess(schemeStream);
}

void SchemeUnit::preprocess(std::istream& schemeStream)
{
    inComment = false;
    static std::string buffer;
    while (!schemeStream.eof())
    {
        getline(schemeStream, buffer);
        processMultilineComment(buffer);

        stripSemiColon(buffer);
        if (!inComment)
          lines.push_back(buffer);
    }
}


SchemeUnit::MultilineCommentStatus SchemeUnit::processMultilineComment( std::string& line)
{
    size_t pos = line.find("#!");
    if (pos != line.npos && ( pos <2 || ( line[pos-1] != '\\' && line[pos-2]!='#')))
    {
        inComment = true;
        line.erase(pos);
        return CommentStart;
    }

    size_t pos2 = line.find("!#");
    if (pos2 != line.npos && ( pos <2 || ( line[pos2-1] != '\\' && line[pos2-2]!='#')))
    {
        if (inComment)
        {
            inComment = false;
            line = line.substr(pos2+2);
            return CommentEnd;
        }
    }
    return Neutral;
}

void SchemeUnit::stripSemiColon(std::string &line)
{
    size_t pos = line.find(';');
    if (pos != line.npos) line.erase(pos);
}

