#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// A class for error handling
class ErrorHandler
{
public:
    static bool doesTableExists(string tableName)
    {
        fstream SchemaFile;
        SchemaFile.open("SchemaFile.txt", ios::in);
        if (SchemaFile)
        {
            string line;
            while (!SchemaFile.eof())
            {
                getline(SchemaFile, line);
                if (line[0] == '*')
                {
                    string name = line.substr(1, line.size() - 2);
                    if (name == tableName)
                    {
                        SchemaFile.close();
                        return true;
                    }
                }
            }
        }
        else
        {
            cout << "Schema File doesn't exists" << endl;
        }
        return false;
    }
};

// A class for error checking
class ErrorChecker
{
public:
    static bool ErrorsChecking(const vector<string> &Tokens)
    {
        if (Tokens.empty())
            return false;

        if (Tokens[0] == "create" && Tokens[1] == "table")
        {
            // Error 1 : Checking whether table with specified name exists in Schema file or not
            if (ErrorHandler::doesTableExists(Tokens[2]))
            {
                cout << "table <" << Tokens[2] << "> already exists" << endl;
                cout << "Table not created" << endl;
                return false;
            }

            // Error 2 : Checking whether PK attribute is defined or not
            {
                int Tsize = Tokens.size();
                if (Tokens[Tsize - 3] != "primary" && Tokens[Tsize - 2] != "key")
                {
                    cout << "Defining PK is mandatory" << endl;
                    cout << "Table not created" << endl;
                    return false;
                }
            }
        }

        else if (Tokens[0] == "drop" && Tokens[1] == "table")
        {
            // Error 1 : Checking whether table with specified name exists in Schema file or not
            if (!ErrorHandler::doesTableExists(Tokens[2]))
            {
                cout << "table <" << Tokens[2] << "> doesn't exists" << endl;
                cout << "Table not dropped" << endl;
                return false;
            }
        }

        else if (Tokens[0] == "describe")
        {
            // Error 1 : Checking whether table with specified name exists in Schema file or not
            if (!ErrorHandler::doesTableExists(Tokens[1]))
            {
                cout << "table <" << Tokens[1] << "> doesn't exists" << endl;
                cout << "Table cannot be described" << endl;
                return false;
            }
        }

        else if (Tokens[0] == "insert" && Tokens[1] == "into")
        {
            // Error 1 : Checking whether table with specified name exists in Schema file or not
            if (!ErrorHandler::doesTableExists(Tokens[2]))
            {
                cout << "table <" << Tokens[2] << "> doesn't exists" << endl;
                cout << "Tuple not inserted" << endl;
                return false;
            }

            // Other errors handling done in insert function itself.
        }

        else if (Tokens[0] == "select")
        {
            // All errors are handled in Select function itself
        }

        else if (Tokens[0] == "help" && Tokens[1] == "tables")
        {
        }

        else if (Tokens[0] == "help")
        {
        }

        else if (Tokens[0] == "delete" && Tokens[1] == "from")
        {
            if (!ErrorHandler::doesTableExists(Tokens[2]))
            {
                cout << "table <" << Tokens[2] << "> doesn't exists" << endl;
                cout << "0 rows affected" << endl;
                return false;
            }
        }
        else if (Tokens[0] == "update")
        {
            if (!ErrorHandler::doesTableExists(Tokens[1]))
            {
                cout << "table <" << Tokens[1] << "> doesn't exists" << endl;
                cout << "0 rows affected" << endl;
                return false;
            }
        }
        else if (Tokens[0] == "quit")
        {
        }
        else
        {
        }

        return true;
    }
};
