// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D
#include <iostream>
#include <getopt.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include "TableEntry.h"

using namespace std;

class table{
    
    private:
    struct tableObj{
        std::vector<vector<TableEntry>> tabTable;
        vector<EntryType> types;
        //vector<string> colNames; //another vector with col names ?
        
        int numCols = 0;
        size_t numRows = 0; 
        vector<string> printColNames;
        unordered_map<string, int> colTracka;

        map<TableEntry, vector<size_t>> bst;
        unordered_map<TableEntry, vector<size_t>> hash;
        bool bstPres = false;
        bool hashPres = false;

        int gencol = 0;

    };
    bool quietMode = false;
    
    unordered_map<string, tableObj> um; //table name, 2D vector
    //another structure for type and col name?
    public:
    void printHelp(){
        cout << "useless project\n";
        exit(0);
    }

    struct compareEqualRights{
        int columbus = 0;
        TableEntry &senpai;
        compareEqualRights(int colIn, TableEntry &walahi): columbus(colIn),senpai(walahi){}
        bool operator()(const vector<TableEntry> &tempVect)const{
                return (tempVect[columbus] == senpai);
        }
    };
    struct compareGrater{
        int columbus = 0;
        TableEntry &senpai;
        compareGrater(int colIn, TableEntry &walahi) : columbus(colIn), senpai(walahi){}
        bool operator()(const vector<TableEntry> &tempVect)const{
                return (tempVect[columbus] > senpai);
        }
    };
    struct compareLase{
        int columbus = 0;
        TableEntry &senpai;
        compareLase(int colIn, TableEntry &walahi) : columbus(colIn), senpai(walahi){}
        bool operator()(const vector<TableEntry> &tempVect)const{
                return (tempVect[columbus] < senpai);
        }
    };
    


    void getOpt(int argc, char * argv[]){
                int gotopt;
                int option_index = 0;
                option long_opts[] = {
                    {"help", no_argument, nullptr, 'h'},
                    {"quiet", no_argument, nullptr, 'q'},
                    {nullptr, 0, nullptr, '\0'}
                };        
                while((gotopt = getopt_long(argc, argv, "hq", long_opts, &option_index)) != -1){
                    switch(gotopt){
                        case 'h':{
                            printHelp();
                            exit(0);
                        }
                        case 'q':{
                            quietMode = true;
                            break;
                        }
                        default:{
                            cerr << "Unknown command line option\n";
                            exit(1);
                        }
                    }
                }
            
            }

    void gen(const string &tabName, const char &BorH, int colInt){
        auto iter = um.find(tabName);
        if(BorH == 'b'){
            iter->second.bst.clear();
            size_t &gey = iter->second.numRows;
            for(size_t n = 0; n < gey; n++){
                if(iter->second.bst.find(iter->second.tabTable[n][colInt]) == iter->second.bst.end()){
                    iter->second.bst[iter->second.tabTable[n][colInt]];
                    auto iter2 = iter->second.bst.find(iter->second.tabTable[n][colInt]);
                    iter2->second.reserve(iter->second.numRows);
                    iter2->second.push_back(n);
                }
                else{
                    auto iterhehe = iter->second.bst.find(iter->second.tabTable[n][colInt]);
                    iterhehe->second.push_back(n);
                }
                
                //check 2D vector at row and colInt
            }
        }
        else{
            iter->second.hash.clear();
            size_t &gey = iter->second.numRows;
            for(size_t n = 0; n < gey; n++){
                if(iter->second.hash.find(iter->second.tabTable[n][colInt]) == iter->second.hash.end()){
                    iter->second.hash[iter->second.tabTable[n][colInt]];
                    auto iter2 = iter->second.hash.find(iter->second.tabTable[n][colInt]);
                    iter2->second.reserve(iter->second.numRows);
                    iter2->second.push_back(n);
                }
                else{
                    auto iterhehe = iter->second.hash.find(iter->second.tabTable[n][colInt]);
                    iterhehe->second.push_back(n);
                }
                
                //check 2D vector at row and colInt
            }
        }
    }

    void read(){
        char cmd2 = 'a';
        string cmd = "";
        do{
            if(cin.fail()){
                cerr << "Error: Reading from cin has failed\n";
                exit(1);
            }
            cout << "% ";
            cin >> cmd2;

            if(cmd2 == '#'){
                getline(cin, cmd); //what if # QUIT ?
            }
            else if(cmd2 == 'C'){
                cin >> cmd;
                cin >> cmd; //table name
                auto iter = um.find(cmd);
                if(iter == um.end()){//check if tablename valid using .find
                    um[cmd]; //make if not present ??
                    iter = um.find(cmd);
                    cin >> iter->second.numCols; //num cols
                    iter->second.types.reserve(iter->second.numCols);
                    int &cum = iter->second.numCols;
                    for(int j = 0; j < cum; j++){
                        //take in col types
                        cin >> cmd;
                        //switch or if statements
                        if(cmd == "string"){
                            iter->second.types.push_back(EntryType::String);
                        }
                        else if(cmd == "int"){
                            iter->second.types.push_back(EntryType::Int);
                        }
                        else if(cmd == "double"){
                            iter->second.types.push_back(EntryType::Double);
                        }
                        else if(cmd == "bool"){
                            iter->second.types.push_back(EntryType::Bool);
                        }
                        //if string then emplace_back() ?
                    }
                    cout << "New table " << iter->first << " with column(s) ";
                    for(int j = 0; j < cum; j++){
                        cin >> cmd;
                        iter->second.colTracka[cmd] = j;
                        cout << cmd << " ";
                    }
                    cout << "created\n";

                }
                else{//if not valid
                    cout << "Error during CREATE: Cannot create already existing table " << cmd << "\n";
                    getline(cin, cmd);
                }

            }
            else if(cmd2 == 'I'){
                cin >> cmd;
                cin >>  cmd; //INTO 
                cin >> cmd; //table name
                if(um.find(cmd) != um.end()){//table name is valid
                    auto iter = um.find(cmd);
                    size_t temp = 0;
                    size_t added = 0;
                    cin >> temp; //number of rows
                    added = temp;
                    temp += iter->second.numRows;
                    iter->second.numRows = temp;  //number of rows
                    cin >> cmd; //ROWS
                    iter->second.tabTable.reserve(temp);
                    for(size_t n = 0; n < added; n++){
                        vector<TableEntry> tempVector;
                        iter->second.tabTable.push_back(tempVector);
                    }
                    size_t sza = iter->second.tabTable.size();
                    for(size_t j = sza - added; j < sza; j++){//iterate only through new rows
                    //RESIZE 2D vector somewhere -----------------------------------------------------------
                        iter->second.tabTable[j].reserve(iter->second.numCols);
                        int &cumonme = iter->second.numCols;
                        for(int c = 0; c < cumonme; c++){//iteratre through columns
                            switch(iter->second.types[c]){
                                case EntryType::Bool:{
                                    bool datumBoo = false;
                                    cin >> datumBoo;
                                    iter->second.tabTable[j].emplace_back(datumBoo);
                                    break;
                                }
                                case EntryType::Double:{
                                    double datumDub = 0;
                                    cin >> datumDub;
                                    iter->second.tabTable[j].emplace_back(datumDub);
                                    break;
                                }
                                case EntryType::Int:{
                                    int datumIn = 0;
                                    cin >> datumIn;
                                    iter->second.tabTable[j].emplace_back(datumIn);
                                    break;
                                }
                                case EntryType::String:{
                                    string datumS = "";
                                    cin >> datumS;
                                    iter->second.tabTable[j].emplace_back(datumS);
                                    break;
                                }
                            }
                        }
                    }
                    if(iter->second.bstPres ){
                         gen(iter->first, 'b', iter->second.gencol);
                     }
                     else if(iter->second.hashPres){
                         gen(iter->first, 'h', iter->second.gencol);
                     }
                    cout << "Added " << added << " rows to " << iter->first << " from position " << temp - added << " to " << temp - 1 << "\n";
                }
                else{//table name is not a name of a table in the database
                    cout << "Error during INSERT: " << cmd << " does not name a table in the database\n";
                    getline(cin, cmd);
                }
            }
            else if(cmd2 == 'P'){
                cin >> cmd;
                int numColsPrint = 0;
                cin >> cmd; //FROM
                cin >> cmd; //table name
                string tempTabName = cmd;
                bool columnError = false;
                if(um.find(cmd) != um.end()){   //table name valid
                    auto iter = um.find(cmd);
                    iter->second.printColNames.clear();
                    iter->second.printColNames.reserve(iter->second.numCols);
                    cin >> numColsPrint;
                    for(int c = 0; c < numColsPrint; c++){
                        cin >> cmd;
                        if(iter->second.colTracka.find(cmd) == iter->second.colTracka.end()){//not found
                            cout << "Error during PRINT: " << cmd << " does not name a column in " << tempTabName << "\n";
                            getline(cin, cmd);
                            columnError = true;
                            break;
                        }
                        else{
                            iter->second.printColNames.push_back(cmd);
                        }
                    }
                    if(!columnError){
                        cin >> cmd; //ALL or WHERE
                    
                    if(cmd == "WHERE"){
                        int printCount = 0;
                        cin >> cmd; //colName
                        int indexofName = 0;
                        if(iter->second.colTracka.find(cmd) == iter->second.colTracka.end()){
                            cout << "Error during PRINT: " << cmd << " does not name a column in " << tempTabName << "\n";
                            getline(cin, cmd);
                        }
                        else{
                            indexofName = iter->second.colTracka[cmd];
                            if(!quietMode){
                                size_t cumming = iter->second.printColNames.size();
                                for(size_t i = 0; i < cumming; i++){
                                    cout << iter->second.printColNames[i] << " ";   //print column names 
                                }
                                cout << "\n";
                            }
                                EntryType temp = iter->second.types[indexofName];
                                cin >> cmd;//operator
                                switch(temp){
                    case EntryType::Bool:{
                        bool datumBoo = false;
                            cin >> datumBoo;
                        if(cmd == "="){
                            if(iter->second.hashPres && iter->second.gencol == indexofName){
                                TableEntry watum(datumBoo);
                                        auto bFinder = iter->second.hash.find(watum);
                                        if(bFinder != iter->second.hash.end()){
                                            size_t cream = bFinder->second.size();
                                            for(size_t p = 0; p < cream; p++){
                                                printCount++;
                                                if(!quietMode){
                                                    size_t poppycock = iter->second.printColNames.size();
                                                    size_t &fuckme = bFinder->second[p];
                                                for(size_t c = 0; c < poppycock; c++){
                                                    cout << iter->second.tabTable[fuckme][iter->second.colTracka[iter->second.printColNames[c]] ] << " ";
                                                }
                                                cout << "\n";
                                                }
                                            }
                                        }
                            }
                            else{
                                size_t cumpie = iter->second.numRows;
                                for(size_t n = 0; n < cumpie; n++){
                                if(iter->second.tabTable[n][indexofName] == datumBoo){
                                    printCount++;
                                    if(!quietMode){
                                        size_t ppPower = iter->second.printColNames.size();
                                    for(size_t c = 0; c < ppPower; c++){
                                        cout << iter->second.tabTable[n][iter->second.colTracka[iter->second.printColNames[c]] ] << " ";
                                    }
                                    cout << "\n";
                                    }
                                }
                               
                                }
                            }
                            
                            
                        }
                        else if(cmd == "<"){
                            if(iter->second.bstPres && iter->second.gencol == indexofName){
                                TableEntry temp(datumBoo);
                                auto bFinder = iter->second.bst.lower_bound(temp);
                                auto bBegin = iter->second.bst.begin();
                                while(bBegin != bFinder){
                                        size_t tit = bBegin->second.size();
                                    for(size_t n = 0; n < tit; n++){
                                        printCount++;
                                        if(!quietMode){
                                            size_t boob = iter->second.printColNames.size();
                                            size_t &fuckme = bBegin->second[n];
                                        for(size_t c = 0; c < boob; c++){
                                            cout << iter->second.tabTable[fuckme][iter->second.colTracka[iter->second.printColNames[c]]] << " ";
                                        }
                                        cout << "\n";
                                        }
                                    }
                                    ++bBegin;
                                }
                            }
                            else{
                                size_t &gey = iter->second.numRows;
                                for(size_t n = 0; n < gey; n++){
                                if(iter->second.tabTable[n][indexofName] < datumBoo){
                                    printCount++;
                                    if(!quietMode){
                                    size_t breast = iter->second.printColNames.size();
                                    for(size_t c = 0; c < breast; c++){
                                        cout << iter->second.tabTable[n][iter->second.colTracka[iter->second.printColNames[c]] ] << " ";
                                    }
                                    cout << "\n";
                                    }
                                }
                               
                                }
                            }
                            
                        }
                        else{//operat == >
                            if(iter->second.bstPres && iter->second.gencol == indexofName){
                                TableEntry temp(datumBoo);
                                auto bFinder = iter->second.bst.upper_bound(temp);
                                while(bFinder != iter->second.bst.end()){
                                    size_t poopy = bFinder->second.size();
                                    for(size_t n = 0; n < poopy; n++){
                                        printCount++;
                                        if(!quietMode){
                                            size_t &fuckme = bFinder->second[n];
                                            size_t tp = iter->second.printColNames.size();
                                        for(size_t c = 0; c < tp; c++){
                                            cout << iter->second.tabTable[fuckme][iter->second.colTracka[iter->second.printColNames[c]]] << " ";
                                        }
                                        cout << "\n";
                                        }
                                    }
                                    ++bFinder;
                                }
                            }
                            else{
                                size_t igu = iter->second.numRows;
                                for(size_t n = 0; n < igu; n++){
                                if(iter->second.tabTable[n][indexofName] > datumBoo){
                                    printCount++;
                                    if(!quietMode){
                                        size_t yep = iter->second.printColNames.size();
                                    for(size_t c = 0; c < yep; c++){
                                        cout << iter->second.tabTable[n][iter->second.colTracka[iter->second.printColNames[c]] ] << " ";
                                    }
                                    cout << "\n";
                                    }
                                }
                               
                                }
                            }
                           
                        }
                        break;
                    }
                    case EntryType::Double:{
                        double datumDub = 0;
                            cin >> datumDub;
                        if(cmd == "="){
                            if(iter->second.hashPres && iter->second.gencol == indexofName){
                                TableEntry watum(datumDub);
                                        auto bFinder = iter->second.hash.find(watum);
                                        if(bFinder != iter->second.hash.end()){
                                            size_t cp = bFinder->second.size();
                                            for(size_t p = 0; p < cp; p++){
                                                printCount++;
                                                if(!quietMode){
                                                    size_t hum = iter->second.printColNames.size();
                                                for(size_t c = 0; c < hum; c++){
                                                    cout << iter->second.tabTable[bFinder->second[p]][iter->second.colTracka[iter->second.printColNames[c]] ] << " ";
                                                }
                                                cout << "\n";
                                                }
                                            }
                                        }
                            }
                            else{
                                size_t hey = iter->second.numRows;
                                for(size_t n = 0; n < hey; n++){
                                if(iter->second.tabTable[n][indexofName] == datumDub){
                                    printCount++;
                                    if(!quietMode){
                                        size_t yo = iter->second.printColNames.size();
                                    for(size_t c = 0; c < yo; c++){
                                        cout << iter->second.tabTable[n][iter->second.colTracka[iter->second.printColNames[c]]] << " ";
                                    }
                                    cout << "\n";
                                    }
                                }
                                
                                }
                            }
                            
                        }
                        else if(cmd == "<"){
                            if(iter->second.bstPres && iter->second.gencol == indexofName){
                                TableEntry temp(datumDub);
                                auto bFinder = iter->second.bst.lower_bound(temp);
                                auto bBegin = iter->second.bst.begin();
                                while(bBegin != bFinder){
                                    size_t milk = bBegin->second.size();
                                            for(size_t r = 0; r < milk; r++){
                                                printCount++;
                                                if(!quietMode){
                                                    size_t yum = iter->second.printColNames.size();
                                                    size_t &choco = bBegin->second[r];
                                        for(size_t c = 0; c < yum; c++){
                                            cout << iter->second.tabTable[choco][iter->second.colTracka[iter->second.printColNames[c]]] << " ";
                                        }
                                        cout << "\n";
                                        }
                                        }
                                    ++bBegin;
                                }
                            }
                            else{
                                size_t milk = iter->second.numRows;
                                for(size_t n = 0; n < milk; n++){
                                
                                if(iter->second.tabTable[n][indexofName] < datumDub){
                                    printCount++;
                                    if(!quietMode){
                                    for(size_t c = 0; c < iter->second.printColNames.size(); c++){
                                        cout << iter->second.tabTable[n][iter->second.colTracka[iter->second.printColNames[c]]] << " ";
                                    }
                                    cout << "\n";
                                    }
                                }
                                
                                }
                            }
                            
                        }
                        else{//operat == >
                        if(iter->second.bstPres && iter->second.gencol == indexofName){
                                TableEntry temp(datumDub);
                                auto bFinder = iter->second.bst.upper_bound(temp);
                                while(bFinder != iter->second.bst.end()){
                                    size_t pls = bFinder->second.size();
                                    for(size_t r = 0; r < pls; r++){
                                        printCount++;
                                        if(!quietMode){
                                        for(size_t c = 0; c < iter->second.printColNames.size(); c++){
                                            cout << iter->second.tabTable[bFinder->second[r]][iter->second.colTracka[iter->second.printColNames[c]]] << " ";
                                        }
                                        cout << "\n";
                                            }
                                        }
                                    
                                    ++bFinder;
                                }
                            }
                            else{
                                size_t pause = iter->second.numRows;
                                for(size_t n = 0; n < pause; n++){
                                
                                if(iter->second.tabTable[n][indexofName] > datumDub){
                                    printCount++;
                                    if(!quietMode){
                                    for(size_t c = 0; c < iter->second.printColNames.size(); c++){
                                        cout << iter->second.tabTable[n][iter->second.colTracka[iter->second.printColNames[c]]] << " ";
                                    }
                                    cout << "\n";
                                    }
                                }
                                
                                }
                            }
                        
                        }
                        break;
                    }
                    case EntryType::Int:{
                        int datumIn = 0;
                        cin >> datumIn;
                        if(cmd == "="){
                            if(iter->second.hashPres && iter->second.gencol == indexofName){
                                TableEntry watum(datumIn);
                                        auto bFinder = iter->second.hash.find(watum);
                                        if(bFinder != iter->second.hash.end()){
                                            size_t huh = bFinder->second.size();
                                            for(size_t p = 0; p < huh; p++){
                                                printCount++;
                                                if(!quietMode){
                                                for(size_t c = 0; c < iter->second.printColNames.size(); c++){
                                                    cout << iter->second.tabTable[bFinder->second[p]][iter->second.colTracka[iter->second.printColNames[c]] ] << " ";
                                                }
                                                cout << "\n";
                                                }
                                            }
                                        }
                            }
                            else{
                                size_t help = iter->second.numRows;
                                for(size_t n = 0; n < help; n++){
                                
                                if(iter->second.tabTable[n][indexofName] == datumIn){
                                    printCount++;
                                    if(!quietMode){
                                    for(size_t c = 0; c < iter->second.printColNames.size(); c++){
                                        cout << iter->second.tabTable[n][iter->second.colTracka[iter->second.printColNames[c]]] << " ";
                                    }
                                    cout << "\n";
                                    }
                                } 
                                
                                }
                            }
                            
                        }
                        else if(cmd == "<"){
                           if(iter->second.bstPres && iter->second.gencol == indexofName){
                                TableEntry temp(datumIn);
                                auto bFinder = iter->second.bst.lower_bound(temp);
                                auto bBegin = iter->second.bst.begin();
                                while(bBegin != bFinder){
                                        size_t tempTehe = bBegin->second.size();
                                    for(size_t n = 0; n < tempTehe; n++){
                                        printCount++;
                                        if(!quietMode){
                                        for(size_t c = 0; c < iter->second.printColNames.size(); c++){
                                            cout << iter->second.tabTable[bBegin->second[n]][iter->second.colTracka[iter->second.printColNames[c]]] << " ";
                                        }
                                        cout << "\n";
                                        }
                                    }
                                    ++bBegin;
                                }
                            }
                            else{
                                size_t tempTehe = iter->second.numRows;
                                for(size_t n = 0; n < tempTehe; n++){
                                
                                if(iter->second.tabTable[n][indexofName] < datumIn){
                                    printCount++;
                                    if(!quietMode){
                                    for(size_t c = 0; c < iter->second.printColNames.size(); c++){
                                        cout << iter->second.tabTable[n][iter->second.colTracka[iter->second.printColNames[c]]] << " ";
                                    }
                                    cout << "\n";
                                    }
                                } 
                                
                                }
                            }
                            
                        }
                        else{//operat == >
                        if(iter->second.bstPres && iter->second.gencol == indexofName){
                                TableEntry temp(datumIn);
                                auto bFinder = iter->second.bst.upper_bound(temp);
                                while(bFinder != iter->second.bst.end()){
                                    size_t tempTehe = bFinder->second.size();
                                    for(size_t n = 0; n < tempTehe; n++){
                                        printCount++;
                                        if(!quietMode){
                                        for(size_t c = 0; c < iter->second.printColNames.size(); c++){
                                            cout << iter->second.tabTable[bFinder->second[n]][iter->second.colTracka[iter->second.printColNames[c]]] << " ";
                                        }
                                        cout << "\n";
                                        }
                                    }
                                    ++bFinder;
                                }
                            }
                            else{
                                size_t tempTehe = iter->second.numRows;
                                for(size_t n = 0; n < tempTehe; n++){
                                
                                if(iter->second.tabTable[n][indexofName] > datumIn){
                                    printCount++;
                                    if(!quietMode){
                                    for(size_t c = 0; c < iter->second.printColNames.size(); c++){
                                        cout << iter->second.tabTable[n][iter->second.colTracka[iter->second.printColNames[c]]] << " ";
                                    }
                                    cout << "\n";
                                    }
                                } 
                                
                            }
                            }
                        
                        }
                        break;
                    }
                    case EntryType::String:{
                        string datumS = "";
                        cin >> datumS;
                        if(cmd == "="){
                            if(iter->second.hashPres && iter->second.gencol == indexofName){
                                TableEntry watum(datumS);
                                        auto bFinder = iter->second.hash.find(watum);
                                        if(bFinder != iter->second.hash.end()){
                                            size_t tempTehe = bFinder->second.size();
                                            for(size_t p = 0; p < tempTehe; p++){
                                                printCount++;
                                                if(!quietMode){
                                                for(size_t c = 0; c < iter->second.printColNames.size(); c++){
                                                    cout << iter->second.tabTable[bFinder->second[p]][iter->second.colTracka[iter->second.printColNames[c]] ] << " ";
                                                }

                                                cout << "\n";
                                                }
                                            }
                                        }
                            }
                            else{
                                size_t tempTehe = iter->second.numRows;
                                for(size_t n = 0; n < tempTehe; n++){
                                
                                if(iter->second.tabTable[n][indexofName] == datumS){
                                    printCount++;
                                    if(!quietMode){
                                    for(size_t c = 0; c < iter->second.printColNames.size(); c++){
                                        cout << iter->second.tabTable[n][iter->second.colTracka[iter->second.printColNames[c]]] << " ";
                                    }
                                    cout << "\n";
                                    }
                                }                                   
                                }
                            }
                            
                        }
                        else if(cmd == "<"){
                            if(iter->second.bstPres && iter->second.gencol == indexofName){
                                TableEntry temp(datumS);
                                auto bFinder = iter->second.bst.lower_bound(temp);
                                auto bBegin = iter->second.bst.begin();
                                while(bBegin != bFinder){                       
                                    size_t tempTehe = bBegin->second.size();                 
                                    for(size_t n = 0; n < tempTehe; n++){
                                        printCount++;
                                        if(!quietMode){
                                        for(size_t c = 0; c < iter->second.printColNames.size(); c++){
                                            cout << iter->second.tabTable[bBegin->second[n]][iter->second.colTracka[iter->second.printColNames[c]]] << " ";
                                        }
                                        cout << "\n";
                                        }
                                    }
                                    ++bBegin;
                                }
                            }
                            else{
                                size_t tempTehe = iter->second.numRows;
                                for(size_t n = 0; n < tempTehe; n++){
                                if(iter->second.tabTable[n][indexofName] < datumS){
                                printCount++;
                                    if(!quietMode){
                                    for(size_t c = 0; c < iter->second.printColNames.size(); c++){
                                        cout << iter->second.tabTable[n][iter->second.colTracka[iter->second.printColNames[c]]] << " ";
                                    }
                                    cout << "\n";
                                }
                            }
                            }
                            }
                            
                        }
                        else{//operat == >
                        if(iter->second.bstPres && iter->second.gencol == indexofName){
                                TableEntry temp(datumS);
                                auto bFinder = iter->second.bst.upper_bound(temp);
                                
                                while(bFinder != iter->second.bst.end()){
                                    size_t tempTehe = bFinder->second.size();
                                    for(size_t n = 0; n < tempTehe; n++){
                                        printCount++;
                                        if(!quietMode){
                                        for(size_t c = 0; c < iter->second.printColNames.size(); c++){
                                            cout << iter->second.tabTable[bFinder->second[n]][iter->second.colTracka[iter->second.printColNames[c]]] << " ";
                                        }
                                        cout << "\n";
                                        }
                                    }
                                    ++bFinder;
                                }
                            }
                            else{
                                for(size_t n = 0; n < iter->second.numRows; n++){
                            
                                if(iter->second.tabTable[n][indexofName] > datumS){
                                    printCount++;
                                    if(!quietMode){
                                    for(size_t c = 0; c < iter->second.printColNames.size(); c++){
                                        cout << iter->second.tabTable[n][iter->second.colTracka[iter->second.printColNames[c]]] << " ";
                                    }
                                    cout << "\n";
                                }
                                }
                            }
                            }
                        
                        }
                        break;
                    } //String
                        }//switch
                        cout << "Printed " << printCount << " matching rows from " << iter->first << "\n";
                    }//if it is present
                    
                    }
                    
                    else{ //ALL or __ ?
                        if(!quietMode){
                            for(size_t i = 0; i < iter->second.printColNames.size(); i++){
                                cout << iter->second.printColNames[i] << " ";   //print column names 
                            }
                            cout << "\n";
                            for(size_t r = 0; r < iter->second.numRows; r++){
                                for(size_t c = 0; c < iter->second.printColNames.size(); c++){
                                    cout << iter->second.tabTable[r][iter->second.colTracka[iter->second.printColNames[c]]] << " ";
                                }
                                cout << "\n";
                            }
                        }
                        cout << "Printed " << iter->second.numRows << " matching rows from " << iter->first << "\n";
                    }
                }//if not error
            
        }
        else{//table name not valid
                    cout << "Error during PRINT: " << tempTabName << " does not name a table in the database\n";
                    getline(cin, cmd);
            }
            }
            else if(cmd2 == 'R'){
                cin >> cmd;
                cin >> cmd; //name of table
                if(um.find(cmd) != um.end()){
                    um.erase(cmd);
                    cout << "Table " << cmd << " removed\n";
                }
                else{
                    cout << "Error during REMOVE: " << cmd << " does not name a table in the database\n";
                }
            }
            else if(cmd2 == 'D'){
                cin >> cmd;
                cin >> cmd; //FROM
                cin >> cmd; //table name
                string tempTabName = cmd;
                if(um.find(cmd) != um.end()){
                    cin >> cmd; //WHERE
                    cin >> cmd; //colName
                    auto iter = um.find(tempTabName);
                    if(iter->second.colTracka.find(cmd) == iter->second.colTracka.end()){
                        cout << "Error during DELETE: " << cmd << " does not name a column in " << tempTabName << "\n";
                        getline(cin, cmd);                    
                    }
                    else{
                        size_t initSize = iter->second.tabTable.size();
                        int plum = iter->second.colTracka[cmd];
                        EntryType temp = iter->second.types[plum];
                        //find type of colName with type[c] vector
                        //pass into compare helper along with operator and comparison ?
                        //in helper, four way split based on type
                        cin >> cmd; //operator
                        string opera = cmd;
                switch(temp){
                    case EntryType::Bool:{
                        bool dumdum = false;
                        cin >> dumdum;
                        TableEntry idk(dumdum);
                        if(opera == "="){
                            compareEqualRights booby(plum, idk);
                            iter->second.tabTable.erase(std::remove_if(iter->second.tabTable.begin(), iter->second.tabTable.end(),booby),iter->second.tabTable.end());
                        }
                        else if(opera == ">"){
                            compareGrater cuck(plum, idk);
                            iter->second.tabTable.erase(std::remove_if(iter->second.tabTable.begin(),iter->second.tabTable.end(), cuck),iter->second.tabTable.end());
                        }
                        else{
                            compareLase shaft(plum, idk);
                            iter->second.tabTable.erase(std::remove_if(iter->second.tabTable.begin(), iter->second.tabTable.end(),shaft),iter->second.tabTable.end());
                        }                        
                        iter->second.numRows = iter->second.tabTable.size();
                        if(iter->second.bstPres){
                            gen(iter->first, 'b', iter->second.gencol);
                        }
                        else if(iter->second.hashPres){
                            gen(iter->first, 'h', iter->second.gencol);
                        }
                        break;
                    }
                    case EntryType::Double:{
                        double dummy = 0;
                        cin >> dummy;
                        TableEntry idk(dummy);
                        if(opera == "="){
                            compareEqualRights booby(plum, idk);
                            iter->second.tabTable.erase(std::remove_if(iter->second.tabTable.begin(), iter->second.tabTable.end(),booby),iter->second.tabTable.end());
                        }
                        else if(opera == ">"){
                            compareGrater cuck(plum, idk);
                            iter->second.tabTable.erase(std::remove_if(iter->second.tabTable.begin(),iter->second.tabTable.end(), cuck),iter->second.tabTable.end());
                        }
                        else{
                            compareLase shaft(plum, idk);
                            iter->second.tabTable.erase(std::remove_if(iter->second.tabTable.begin(), iter->second.tabTable.end(),shaft),iter->second.tabTable.end());
                        }                        
                        iter->second.numRows = iter->second.tabTable.size();
                        if(iter->second.bstPres && iter->second.bst.size() != 0){
                            gen(iter->first, 'b', iter->second.gencol);
                        }
                        else if(iter->second.hashPres && iter->second.hash.size() != 0){
                            gen(iter->first, 'h', iter->second.gencol);
                        }                        
                        break;
                    }
                    case EntryType::Int:{
                        int wompwomp = 0;
                        cin >> wompwomp;
                        TableEntry idk(wompwomp);
                        if(opera == "="){
                            compareEqualRights booby(plum, idk);
                            iter->second.tabTable.erase(std::remove_if(iter->second.tabTable.begin(), iter->second.tabTable.end(),booby),iter->second.tabTable.end());
                        }
                        else if(opera == ">"){
                            compareGrater cuck(plum, idk);
                            iter->second.tabTable.erase(std::remove_if(iter->second.tabTable.begin(),iter->second.tabTable.end(), cuck),iter->second.tabTable.end());
                        }
                        else{
                            compareLase shaft(plum, idk);
                            iter->second.tabTable.erase(std::remove_if(iter->second.tabTable.begin(), iter->second.tabTable.end(),shaft),iter->second.tabTable.end());
                        }                        
                        iter->second.numRows = iter->second.tabTable.size();
                        if(iter->second.bstPres ){
                            gen(iter->first, 'b', iter->second.gencol);
                        }
                        else if(iter->second.hashPres ){
                            gen(iter->first, 'h', iter->second.gencol);
                        }
                        break;
                        }
                    case EntryType::String:{
                        string poopo = "";
                        cin >> poopo;
                        TableEntry idk(poopo);
                        if(opera == "="){
                            compareEqualRights booby(plum, idk);
                            iter->second.tabTable.erase(std::remove_if(iter->second.tabTable.begin(), iter->second.tabTable.end(),booby),iter->second.tabTable.end());
                        }
                        else if(opera == ">"){
                            compareGrater cuck(plum, idk);
                            iter->second.tabTable.erase(std::remove_if(iter->second.tabTable.begin(),iter->second.tabTable.end(), cuck),iter->second.tabTable.end());
                        }
                        else{
                            compareLase shaft(plum, idk);
                            iter->second.tabTable.erase(std::remove_if(iter->second.tabTable.begin(), iter->second.tabTable.end(),shaft), iter->second.tabTable.end());
                        }                        
                        iter->second.numRows = iter->second.tabTable.size();
                        if(iter->second.bstPres ){
                            gen(iter->first, 'b', iter->second.gencol);
                        }
                        else if(iter->second.hashPres ){
                            gen(iter->first, 'h', iter->second.gencol);
                        }
                        break;
                    }
                }
                        
                cout << "Deleted " << initSize - iter->second.tabTable.size() << " rows from " << iter->first << "\n";
            }
                    
        }
        else{//invalid table
            cout << "Error during DELETE: " << cmd << " does not name a table in the database\n";
            getline(cin, cmd);
        }
        }//DELETE
            else if(cmd2 == 'J'){
                cin >> cmd;
                cin >> cmd; //table name1
                string tabname1 = cmd;
                if(um.find(cmd) != um.end()){
                    auto iter1 = um.find(cmd);
                    cin >> cmd; //AND
                    cin >> cmd; //table name2
                    string tabname2 = cmd;
                    if(um.find(cmd) != um.end()){
                        auto iter2 = um.find(cmd);
                        cin >> cmd; //WHERE
                        cin >>cmd; //colname1
                        string colName1 = cmd;
                        if(iter1->second.colTracka.find(cmd) != iter1->second.colTracka.end()){
                            cin >> cmd; //=
                            cin >> cmd; //colname2
                            string colName2 = cmd;
                            if(iter2->second.colTracka.find(cmd) != iter2->second.colTracka.end()){
                                cin >> cmd; //AND
                                cin >> cmd; //PRINT
                                int howmany = 0;
                                cin >> howmany;
                                bool founderhehe = true;
                                string col_name = "";
                                int n = 0;
                                int siz = howmany;

                                vector<pair<string, int>> hehe;
                                while(n < siz && founderhehe){
                                    founderhehe = false;
                                    cin >> col_name; //print_col name;
                                    cin >> howmany; //1 or 2
                                    hehe.reserve(siz);
                                    if(howmany == 1){
                                        if(iter1->second.colTracka.find(col_name) != iter1->second.colTracka.end()){
                                            founderhehe = true;
                                            hehe.push_back(make_pair(col_name , 1));
                                        }
                                        else{
                                            //error , printcolname not in table
                                            cout << "Error during JOIN: " << col_name << " does not name a column in " << iter1->first << "\n";
                                            getline(cin, cmd);
                                        }
                                    }
                                    else{
                                        if(iter2->second.colTracka.find(col_name) != iter2->second.colTracka.end()){
                                            founderhehe = true;
                                            //printColTracker2.push_back(iter2->second.colTracka[col_name]);
                                            hehe.push_back(make_pair(col_name,2));
                                        }
                                        else{
                                            //error, printcolname not in table
                                            cout << "Error during JOIN: " << col_name << " does not name a column in " << iter2->first << "\n";
                                            getline(cin, cmd);

                                        }
                                    }

                                    n++;
                                }
                                if(founderhehe){//al the print_cols are valid
                                    int count = 0;
                                    unordered_map<TableEntry, vector<size_t>> joinHash;
                                    for(size_t n = 0; n < iter2->second.tabTable.size(); n++){
                                        joinHash[iter2->second.tabTable[n][iter2->second.colTracka[colName2]]].reserve(iter2->second.numRows);
                                        joinHash[iter2->second.tabTable[n][iter2->second.colTracka[colName2]]].push_back(n);
                                    }

                                    if(!quietMode){
                                    for(size_t l = 0; l < hehe.size(); l++){
                                        cout << hehe[l].first << " ";
                                    }
                                        cout << "\n";
                                    }
                                    for(size_t n = 0; n < iter1->second.tabTable.size(); n++){
                                        auto it = joinHash.find(iter1->second.tabTable[n][iter1->second.colTracka[colName1]]);
                                        if(it != joinHash.end()){
                                            for(size_t l = 0; l < it->second.size(); l++){
                                                //if(){
                                                    //find rows where col1=col2, print corresponging columns for those rows
                                                    count++;
                                                    if(!quietMode){
                                                    for(size_t b = 0; b < hehe.size(); b++){
                                                        if(hehe[b].second == 1){
                                                            cout << iter1->second.tabTable[n][iter1->second.colTracka[hehe[b].first]] << " ";
                                                        }
                                                        else{
                                                            cout << iter2->second.tabTable[it->second[l]][iter2->second.colTracka[hehe[b].first]] << " ";
                                                        }
                                                    }
                                                    cout << "\n";
                                                    }
                                                //}
                                            }
                                        }
                                        
                                    }
                                    cout << "Printed " << count << " rows from joining " << iter1->first << " to " << iter2->first << "\n";
                                }
                                else{
                                    if(howmany == 1){
                                        cout << "Error during JOIN: " << col_name << " does not name a column in " << iter1->first << "\n";
                                        getline(cin, cmd);
                                    }
                                    else{
                                        cout << "Error during JOIN: " << col_name << " does not name a column in " << iter2->first << "\n";
                                        getline(cin, cmd);
                                    }
                                }
                            }
                            else{ //error colname2 not valid
                                cout << "Error during JOIN: " << cmd << " does not name a column in " << tabname2 << "\n";
                                getline(cin, cmd);
                            }
                        }
                        else{//error colname1 not valid
                            cout << "Error during JOIN: " << cmd << " does not name a column in " << tabname1 << "\n";
                            getline(cin, cmd);
                        }
                    }
                    else{//error table2 not valid
                        cout << "Error during JOIN: " << cmd << " does not name a table in the database\n";
                        getline(cin, cmd);
                    }
                }
                else{//error table1 name not valid
                    cout << "Error during JOIN: " << cmd << " does not name a table in the database\n";
                    getline(cin, cmd);
                }
            }
            else if(cmd2 == 'G'){
                cin >> cmd;
                cin >> cmd; //FOR
                cin >> cmd; //tablename
                string tabtab = cmd;
                if(um.find(cmd) != um.end()){
                    auto iter = um.find(cmd);
                    cin >> cmd; //indextype
                    string hashBST = cmd;
                    cin >> cmd; //INDEX
                    cin >> cmd; //ON
                    cin >> cmd; //colName
                    if(iter->second.colTracka.find(cmd) != iter->second.colTracka.end()){//colName is valid
                        if(iter->second.bstPres){//if bst is already present, clear it
                            iter->second.bstPres = false;
                            iter->second.bst.clear();
                        }
                        else if(iter->second.hashPres){//if hash is already present, clear it
                            iter->second.hashPres = false;
                            iter->second.hash.clear();
                        }

                        if(hashBST == "hash"){
                            iter->second.hashPres = true;
                            iter->second.gencol = iter->second.colTracka[cmd];
                            gen(tabtab, 'h', iter->second.colTracka[cmd]);
                            cout << "Created hash index for table " << iter->first << " on column " << cmd << ", with " << iter->second.hash.size() << " distinct keys\n";
                        }
                        else{
                            iter->second.bstPres = true;
                            iter->second.gencol = iter->second.colTracka[cmd];
                            gen(tabtab, 'b', iter->second.colTracka[cmd]);
                            cout << "Created bst index for table " << iter->first << " on column " << cmd << ", with " << iter->second.bst.size() << " distinct keys\n";
                        }
                    }
                    else{//error colName not in table
                        cout << "Error during GENERATE: " << cmd << " does not name a column in " << tabtab << "\n";
                        getline(cin, cmd);
                    }
                }
                else{
                    //error, tablename not in database
                    cout << "Error during GENERATE: " << cmd << " does not name a table in the database\n";
                    getline(cin, cmd);
                }
            }
            else if(cmd2 != 'Q'){
                cout << "Error: unrecognized command\n";
                getline(cin, cmd);
            }
        
    }while(cmd2 != 'Q');
        cout << "Thanks for being silly!";

    }
};

int main(int argc, char * argv[]){
    ios_base::sync_with_stdio(false);
    cin >> std::boolalpha;
    cout << std::boolalpha;

    table IkeaTable;
    IkeaTable.getOpt(argc, argv);
    IkeaTable.read();

    return 0;
}