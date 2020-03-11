#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cctype>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <utility>

using namespace std;
typedef vector<string> TVector;
typedef set<pair<long, int>> TPair;

//split the paragraph into words
TVector split(string &s) {

    //remove punctuation
    std::size_t l = s.size();
    for (std::size_t i = 0; i<l; i++)
    {
        if (std::ispunct(s[i]) && s[i] != '\'')
        {
            s[i] = ' ';
        }
    }
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, ' ')) {

        if (item != "") {
            bool f = true;
            for (char& c : item) {
                c = tolower(c);

                if (!((c >= 'a' && c <= 'z')
                      || (c >= '0' && c <= '9')))
                    f = false;

            }
            if (f) {//select words and numbers only
                tokens.push_back(item);
            }
        }
    }
    return tokens;
}


// read the file and create the map: key: word, value: set of pairs <row, pos>
map<string, TPair>  getMap(string filename) {

    string content;
    map<string, TPair> myMap; // key: word, value: set of pairs <row, pos>

    ifstream file(filename);
    if (file.is_open()) {

        long n=1;
        // read all lines
        while (getline(file, content)) {

            // get line and fill the vector for each line
            TVector words = split(content);
            content=" "+content+" ";

            //create the set
            TPair allWords;
            for(auto word:words){
                //find the first position of the word in content
                int pos = content.find(" "+word+" ", 0);

                //find other positions of the word in content
                while(pos!=string::npos) {
                    //fill the map
                    myMap[word].insert(make_pair(n, pos));
                    pos = content.find(" "+word+" ", pos+1);
                }
            }

            //next line
            n++;

        }
        file.close();

        return myMap;

    }
    else {
        // show error message
        cerr << "File not available!";
        cin.get();
        exit(0);
    }

}

int main(int argc, const char * argv[]) {

    string fname = "GettysburgAddress.txt";

    map<string, TPair> m = getMap(fname);

    //print the map
    for(auto it = m.cbegin(); it != m.cend(); ++it)
    {
        //excellent 3 [ (7,4) , (7,23), (55,6) ]
        cout << it->first << " " <<(it->second).size() << " [";

        //print the set into the string pairs
        string pairs="";
        for(auto p: it->second){
            pairs+="("+ to_string(p.first) + ", " +to_string(p.second)+ "), ";
        }
        //delete 2 last chars from the pairs string: ", "
        pairs.pop_back();
        pairs.pop_back();


        cout<<pairs<<" ]\n";
    }

    return 0;
}


