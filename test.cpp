#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    string str;
    string buffer;
    string temp;
    int string_lenght;
    bool space_counter = 0;
    ofstream file_out;
    ifstream file;
    file.open("/mnt/c/Users/Ivan/CLionProjects/test/test.xml");
    file_out.open("/mnt/c/Users/Ivan/CLionProjects/test/test.log");
    if (!file.is_open())
    {
        cout << "Ошбика открытия файла XML" << endl;
    }
    else
    {
        cout << "Файл XML открыт..." << endl;
        if (!file_out.is_open()){
            cout << "Ошбика открытия файла LOG" << endl;
        }
        else
        {
            cout << "Файл LOG открыт..." << endl;
            while (!file.eof()){
                str = "";
                getline(file, str);
                int null_line_tester = str.find_first_not_of("< ")-1;
                while (null_line_tester < 0){                           //Тест на пустую строку, если пустая - переход на следующую
                    str = "";
                    getline(file, str);
                    null_line_tester = str.find_first_not_of("< ")-1;
                }
                    while (str.length()>1){                                          //Условия конца строки
                    if (str.find_first_of("/") == str.find_first_not_of("<") || space_counter == 1){
                        buffer.erase(buffer.find_last_of("/"), buffer.length()-1);
                        temp = "";
                        space_counter = 0;
                        //file_out << buffer;
                    }
                    else{
                        if (str.length()==2){
                            str = "";
                        } else {
                            str.erase(0, str.find_first_not_of("< "));
                        }
                        if (buffer.length() == 0){
                            buffer = str;
                            buffer.erase(buffer.find_first_of("> "),buffer.length()-1);
                            str.erase(0, str.find_first_of("> ")+1);
                            file_out << buffer;
                            cout << buffer << endl;
                        }
                        else{


                            if(str.find_first_of(" ") < str.find_first_of("\">")){            //ВОЗМОЖНА ОШИБКА!!!

                                temp = str;
                                temp.erase(temp.find_first_of(" "),temp.length()-1);
                                str.erase(0, str.find_first_of(" "));
                                buffer = buffer + "/" + temp;
                                file_out << buffer;
                                cout << buffer << endl;
                                    space_counter = 1;

                            }
                            else if (str.length()!=0){
                                temp = str;
                                temp.erase(temp.find_first_of("\">")+1, temp.length() -1);
                                str.erase(0, str.find_first_of("\">")+1);
                                buffer = buffer + "/" + temp;
                                temp = str;
                                temp.erase(temp.find_first_of("\">")+1, temp.length() -1);
                                str.erase(0, str.find_first_of("\">")+1);
                                buffer = buffer + temp;
                                file_out << buffer;
                                cout << buffer << endl;
                                buffer.erase(buffer.find_last_of("/"), buffer.length()-1);
                            }
                            }



                        }

                    }
                        string_lenght = str.length();

                    }





            }

        }



    file.close();
    file_out.close();
    return 0;


    }



