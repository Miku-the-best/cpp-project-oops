#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include "functions.h"
#include "functions.cpp"
#include "HelpCommands.cpp"
#include "ErrorHandling.cpp"

using namespace std;

class QueryParser
{
private:
    vector<string> Tokens;

    void ParseIntoTokens(string Query)
    {
        string temp = "";
        for (int i = 0; i < Query.size(); i++)
        {
            char c = Query[i];
            if (c == '"')
            {
                i++;
                while (Query[i] != '"')
                {
                    temp += Query[i];
                    i++;
                }
                if (temp != "")
                    Tokens.push_back(temp);
                temp = "";
            }
            else if (c == ' ' || c == '(' || c == ')' || c == ',' || c == ';' || c == '*')
            {
                if (temp != "")
                    Tokens.push_back(temp);
                if (c == '*')
                    Tokens.push_back("*"); // for handling special case in select
                temp = "";
            }
            else if (Query[i] == '!' && Query[i + 1] == '=')
            {
                if (temp != "")
                    Tokens.push_back(temp);
                temp = "";
                Tokens.push_back("!=");
                i++;
            }
            else if (c == '<' || c == '>' || c == '=')
            { // OR other operators
                if (temp != "")
                    Tokens.push_back(temp);
                temp = "";
                Tokens.push_back(string(1, c));
            }
            else
            {
                temp += c;
            }
        }
        if (temp != "")
            Tokens.push_back(temp);
    }

    void cvtIntoSmallerCase()
    {
        set<string> keywords = {
            "create",
            "table",
            "primary",
            "key",
            "int",
            "varchar",
            "date",
            "decimal"
            "drop",
            "describe",
            "insert",
            "into",
            "values",
            "help",
            "tables",
            "select",
            "from",
            "where",
            "and",
            "or",
        };
        for (int i = 0; i < Tokens.size(); i++)
        {
            string x = Tokens[i];
            transform(x.begin(), x.end(), x.begin(), ::tolower);
            if (keywords.find(x) != keywords.end())
                Tokens[i] = x;
        }
    }

public:
    void DisplayTokens()
    {
        for (string x : Tokens)
            cout << x << endl;
    }

    void ParseQuery(string query)
    {
        Tokens.clear();
        ParseIntoTokens(query);
        cvtIntoSmallerCase();
    }

    vector<string> GetTokens()
    {
        return Tokens;
    }
};

int main()
{
    system("cls");
    string Query;
    TableManager tableManager;
    QueryParser parser;

    while (1)
    {
        cout << endl
             << ">> ";
        getline(cin, Query);
        cout << endl;

        if (Query.back() != ';')
        {
            cout << "; missing at the end" << endl;
            continue;
        }

        parser.ParseQuery(Query);
        vector<string> Tokens = parser.GetTokens();
        bool noerrors = ErrorChecker::ErrorsChecking(Tokens);

        if (noerrors)
        {
            if (Tokens.empty())
                return 0;

            if (Tokens[0] == "create" && Tokens[1] == "table")
            {
                tableManager.CreateTable(Tokens);
            }
            else if (Tokens[0] == "drop" && Tokens[1] == "table")
            {
                tableManager.DropTable(Tokens);
            }
            else if (Tokens[0] == "describe")
            {
                tableManager.DescribeTable(Tokens);
            }
            else if (Tokens[0] == "help" && Tokens[1] == "tables")
            {
                HelpTables();
            }
            else if (Tokens[0] == "help")
            {
                HelpCommand(Tokens);
            }
            else if (Tokens[0] == "insert" && Tokens[1] == "into")
            {
                int res = tableManager.InsertInto(Tokens);
                res == 1 ? cout << "Tuple inserted successfully" << endl : cout << "Tuple not inserted" << endl;
            }
            else if (Tokens[0] == "select")
            {
                tableManager.Select(Tokens);
            }
            else if (Tokens[0] == "update")
            {
                tableManager.UpdateTable(Tokens);
            }
            else if (Tokens[0] == "delete" && Tokens[1] == "from")
            {
                tableManager.DeleteFrom(Tokens);
            }
            else if (Tokens[0] == "quit")
            {
                cout << "Program terminated successfully." << endl;
                exit(0);
            }
            else
            {
                cout << "INVALID QUERY" << endl;
            }
        }
    }

    return 0;
}
