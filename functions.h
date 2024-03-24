// functions.h

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

class TableManager
{
public:
    void CreateTable(const std::vector<std::string> &Tokens);
    void DropTable(const std::vector<std::string> &Tokens);
    void DescribeTable(const std::vector<std::string> &Tokens);
    int InsertInto(const std::vector<std::string> &Tokens);
    void UpdateTable(const std::vector<std::string> &Tokens);
    void DeleteFrom(const std::vector<std::string> &Tokens);
    void Select(const std::vector<std::string> &Tokens);
    void ShowTables();
    bool doesTableExists(const std::string &tableName);
    std::vector<std::string> attributes_of_table;

private:
    bool doesTableExists2(const std::string &tableName);
    void FillingAttributesOfTable(const std::string &tableName);
    int Count_no_Attributes(const std::string &TableName);
    std::string ExtractCol(const std::string &tuple, int colno);
    bool isInt(const std::string &s);
    int checkValuesOrder(const std::vector<std::string> &Tokens);
    std::vector<int> Find_Indices(const std::vector<std::string> &Tokens, const std::vector<std::string> &attributes_of_table);
    bool is_Where_True(const std::string &tuple, const std::vector<std::string> &Tokens, int i);
    void Helper_Select(const std::vector<std::string> &Tokens, const std::string &TableNameInQuery, int i);
    std::vector<int> GetIndices(const std::string &tableName, const std::map<std::string, std::string> &mpp);
    std::vector<std::string> split(const std::string &s, char delim);
    void delete_last_line();
};

#endif // FUNCTIONS_H
