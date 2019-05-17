#include <fstream>
#include <cstring>
#include <bitset>

using namespace std;

int main (int argc, char* argv[]){
    if (argc>1){
        ifstream f_entrada;
        ofstream f_salida;
        f_entrada.open(argv[1], ios::binary);
        f_salida.open (strcat(argv[1],"bytes"), ios::binary);
        unsigned char c;
        f_entrada.read(reinterpret_cast<char*>(&c), sizeof(unsigned char));
        while(!f_entrada.eof()){
            f_salida << bitset<8>(c)<<endl;
            f_entrada.read(reinterpret_cast<char*>(&c), sizeof(unsigned char));
        }
        f_entrada.close();
        f_salida.close();
    }
}