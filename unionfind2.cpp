#include <iostream>
#include <vector>
#include <list>
using namespace std;

typedef unsigned int Vertex;
class UnionFind
{
    private:
        vector<int> id;
        int count;//numero de componentes
    public:
        UnionFind(int N): id(N), count(N){
            count = N;
            for(int i = 0; i < N; i++){
                id[i] = i;  //todo identificador do conjunto no início é ele mesmo
            }
        }
        //quick find 
        int find(int p){
            return id[p];
        }

        void unionf(int p, int q){
            int pID = find(p);
            int qID = find(q);
            if (pID == qID){
                return; //ja estao no mesmo componente
            }
            for (int i = 0; i < count; i++){
                if (id[i] == pID){
                    id[i] = qID;
                }
                count--;
            }
        }

        bool connected(int p, int q){
            return find(p) == find(q);//se id sao iguais sao do mesmo conjunto logo estao conectados
        }
};
int main()
{
    UnionFind uf(4);
    uf.unionf(1, 2);
    cout<< uf.find(3);
    return 0;
}