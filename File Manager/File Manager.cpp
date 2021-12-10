//Используется C++ 17
//File Manager на C++ с использованием Filesystem
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem; //для удобства
bool is_quit = true; //глобальная переменная, которая отвечает за постоянное чтение команд до введения /quit

//функция вывода текущей директории
void CurrentDirectory() {
    std::cout << "Current directory: " << fs::current_path() << std::endl;
    return;
}
//папки и файлы текущего каталога
void show() {
    CurrentDirectory();
    for (auto it : fs::directory_iterator(fs::current_path()))
    {
        fs::path p = it.path();
        std::cout << "|" << std::endl;
        std::cout << "---->" << p.filename() << std::endl;
    }
    return;
}
//для /showall рекурсивный вывод файлов и каталогов
void show(fs::path a, int dpt, int &n) {
    if (n > 25 || dpt > 4) { //чтобы программа не падала при слишком большом количестве каталогов
        return;
    }
    std::string str;
    for (int i = 0; i < dpt; ++i) {
        str += "     ";
    }
    for (auto it : fs::directory_iterator(a)) {
        n += 1;
        fs::path p = it.path();
            std::cout << str << "|" << std::endl;
            std::cout << str << "---->" << p.filename() << std::endl;
        if (fs::is_directory(it)) {
            show(it, dpt + 1, n);
        }
    }
    return;
}

int DelDir(fs::path a) { //рекурсивное удаление паки и её содержимого
    int j = 0;
    for (auto it : fs::directory_iterator(a)) {
        j += 1;
        if (fs::is_directory(it)) {
            j+= DelDir(it);
            remove(it);
        }
        else {
            fs::remove(it);
        }
    }
    remove(a);
    return j;
}

//обработка команд
void CommandProcessing(std::string command) {
    if (command == "/help") {
        std::cout << "=================================" << std::endl;
        std::cout << "       List of commands:" << std::endl;
        std::cout << "=================================" << std::endl;
        std::cout << "Command - description of command:\n" << std::endl;
        //
        std::cout << "/cd       - changing the current path to the entered one\n Format: 'C:\\\\Users\\\\Visheratin' or 'Users' if directory is C:\\" << std::endl;
        std::cout << "/clr      - clear console" << std::endl;
        std::cout << "/deldir   - delete a directory (using fs::remove_all)" << std::endl;
        std::cout << "/deldir2  - delete a directory (using recursion)" << std::endl;
        std::cout << "/delfile  - delete a file with a given extension" << std::endl;
        std::cout << "/mkdir    - create a directory" << std::endl;
        std::cout << "/mkfile   - create a file with a given extension" << std::endl;
        std::cout << "/show     - show files and folders only in the current directory" << std::endl;
        std::cout << "/showall  - show files and folders or directory (with recursion)" << std::endl;
        std::cout << "/status   - show data about the current disk" << std::endl;
        std::cout << "/read     - read file" << std::endl;
        std::cout << "/tree     - build directory tree (using console)" << std::endl;
        std::cout << "/quit     - close the program" << std::endl;
    }
    //очистка консоли
    else if (command == "/clr") {
        system("cls");
    }
    //выход из приложения
    else if (command == "/quit") {
        is_quit = false;
        std::cout << "Thanks for using.";
    }
    //смена текущей папки
    else if (command == "/cd") {
        CurrentDirectory();
        std::string catalog;
        std::cout << "Enter the directory to change to: ";
        std::cin >> catalog;
        if (fs::exists(catalog)) {
            fs::current_path(fs::u8path(catalog));
            if (fs::current_path() == fs::u8path(catalog)) {
                system("cls");
                std::cout << "Directory was changed successfully to '" << catalog << "'" << std::endl;
            }
        }
        else {
            std::cout << "Directory entered incorrectly" << std::endl;
        }
    }
    //показать файлы и папки текущего каталога
    else if (command == "/show") {
        show();
    }
    //вывод списка файлов и подпапок из указанной папки
    else if (command == "/showall") {
        CurrentDirectory();
        int n = 0;
        show(fs::current_path(), 0, n);
        if (n > 25) {
            std::cout << ". . ." << std::endl;
            std::cout << "Too many files and directories" << std::endl;
        }
    }
    //создать каталог
    else if (command == "/mkdir") {
        CurrentDirectory();
        std::string dir_name;
        std::cout << "Enter the directory name: ";
        std::cin >> dir_name;
        fs::path newPath = fs::current_path() / dir_name;

        //проверяем создание каталога
        if (fs::create_directories(newPath)) {
            std::cout << "The directory was created successfully" << std::endl;
        }
        else {
            std::cout << "Directory was not created" << std::endl;
        }
    }
    //удаление директории
    else if (command == "/deldir") {
        CurrentDirectory();
        std::string dir_name;
        std::cout << "Enter the directory name: ";
        std::cin >> dir_name;
        std::cout << std::endl;
      
        fs::path delDir(dir_name);
        //проверяем наличие каталога
        if (fs::is_directory(delDir)) {
            std::uintmax_t n = fs::remove_all(delDir);
            //проверяем удаление
            if (!fs::is_directory(delDir)) {
                std::cout << "Directory was deleted successfully" << std::endl;
                std::cout << "Deleted " << n << " files or directories" << std::endl;
            }
            else {
                std::cout << "Direcctory was not deleted" << std::endl;
            }
        }
        else {
            std::cout << "Directory is not exist" << std::endl;
        }
    }
    //второй вариант через рекурсию
    else if (command == "/deldir2") {
        CurrentDirectory();
        std::string dir_name;
        std::cout << "Enter the directory name: ";
        std::cin >> dir_name;
        std::cout << std::endl;
        if (fs::is_directory(dir_name)) {
            std::string full(fs::current_path().u8string());
            full += "\\" + dir_name;
            int n = DelDir(full);
            //проверяем удаление
            if (!fs::is_directory(dir_name)) {
                std::cout << "Directory was deleted successfully" << std::endl;
                std::cout << "Deleted " << n + 1  << " files or directories" << std::endl;
            }
            else {
                std::cout << "Directory was not deleted" << std::endl;
            }
        }
        else {
            std::cout << "Directory is not exist" << std::endl;
        }
    }
    //создание файла с нужным расширением
    else if (command == "/mkfile") {
        CurrentDirectory();
        std::string file_name;
        std::cout << "Enter the file with the extension: ";
        std::cin >> file_name;
        //создаём файл по нашему пути
        std::string full(fs::current_path().u8string());
        full += "\\" + file_name;

        //проверка на создание файла
        std::ofstream of(full);
        if (of)
        {
            std::cout << "The file was created successfully" << std::endl;
        }
        else {
            std::cout << "File was not created" << std::endl;
        }
        of.close();
    }
    //удаление файла с нужным расширением
    else if (command == "/delfile") {
        CurrentDirectory();
        std::string file_name;
        std::cout << "Enter the file with the extension: ";
        std::cin >> file_name;
        //удаляем файл по нашему пути
        std::string full(fs::current_path().u8string());
        full += "\\" + file_name;
        fs::path del = fs::path(full);
        //проверка на удаление файла
        if (fs::remove(del))
        {
            std::cout << "The file was deleted successfully" << std::endl;  
        }
        else {
            std::cout << "File was not deleted" << std::endl;
        }
    }
    //отобразить файлы текущего каталога
    else if (command == "/tree") {
        std::string cm = "tree ";
        cm += fs::current_path().u8string();
        system(cm.data());
        
    }
    //чтение файла
    else if (command == "/read") {
        CurrentDirectory();
        std::string file_name;
        std::cout << "Enter name of file with the extension: ";
        std::cin >> file_name;
        std::string full(fs::current_path().u8string());
        full += "\\" + file_name;
        std::string x;
        std::ifstream inFile;

        inFile.open(full);
        if (!inFile) {
            std::cout << "Unable to open file" << std::endl;
        }
        std::cout << std::endl;
        std::cout << file_name << std::endl;
        std::cout << "==============================================================\n" << std::endl;
        //выводим файл построчно
        while (inFile >> x) {
            std::cout << x << std::endl;
        }
        std::cout << "\n\n==============================================================\n" <<std::endl;
        inFile.close();
    }
    //место на текущем диске
    else if (command == "/status") {
    auto root = fs::path("/");
    auto space = fs::space(root);
    std::cout << "Total space     : " << space.capacity / 1024 / 1024 / 1024 << "gb" << std::endl;
    std::cout << "Free space      : " << space.free / 1024 / 1024 / 1024 << "gb" << std::endl;
    std::cout << "Avaliable space : " << space.available / 1024 / 1024 / 1024 << "gb" << std::endl;

    }
    else {
        std::cout << "There is no such command as '" << command << "'.Enter /help for command list ." << std::endl;
    }
    return;
}

int main()
{
    system("title File Manager"); //заголовок окна консоли
    
    while (is_quit) {
        CurrentDirectory();
        std::string command;
        std::cout << "Enter command or /help for command list:" << std::endl;
        std::cin >> command;
        system("cls"); //очищаем консоль (так удобнее читать)
        CommandProcessing(command);
        std::cout << std::endl;
    }
    system("pause");
    return 0;
}