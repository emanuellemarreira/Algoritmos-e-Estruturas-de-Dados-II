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
        //quick find não é bom pra grandes problemas (esse caso)
        //quick union
        int find(int p){
            while( p != id[p]){ //verifica se é id do grupo
                p = id[p]; //vai percorrendo
            }
            return p;//se ele acha o id do grupo (p = id[p]) retorna ele
        }

        void unionf(int p, int q){
            int pRoot = find(p); //id do grupo do p
            int qRoot = find(q);//id do grupo do q
            if (pRoot == qRoot){
                return; //ja estao no mesmo grupo
            }
            id[pRoot] = qRoot; //dá pro P o id do Q e o Q fica com o mesmo id, é arbitrário
            count--;
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